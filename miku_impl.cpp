#include "miku_ast.h"
#include <iostream>

TableManager g_tm; // NOT an AST global

// -------- TableManager --------

TableManager::TableManager() {
    allTables.emplace_back(std::make_unique<SymbolTable>("global", nullptr));
    global = allTables.back().get();
    current = global;
}

SymbolTable* TableManager::push_scope(const std::string& name) {
    allTables.emplace_back(std::make_unique<SymbolTable>(name, current));
    current = allTables.back().get();
    return current;
}

void TableManager::pop_scope() {
    if (current && current->parent) current = current->parent;
}

const VarInfo* TableManager::lookup_var(const std::string& name) const {
    const SymbolTable* t = current;
    while (t) {
        auto it = t->vars.find(name);
        if (it != t->vars.end()) return &it->second;
        t = t->parent;
    }
    return nullptr;
}

VarInfo* TableManager::lookup_var_mut(const std::string& name) {
    SymbolTable* t = current;
    while (t) {
        auto it = t->vars.find(name);
        if (it != t->vars.end()) return &it->second;
        t = t->parent;
    }
    return nullptr;
}

const FuncInfo* TableManager::lookup_func(const std::string& name) const {
    const SymbolTable* t = current;
    while (t) {
        auto it = t->funcs.find(name);
        if (it != t->funcs.end()) return &it->second;
        t = t->parent;
    }
    return nullptr;
}

const ClassInfo* TableManager::lookup_class(const std::string& name) const {
    auto it = classes.find(name);
    if (it == classes.end()) return nullptr;
    return &it->second;
}

void TableManager::dump_all_tables(const std::string& path) const {
    std::ofstream out(path, std::ios::trunc);
    if (!out) {
        std::cerr << "[tables] cannot write to " << path << "\n";
        return;
    }

    out << "Miku Language - Symbol Tables\n\n";

    for (const auto& up : allTables) {
        const SymbolTable& t = *up;
        out << "=== SymbolTable: " << t.name << " ===\n";
        out << "Parent: " << (t.parent ? t.parent->name : "NULL") << "\n";

        out << "Variables:\n";
        if (t.vars.empty()) out << "  (none)\n";
        for (const auto& [k, v] : t.vars) {
            out << "  " << v.name << " : " << type_to_string(v.type)
                << " = " << v.value.to_string(v.type)
                << " (decl line " << v.declLine << ")\n";
        }

        out << "Functions:\n";
        if (t.funcs.empty()) out << "  (none)\n";
        for (const auto& [k, f] : t.funcs) {
            out << "  " << f.name << "(";
            for (size_t i = 0; i < f.paramTypes.size(); i++) {
                if (i) out << ", ";
                out << type_to_string(f.paramTypes[i]);
                if (i < f.paramNames.size() && !f.paramNames[i].empty()) {
                    out << " " << f.paramNames[i];
                }
            }
            out << ") -> " << type_to_string(f.retType)
                << " (decl line " << f.declLine << ")\n";
        }

        out << "\n";
    }

    out << "=== Global Classes Registry ===\n";
    if (classes.empty()) out << "  (none)\n";
    for (const auto& [cn, c] : classes) {
        out << "Class " << cn << " (decl line " << c.declLine << ")\n";
        out << "  Fields:\n";
        if (c.fields.empty()) out << "    (none)\n";
        for (const auto& [fn, ft] : c.fields) {
            out << "    " << fn << " : " << type_to_string(ft) << "\n";
        }
        out << "  Methods:\n";
        if (c.methods.empty()) out << "    (none)\n";
        for (const auto& [mn, mi] : c.methods) {
            out << "    " << mn << "(";
            for (size_t i = 0; i < mi.paramTypes.size(); i++) {
                if (i) out << ", ";
                out << type_to_string(mi.paramTypes[i]);
            }
            out << ") -> " << type_to_string(mi.retType) << "\n";
        }
        out << "\n";
    }
}

// -------- Errors --------

void semantic_error(TableManager& tm, int line, const std::string& msg) {
    tm.hadSemanticErrors = true;
    std::cerr << "[SEMANTIC] line " << line << ": " << msg << "\n";
}

// -------- ASTNode factories --------

