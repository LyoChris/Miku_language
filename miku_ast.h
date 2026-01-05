#pragma once
/*
  Miku Language — spec-compliant implementation for:
  - Symbol tables (global/function/class scopes) printed to tables.txt
  - Semantic checks:
      * member exists on class instance (field/method)
      * identifiers used must be previously defined
      * no casting: operands in expression must have same type
      * assignment LHS type == RHS type
      * call args types match function/method signature
      * detailed errors with line numbers
  - AST construction + evaluation:
      * expression AST
      * statement AST ONLY for:
          - assignment: ID := expr;
          - Print(expr): tell_your_world(expr);
        other statements => NULL AST
      * main block evaluation: evaluate each non-NULL statement AST
  - IMPORTANT per spec:
      * any function call / method call / field access / object creation used as an expression operand
        becomes a single leaf node labeled OTHER
      * OTHER evaluates to default value for its type
*/

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <variant>
#include <optional>
#include <sstream>
#include <fstream>

struct Type {
    enum class Kind { INT, FLOAT, BOOL, STRING, CLASS, VOID, ERROR } kind = Kind::ERROR;
    std::string className; // only when kind == CLASS

    static Type Int()   { return {Kind::INT,   ""}; }
    static Type Float() { return {Kind::FLOAT, ""}; }
    static Type Bool()  { return {Kind::BOOL,  ""}; }
    static Type String(){ return {Kind::STRING,""}; }
    static Type Void()  { return {Kind::VOID,  ""}; }
    static Type Error() { return {Kind::ERROR, ""}; }
    static Type Class(std::string n) { Type t; t.kind = Kind::CLASS; t.className = std::move(n); return t; }

    bool operator==(const Type& o) const {
        if (kind != o.kind) return false;
        if (kind == Kind::CLASS) return className == o.className;
        return true;
    }
    bool operator!=(const Type& o) const { return !(*this == o); }
};

inline std::string type_to_string(const Type& t) {
    switch (t.kind) {
        case Type::Kind::INT: return "int";
        case Type::Kind::FLOAT: return "float";
        case Type::Kind::BOOL: return "bool";
        case Type::Kind::STRING: return "string";
        case Type::Kind::VOID: return "void";
        case Type::Kind::ERROR: return "error";
        case Type::Kind::CLASS: return "class(" + t.className + ")";
    }
    return "error";
}

// For CLASS values we store a placeholder (std::monostate). No runtime objects per spec.
struct Value {
    using Storage = std::variant<int64_t, double, bool, std::string, std::monostate>;
    Storage v;

    static Value default_of(const Type& t) {
        switch (t.kind) {
            case Type::Kind::INT:    return Value{int64_t(0)};
            case Type::Kind::FLOAT:  return Value{double(0.0)};
            case Type::Kind::BOOL:   return Value{bool(false)};
            case Type::Kind::STRING: return Value{std::string("")};
            case Type::Kind::CLASS:  return Value{std::monostate{}};
            case Type::Kind::VOID:   return Value{std::monostate{}};
            default:                 return Value{std::monostate{}};
        }
    }

    std::string to_string(const Type& t) const {
        switch (t.kind) {
            case Type::Kind::INT:    return std::to_string(std::get<int64_t>(v));
            case Type::Kind::FLOAT:  {
                std::ostringstream oss;
                oss << std::get<double>(v);
                return oss.str();
            }
            case Type::Kind::BOOL:   return std::get<bool>(v) ? "true" : "false";
            case Type::Kind::STRING: return std::get<std::string>(v);
            case Type::Kind::CLASS:  return "<" + t.className + ">";
            case Type::Kind::VOID:   return "<void>";
            default:                 return "<error>";
        }
    }
};

struct VarInfo {
    std::string name;
    Type type;
    Value value;
    int declLine = 0;
};

struct FuncInfo {
    std::string name;
    Type retType;
    std::vector<Type> paramTypes;
    std::vector<std::string> paramNames;
    int declLine = 0;
};

struct ClassInfo {
    std::string name;
    std::unordered_map<std::string, Type> fields;
    std::unordered_map<std::string, FuncInfo> methods;
    int declLine = 0;
};

struct SymbolTable {
    std::string name;
    SymbolTable* parent = nullptr;

    std::unordered_map<std::string, VarInfo> vars;
    std::unordered_map<std::string, FuncInfo> funcs;

    SymbolTable(std::string n, SymbolTable* p): name(std::move(n)), parent(p) {}
};

struct TableManager {
    std::vector<std::unique_ptr<SymbolTable>> allTables;
    SymbolTable* global = nullptr;
    SymbolTable* current = nullptr;