ASTNode* ASTNode::lit_int(int ln, int64_t v) {
    auto* n = new ASTNode(ASTKind::LIT_INT, Type::Int(), ln);
    n->lit.v = v;
    return n;
}
ASTNode* ASTNode::lit_float(int ln, double v) {
    auto* n = new ASTNode(ASTKind::LIT_FLOAT, Type::Float(), ln);
    n->lit.v = v;
    return n;
}
ASTNode* ASTNode::lit_bool(int ln, bool v) {
    auto* n = new ASTNode(ASTKind::LIT_BOOL, Type::Bool(), ln);
    n->lit.v = v;
    return n;
}
ASTNode* ASTNode::lit_string(int ln, std::string v) {
    auto* n = new ASTNode(ASTKind::LIT_STRING, Type::String(), ln);
    n->lit.v = std::move(v);
    return n;
}

ASTNode* ASTNode::ident(int ln, std::string n, Type t) {
    auto* node = new ASTNode(ASTKind::IDENT, std::move(t), ln);
    node->name = std::move(n);
    return node;
}

ASTNode* ASTNode::other(int ln, Type t) {
    return new ASTNode(ASTKind::OTHER, std::move(t), ln);
}

ASTNode* ASTNode::unary(int ln, std::string op, Type t, ASTNode* child) {
    auto* n = new ASTNode(ASTKind::UNARY_OP, std::move(t), ln);
    n->op = std::move(op);
    n->left.reset(child);
    return n;
}

ASTNode* ASTNode::binary(int ln, std::string op, Type t, ASTNode* l, ASTNode* r) {
    auto* n = new ASTNode(ASTKind::BINARY_OP, std::move(t), ln);
    n->op = std::move(op);
    n->left.reset(l);
    n->right.reset(r);
    return n;
}

ASTNode* ASTNode::assign(int ln, std::string lhsName, Type lhsType, ASTNode* rhs) {
    auto* n = new ASTNode(ASTKind::ASSIGN, lhsType, ln);
    n->name = std::move(lhsName);
    n->left.reset(rhs); // rhs
    return n;
}

ASTNode* ASTNode::print(int ln, ASTNode* expr) {
    auto* n = new ASTNode(ASTKind::PRINT, Type::Void(), ln);
    n->left.reset(expr);
    return n;
}

// -------- AST evaluation --------

static bool is_numeric(const Type& t) {
    return t.kind == Type::Kind::INT || t.kind == Type::Kind::FLOAT;
}

Value ASTNode::eval(TableManager& tm) const {
    switch (kind) {
        case ASTKind::LIT_INT:
        case ASTKind::LIT_FLOAT:
        case ASTKind::LIT_BOOL:
        case ASTKind::LIT_STRING:
            return lit;

        case ASTKind::IDENT: {
            const VarInfo* v = tm.lookup_var(name);
            if (!v) {
                semantic_error(tm, line, "Identifier '" + name + "' used before definition");
                return Value::default_of(type);
            }
            return v->value;
        }

        case ASTKind::OTHER:
            return Value::default_of(type);

        case ASTKind::UNARY_OP: {
            Value a = left->eval(tm);
            if (op == "!") {
                bool x = std::get<bool>(a.v);
                return Value{!x};
            }
            if (op == "u-") {
                if (type.kind == Type::Kind::INT) {
                    int64_t x = std::get<int64_t>(a.v);
                    return Value{-x};
                } else {
                    double x = std::get<double>(a.v);
                    return Value{-x};
                }
            }
            return Value::default_of(type);
        }

        case ASTKind::BINARY_OP: {
            Value a = left->eval(tm);
            Value b = right->eval(tm);

            if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%") {
                if (type.kind == Type::Kind::INT) {
                    int64_t x = std::get<int64_t>(a.v);
                    int64_t y = std::get<int64_t>(b.v);
                    if (op == "+") return Value{x + y};
                    if (op == "-") return Value{x - y};
                    if (op == "*") return Value{x * y};
                    if (op == "/") return Value{ y == 0 ? int64_t(0) : x / y };
                    if (op == "%") return Value{ y == 0 ? int64_t(0) : x % y };
                } else if (type.kind == Type::Kind::FLOAT) {
                    double x = std::get<double>(a.v);
                    double y = std::get<double>(b.v);
                    if (op == "+") return Value{x + y};
                    if (op == "-") return Value{x - y};
                    if (op == "*") return Value{x * y};
                    if (op == "/") return Value{ y == 0.0 ? double(0.0) : x / y };
                    return Value{double(0.0)};
                }
                return Value::default_of(type);
            }

            if (op == "==" || op == "!=" || op == "<" || op == "<=" || op == ">" || op == ">=") {
                bool res = false;

                if (left->type.kind == Type::Kind::INT) {
                    int64_t x = std::get<int64_t>(a.v);
                    int64_t y = std::get<int64_t>(b.v);
                    if (op == "==") res = (x == y);
                    if (op == "!=") res = (x != y);
                    if (op == "<")  res = (x < y);
                    if (op == "<=") res = (x <= y);
                    if (op == ">")  res = (x > y);
                    if (op == ">=") res = (x >= y);
                } else if (left->type.kind == Type::Kind::FLOAT) {
                    double x = std::get<double>(a.v);
                    double y = std::get<double>(b.v);
                    if (op == "==") res = (x == y);
                    if (op == "!=") res = (x != y);
                    if (op == "<")  res = (x < y);
                    if (op == "<=") res = (x <= y);
                    if (op == ">")  res = (x > y);
                    if (op == ">=") res = (x >= y);
                } else if (left->type.kind == Type::Kind::BOOL) {
                    bool x = std::get<bool>(a.v);
                    bool y = std::get<bool>(b.v);
                    if (op == "==") res = (x == y);
                    if (op == "!=") res = (x != y);
                } else if (left->type.kind == Type::Kind::STRING) {
                    const std::string& x = std::get<std::string>(a.v);
                    const std::string& y = std::get<std::string>(b.v);
                    if (op == "==") res = (x == y);
                    if (op == "!=") res = (x != y);
                } else {
                    if (op == "==") res = true;
                    if (op == "!=") res = false;
                }

                return Value{res};
            }

            if (op == "&&" || op == "||") {
                bool x = std::get<bool>(a.v);
                bool y = std::get<bool>(b.v);
                return Value{ op == "&&" ? (x && y) : (x || y) };
            }

            return Value::default_of(type);
        }

        case ASTKind::ASSIGN: {
            Value rhs = left->eval(tm);
            VarInfo* v = tm.lookup_var_mut(name);
            if (!v) {
                semantic_error(tm, line, "Assignment to undefined identifier '" + name + "'");
                return rhs;
            }
            v->value = rhs;
            return rhs;
        }

        case ASTKind::PRINT: {
            Value x = left->eval(tm);
            std::cout << x.to_string(left->type) << "\n";
            return x;
        }
    }
    return Value::default_of(type);
}

// -------- Type resolving --------

Type resolve_type_name(TableManager& tm, int line, const std::string& typeName) {
    if (typeName == "int") return Type::Int();
    if (typeName == "float") return Type::Float();
    if (typeName == "bool") return Type::Bool();
    if (typeName == "string") return Type::String();

    const ClassInfo* c = tm.lookup_class(typeName);
    if (!c) {
        semantic_error(tm, line, "Unknown type '" + typeName + "' (class not defined yet)");
        return Type::Error();
    }
    return Type::Class(typeName);
}

// -------- Declarations --------

static bool is_duplicate_in_current_scope(const SymbolTable* st, const std::string& name) {
    return st->vars.count(name) || st->funcs.count(name);
}

void declare_var(TableManager& tm, int line, const std::string& name, const Type& type, const std::optional<Value>& initValue, bool /*isGlobal*/) {
    if (is_duplicate_in_current_scope(tm.current, name)) {
        semantic_error(tm, line, "Identifier '" + name + "' is defined twice in the same scope");
        return;
    }

    VarInfo v;
    v.name = name;
    v.type = type;
    v.value = initValue.has_value() ? *initValue : Value::default_of(type);
    v.declLine = line;
    tm.current->vars[name] = std::move(v);
}

void declare_func(TableManager& tm, int line, const std::string& name, const Type& ret, const ParamList& params) {
    if (is_duplicate_in_current_scope(tm.current, name)) {
        semantic_error(tm, line, "Function '" + name + "' is defined twice in the same scope");
        return;
    }
    FuncInfo f;
    f.name = name;
    f.retType = ret;
    f.declLine = line;
    for (const auto& p : params.v) {
        f.paramTypes.push_back(p.type);
        f.paramNames.push_back(p.name);
    }
    tm.current->funcs[name] = std::move(f);
}