    // Global class registry (spec)
    std::unordered_map<std::string, ClassInfo> classes;

    bool hadSemanticErrors = false;

    TableManager();

    SymbolTable* push_scope(const std::string& name);
    void pop_scope();

    void dump_all_tables(const std::string& path) const;

    const VarInfo* lookup_var(const std::string& name) const;
    VarInfo* lookup_var_mut(const std::string& name);
    const FuncInfo* lookup_func(const std::string& name) const;
    const ClassInfo* lookup_class(const std::string& name) const;
};

// -------- AST --------

enum class ASTKind {
    LIT_INT, LIT_FLOAT, LIT_BOOL, LIT_STRING,
    IDENT,
    OTHER,          // required by spec
    UNARY_OP,
    BINARY_OP,
    ASSIGN,         // statement AST
    PRINT           // statement AST
};

struct ASTNode {
    ASTKind kind;
    Type type;
    int line;

    std::string op;      // operators
    std::string name;    // IDENT / ASSIGN LHS
    Value lit;           // literals

    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    ASTNode(ASTKind k, Type t, int ln): kind(k), type(std::move(t)), line(ln) {}

    static ASTNode* lit_int(int ln, int64_t v);
    static ASTNode* lit_float(int ln, double v);
    static ASTNode* lit_bool(int ln, bool v);
    static ASTNode* lit_string(int ln, std::string v);

    static ASTNode* ident(int ln, std::string n, Type t);
    static ASTNode* other(int ln, Type t);

    static ASTNode* unary(int ln, std::string op, Type t, ASTNode* child);
    static ASTNode* binary(int ln, std::string op, Type t, ASTNode* l, ASTNode* r);

    static ASTNode* assign(int ln, std::string lhsName, Type lhsType, ASTNode* rhs);
    static ASTNode* print(int ln, ASTNode* expr);

    Value eval(TableManager& tm) const;
};

// -------- Parser wrappers --------
struct ExprInfo {
    ASTNode* node = nullptr;
    Type type = Type::Error();
    int line = 0;
};

struct Param {
    std::string name;
    Type type;
    int line = 0;
};

struct Arg {
    Type type;
    int line = 0;
};

struct ParamList { std::vector<Param> v; };
struct ArgList { std::vector<Arg> v; };

// -------- Semantic helpers --------
void semantic_error(TableManager& tm, int line, const std::string& msg);

Type resolve_type_name(TableManager& tm, int line, const std::string& typeName);

void declare_var(TableManager& tm, int line, const std::string& name, const Type& type, const std::optional<Value>& initValue, bool isGlobal);
void declare_func(TableManager& tm, int line, const std::string& name, const Type& ret, const ParamList& params);
void declare_method(TableManager& tm, int line, const std::string& className, const std::string& methodName, const Type& ret, const ParamList& params);
void declare_class_begin(TableManager& tm, int line, const std::string& className);
void declare_class_field(TableManager& tm, int line, const std::string& className, const std::string& fieldName, const Type& fieldType);
void declare_class_end(TableManager& tm);

ExprInfo* make_lit_int(int line, int64_t v);
ExprInfo* make_lit_float(int line, double v);
ExprInfo* make_lit_bool(int line, bool v);
ExprInfo* make_lit_string(int line, std::string v);
ExprInfo* make_ident(TableManager& tm, int line, const std::string& name);

ExprInfo* make_unary_expr(TableManager& tm, int line, const std::string& op, ExprInfo* a);
ExprInfo* make_binary_expr(TableManager& tm, int line, const std::string& op, ExprInfo* a, ExprInfo* b);

ExprInfo* make_other_from_func_call(TableManager& tm, int line, const std::string& funcName, const ArgList& args);
ExprInfo* make_other_from_method_call(TableManager& tm, int line, const ExprInfo& receiver, const std::string& methodName, const ArgList& args);
ExprInfo* make_other_from_field_access(TableManager& tm, int line, const ExprInfo& receiver, const std::string& fieldName);
ExprInfo* make_other_from_object_new(TableManager& tm, int line, const std::string& className);

ArgList* arglist_empty();
ArgList* arglist_single(ExprInfo* e);
ArgList* arglist_append(ArgList* xs, ExprInfo* e);

ParamList* paramlist_empty();
ParamList* paramlist_single(const std::string& name, const Type& t, int line);
ParamList* paramlist_append(ParamList* xs, const std::string& name, const Type& t, int line);

void destroy_exprinfo(ExprInfo* e);
void destroy_arglist(ArgList* a);
void destroy_paramlist(ParamList* p);

// Exposed global context used by parser actions (NOT an AST global).
extern TableManager g_tm;