static std::string infer_current_class_name(const TableManager& tm) {
    const SymbolTable* t = tm.current;
    while (t) {
        if (t->name.rfind("class:", 0) == 0) {
            return t->name.substr(std::string("class:").size());
        }
        t = t->parent;
    }
    return "";
}

void declare_class_begin(TableManager& tm, int line, const std::string& className) {
    if (tm.classes.count(className)) {
        semantic_error(tm, line, "Class '" + className + "' defined twice");
    } else {
        ClassInfo c;
        c.name = className;
        c.declLine = line;
        tm.classes[className] = std::move(c);
    }
    tm.push_scope("class:" + className);
}

void declare_class_field(TableManager& tm, int line, const std::string& /*classNameIgnored*/, const std::string& fieldName, const Type& fieldType) {
    std::string cn = infer_current_class_name(tm);
    if (cn.empty()) {
        semantic_error(tm, line, "Internal error: field declared outside class scope");
        return;
    }
    ClassInfo& c = tm.classes[cn];

    if (c.fields.count(fieldName) || c.methods.count(fieldName)) {
        semantic_error(tm, line, "Field/method name '" + fieldName + "' already exists in class '" + cn + "'");
        return;
    }
    c.fields[fieldName] = fieldType;

    if (is_duplicate_in_current_scope(tm.current, fieldName)) {
        semantic_error(tm, line, "Identifier '" + fieldName + "' is defined twice in class scope");
        return;
    }
    VarInfo v;
    v.name = fieldName;
    v.type = fieldType;
    v.value = Value::default_of(fieldType);
    v.declLine = line;
    tm.current->vars[fieldName] = std::move(v);
}

void declare_method(TableManager& tm, int line, const std::string& /*classNameIgnored*/, const std::string& methodName, const Type& ret, const ParamList& params) {
    std::string cn = infer_current_class_name(tm);
    if (cn.empty()) {
        semantic_error(tm, line, "Internal error: method declared outside class scope");
        return;
    }
    ClassInfo& c = tm.classes[cn];

    if (c.fields.count(methodName) || c.methods.count(methodName)) {
        semantic_error(tm, line, "Field/method name '" + methodName + "' already exists in class '" + cn + "'");
        return;
    }

    FuncInfo m;
    m.name = methodName;
    m.retType = ret;
    m.declLine = line;
    for (const auto& p : params.v) {
        m.paramTypes.push_back(p.type);
        m.paramNames.push_back(p.name);
    }
    c.methods[methodName] = m;

    if (is_duplicate_in_current_scope(tm.current, methodName)) {
        semantic_error(tm, line, "Identifier '" + methodName + "' is defined twice in class scope");
        return;
    }
    tm.current->funcs[methodName] = std::move(m);
}

void declare_class_end(TableManager& tm) {
    tm.pop_scope();
}

// -------- Expr builders --------

static ExprInfo* wrap(ASTNode* n, const Type& t, int line) {
    auto* e = new ExprInfo();
    e->node = n;
    e->type = t;
    e->line = line;
    return e;
}

ExprInfo* make_lit_int(int line, int64_t v) { return wrap(ASTNode::lit_int(line, v), Type::Int(), line); }
ExprInfo* make_lit_float(int line, double v){ return wrap(ASTNode::lit_float(line, v), Type::Float(), line); }
ExprInfo* make_lit_bool(int line, bool v)  { return wrap(ASTNode::lit_bool(line, v), Type::Bool(), line); }
ExprInfo* make_lit_string(int line, std::string v) { return wrap(ASTNode::lit_string(line, std::move(v)), Type::String(), line); }

ExprInfo* make_ident(TableManager& tm, int line, const std::string& name) {
    const VarInfo* v = tm.lookup_var(name);
    if (!v) {
        semantic_error(tm, line, "Identifier '" + name + "' used before definition");
        return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
    }
    return wrap(ASTNode::ident(line, name, v->type), v->type, line);
}

static Type ensure_same_type_or_error(TableManager& tm, int line, const Type& a, const Type& b, const std::string& ctx) {
    if (a != b) {
        semantic_error(tm, line, "Type mismatch (" + ctx + "): left is " + type_to_string(a) +
                               " but right is " + type_to_string(b) + " (no casting allowed)");
        return Type::Error();
    }
    return a;
}

ExprInfo* make_unary_expr(TableManager& tm, int line, const std::string& op, ExprInfo* a) {
    if (!a) return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);

    if (op == "!") {
        if (a->type.kind != Type::Kind::BOOL) {
            semantic_error(tm, line, "Operator '!' expects bool, got " + type_to_string(a->type));
            destroy_exprinfo(a);
            return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
        }
        ASTNode* n = ASTNode::unary(line, "!", Type::Bool(), a->node);
        a->node = nullptr;
        destroy_exprinfo(a);
        return wrap(n, Type::Bool(), line);
    }

    if (op == "u-") {
        if (!is_numeric(a->type)) {
            semantic_error(tm, line, "Unary '-' expects int/float, got " + type_to_string(a->type));
            destroy_exprinfo(a);
            return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
        }
        Type outT = a->type;
        ASTNode* n = ASTNode::unary(line, "u-", outT, a->node);
        a->node = nullptr;
        destroy_exprinfo(a);
        return wrap(n, outT, line);
    }

    destroy_exprinfo(a);
    return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
}

ExprInfo* make_binary_expr(TableManager& tm, int line, const std::string& op, ExprInfo* a, ExprInfo* b) {
    if (!a || !b) {
        if (a) destroy_exprinfo(a);
        if (b) destroy_exprinfo(b);
        return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
    }

    Type same = ensure_same_type_or_error(tm, line, a->type, b->type, "binary '" + op + "'");
    if (same.kind == Type::Kind::ERROR) {
        destroy_exprinfo(a);
        destroy_exprinfo(b);
        return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
    }

    Type outT = Type::Error();

    if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%") {
        if (!is_numeric(same)) {
            semantic_error(tm, line, "Arithmetic operator '" + op + "' expects numeric operands, got " + type_to_string(same));
            destroy_exprinfo(a); destroy_exprinfo(b);
            return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
        }
        if (op == "%" && same.kind != Type::Kind::INT) {
            semantic_error(tm, line, "Operator '%' only allowed for int operands");
            destroy_exprinfo(a); destroy_exprinfo(b);
            return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
        }
        outT = same;
    } else if (op == "==" || op == "!=" || op == "<" || op == "<=" || op == ">" || op == ">=") {
        if ((op == "<" || op == "<=" || op == ">" || op == ">=") && !is_numeric(same)) {
            semantic_error(tm, line, "Relational operator '" + op + "' expects numeric operands, got " + type_to_string(same));
            destroy_exprinfo(a); destroy_exprinfo(b);
            return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
        }
        outT = Type::Bool();
    } else if (op == "&&" || op == "||") {
        if (same.kind != Type::Kind::BOOL) {
            semantic_error(tm, line, "Logical operator '" + op + "' expects bool operands, got " + type_to_string(same));
            destroy_exprinfo(a); destroy_exprinfo(b);
            return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
        }
        outT = Type::Bool();
    } else {
        semantic_error(tm, line, "Unknown binary operator '" + op + "'");
        destroy_exprinfo(a); destroy_exprinfo(b);
        return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
    }

    ASTNode* n = ASTNode::binary(line, op, outT, a->node, b->node);
    a->node = nullptr; b->node = nullptr;
    destroy_exprinfo(a); destroy_exprinfo(b);
    return wrap(n, outT, line);
}

// Calls / field / new => OTHER leaf per spec, with semantic checks.

static void check_call_args(TableManager& tm, int line, const std::string& callable, const std::vector<Type>& expected, const std::vector<Arg>& got) {
    if (expected.size() != got.size()) {
        semantic_error(tm, line, "Call to '" + callable + "' expects " + std::to_string(expected.size()) +
                                 " args but got " + std::to_string(got.size()));
        return;
    }
    for (size_t i = 0; i < expected.size() && i < got.size(); i++) {
        if (expected[i] != got[i].type) {
            semantic_error(tm, got[i].line,
                "Call to '" + callable + "' arg " + std::to_string(i+1) + " type mismatch: expected " +
                type_to_string(expected[i]) + " but got " + type_to_string(got[i].type));
        }
    }
}

ExprInfo* make_other_from_func_call(TableManager& tm, int line, const std::string& funcName, const ArgList& args) {
    const FuncInfo* f = tm.lookup_func(funcName);
    if (!f) {
        semantic_error(tm, line, "Function '" + funcName + "' is not defined");
        return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
    }
    check_call_args(tm, line, funcName, f->paramTypes, args.v);
    return wrap(ASTNode::other(line, f->retType), f->retType, line);
}

ExprInfo* make_other_from_method_call(TableManager& tm, int line, const ExprInfo& receiver, const std::string& methodName, const ArgList& args) {
    if (receiver.type.kind != Type::Kind::CLASS) {
        semantic_error(tm, line, "Method call on non-class receiver of type " + type_to_string(receiver.type));
        return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
    }
    const ClassInfo* c = tm.lookup_class(receiver.type.className);
    if (!c) {
        semantic_error(tm, line, "Unknown class '" + receiver.type.className + "' for method call");
        return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
    }
    auto it = c->methods.find(methodName);
    if (it == c->methods.end()) {
        semantic_error(tm, line, "Class '" + c->name + "' has no method '" + methodName + "'");
        return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
    }
    check_call_args(tm, line, receiver.type.className + "." + methodName, it->second.paramTypes, args.v);
    return wrap(ASTNode::other(line, it->second.retType), it->second.retType, line);
}

ExprInfo* make_other_from_field_access(TableManager& tm, int line, const ExprInfo& receiver, const std::string& fieldName) {
    if (receiver.type.kind != Type::Kind::CLASS) {
        semantic_error(tm, line, "Field access on non-class receiver of type " + type_to_string(receiver.type));
        return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
    }
    const ClassInfo* c = tm.lookup_class(receiver.type.className);
    if (!c) {
        semantic_error(tm, line, "Unknown class '" + receiver.type.className + "' for field access");
        return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
    }
    auto it = c->fields.find(fieldName);
    if (it == c->fields.end()) {
        semantic_error(tm, line, "Class '" + c->name + "' has no field '" + fieldName + "'");
        return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
    }
    return wrap(ASTNode::other(line, it->second), it->second, line);
}

ExprInfo* make_other_from_object_new(TableManager& tm, int line, const std::string& className) {
    const ClassInfo* c = tm.lookup_class(className);
    if (!c) {
        semantic_error(tm, line, "Cannot summon unknown class '" + className + "'");
        return wrap(ASTNode::other(line, Type::Error()), Type::Error(), line);
    }
    Type t = Type::Class(className);
    return wrap(ASTNode::other(line, t), t, line);
}

// -------- Arg/Param lists --------

ArgList* arglist_empty() { return new ArgList(); }

ArgList* arglist_single(ExprInfo* e) {
    auto* a = new ArgList();
    if (e) {
        a->v.push_back(Arg{e->type, e->line});
        destroy_exprinfo(e); // keep only types for calls
    }
    return a;
}

ArgList* arglist_append(ArgList* xs, ExprInfo* e) {
    if (!xs) xs = new ArgList();
    if (e) {
        xs->v.push_back(Arg{e->type, e->line});
        destroy_exprinfo(e);
    }
    return xs;
}

ParamList* paramlist_empty() { return new ParamList(); }

ParamList* paramlist_single(const std::string& name, const Type& t, int line) {
    auto* p = new ParamList();
    p->v.push_back(Param{name, t, line});
    return p;
}

ParamList* paramlist_append(ParamList* xs, const std::string& name, const Type& t, int line) {
    if (!xs) xs = new ParamList();
    xs->v.push_back(Param{name, t, line});
    return xs;
}

void destroy_exprinfo(ExprInfo* e) {
    if (!e) return;
    if (e->node) delete e->node;
    delete e;
}
void destroy_arglist(ArgList* a) { delete a; }
void destroy_paramlist(ParamList* p) { delete p; }

// -------- Entry point --------
extern int yyparse();
extern FILE* yyin;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: miku <file.miku>\n";
        return 2;
    }
    yyin = std::fopen(argv[1], "r");
    if (!yyin) {
        std::perror("fopen");
        return 2;
    }

    int rc = yyparse();
    std::fclose(yyin);

    // Always dump tables (even on errors), per spec.
    g_tm.dump_all_tables("tables.txt");

    if (rc != 0) {
        std::cerr << "[parse] failed.\n";
        return 1;
    }
    if (g_tm.hadSemanticErrors) {
        std::cerr << "[semantic] completed with errors.\n";
        return 1;
    }

    return 0;
}
