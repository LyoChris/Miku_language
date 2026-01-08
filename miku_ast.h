#pragma once
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>
#include <variant>
#include <stdexcept>
#include <iostream>

/*
  Rust-like Miku language:

    Primitives:
      leek   -> int64
      rin    -> double
      scroll -> std::string
      code   -> bool
      ghost  -> void-like

    Structs:
      MikuData Name { field: type; track method(...) -> type { ... } };
      instance:
        Name { field: expr, ... }
        summon Name()
      field access:
        obj.field
      method call:
        obj.method(args...)
      inside methods: implicit 'self' variable bound to the object.
*/

struct RuntimeError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct Type {
    enum class Kind { Leek, Rin, Scroll, Code, Ghost, Struct, Error };
    Kind kind{Kind::Error};
    std::string name;

    static Type Leek()   { return {Kind::Leek,   ""}; }
    static Type Rin()    { return {Kind::Rin,    ""}; }
    static Type Scroll() { return {Kind::Scroll, ""}; }
    static Type Code()   { return {Kind::Code,   ""}; }
    static Type Ghost()  { return {Kind::Ghost,  ""}; }
    static Type Struct(std::string n) { return {Kind::Struct, std::move(n)}; }
    static Type Error()  { return {Kind::Error,  ""}; }

    bool operator==(const Type& o) const { return kind == o.kind && name == o.name; }
    bool operator!=(const Type& o) const { return !(*this == o); }
};

inline std::string type_name(const Type& t) {
    switch (t.kind) {
        case Type::Kind::Leek:   return "leek";
        case Type::Kind::Rin:    return "rin";
        case Type::Kind::Scroll: return "scroll";
        case Type::Kind::Code:   return "code";
        case Type::Kind::Ghost:  return "ghost";
        case Type::Kind::Struct: return t.name;
        default: return "error";
    }
}

struct Object;

struct Value {
    Type ty{Type::Error()};
    std::variant<int64_t, double, std::string, bool, std::shared_ptr<Object>> v;

    static Value leek(int64_t x){ Value r; r.ty=Type::Leek(); r.v=x; return r; }
    static Value rin(double x){ Value r; r.ty=Type::Rin(); r.v=x; return r; }
    static Value scroll(std::string s){ Value r; r.ty=Type::Scroll(); r.v=std::move(s); return r; }
    static Value code(bool b){ Value r; r.ty=Type::Code(); r.v=b; return r; }
    static Value ghost(){ Value r; r.ty=Type::Ghost(); r.v=false; return r; }
    static Value obj(std::string struct_name, std::shared_ptr<Object> o);
};

inline std::string value_to_string(const Value& val) {
    if (val.ty.kind == Type::Kind::Leek)   return std::to_string(std::get<int64_t>(val.v));
    if (val.ty.kind == Type::Kind::Rin)    { char buf[128]; std::snprintf(buf, sizeof(buf), "%g", std::get<double>(val.v)); return buf; }
    if (val.ty.kind == Type::Kind::Scroll) return std::get<std::string>(val.v);
    if (val.ty.kind == Type::Kind::Code)   return std::get<bool>(val.v) ? "true" : "false";
    if (val.ty.kind == Type::Kind::Ghost)  return "";
    if (val.ty.kind == Type::Kind::Struct) return "<" + val.ty.name + ">";
    return "<error>";
}

struct FieldDef {
    std::string name;
    Type ty;
};

struct Param {
    std::string name;
    Type ty;
};

struct Expr;
struct Stmt;
struct Block;

using ExprPtr  = std::unique_ptr<Expr>;
using StmtPtr  = std::unique_ptr<Stmt>;
using BlockPtr = std::unique_ptr<Block>;

struct Function {
    std::string name;
    std::vector<Param> params;
    Type ret{Type::Error()};
    BlockPtr body;

    bool is_method{false};
    std::string receiver;
};

struct StructDef {
    std::string name;
    std::vector<FieldDef> fields;
    std::unordered_map<std::string, std::unique_ptr<Function>> methods;

    const FieldDef* find_field(const std::string& f) const {
        for (auto& x : fields) if (x.name == f) return &x;
        return nullptr;
    }
};

struct Program {
    std::vector<std::unique_ptr<StructDef>> structs;
    std::vector<std::unique_ptr<Function>> funcs;

    std::unordered_map<std::string, StructDef*> struct_map;
    std::unordered_map<std::string, Function*> func_map;

    void index() {
        struct_map.clear();
        func_map.clear();
        for (auto& s : structs) struct_map[s->name] = s.get();
        for (auto& f : funcs)   func_map[f->name] = f.get();
    }

    StructDef* get_struct(const std::string& n) const {
        auto it = struct_map.find(n);
        return (it == struct_map.end()) ? nullptr : it->second;
    }

    Function* get_func(const std::string& n) const {
        auto it = func_map.find(n);
        return (it == func_map.end()) ? nullptr : it->second;
    }

    Function* get_method(const std::string& recv, const std::string& m) const {
        StructDef* sd = get_struct(recv);
        if (!sd) return nullptr;
        auto it = sd->methods.find(m);
        return (it == sd->methods.end()) ? nullptr : it->second.get();
    }
};

struct Ctx {
    Program* prog{nullptr};
};


struct Object {
    std::string struct_name;
    std::unordered_map<std::string, Value> fields;

    explicit Object(std::string n) : struct_name(std::move(n)) {}
};

inline Value Value::obj(std::string struct_name, std::shared_ptr<Object> o) {
    Value r;
    r.ty = Type::Struct(struct_name);
    r.v = std::move(o);
    return r;
}

struct ReturnSignal {
    Value value;
};

struct Env {
    std::unordered_map<std::string, Value> vars;
    Env* parent{nullptr};

    explicit Env(Env* p=nullptr) : parent(p) {}

    Value get(const std::string& k) const {
        for (const Env* e=this; e; e=e->parent) {
            auto it = e->vars.find(k);
            if (it != e->vars.end()) return it->second;
        }
        throw RuntimeError("Undefined variable: " + k);
    }

    void define(const std::string& k, const Value& val) {
    if (vars.find(k) != vars.end()) {
        throw RuntimeError("Redeclaration in same scope: " + k);
    }
    vars.emplace(k, val);
}

    void set_existing(const std::string& k, const Value& val) {
        for (Env* e=this; e; e=e->parent) {
            auto it = e->vars.find(k);
            if (it != e->vars.end()) {
                if (it->second.ty != val.ty) {
                    throw RuntimeError("Assign type mismatch to '" + k + "': " +
                                       type_name(it->second.ty) + " vs " + type_name(val.ty));
                }
                it->second = val;
                return;
            }
        }
        throw RuntimeError("Assign to undefined variable: " + k);
    }
};


inline Value default_value(const Type& t, const Program& p) {
    switch (t.kind) {
        case Type::Kind::Leek:   return Value::leek(0);
        case Type::Kind::Rin:    return Value::rin(0.0);
        case Type::Kind::Scroll: return Value::scroll("");
        case Type::Kind::Code:   return Value::code(false);
        case Type::Kind::Ghost:  return Value::ghost();
        case Type::Kind::Struct: {
            auto* sd = p.get_struct(t.name);
            if (!sd) throw RuntimeError("Unknown struct type: " + t.name);
            auto obj = std::make_shared<Object>(t.name);
            for (auto& f : sd->fields) obj->fields[f.name] = default_value(f.ty, p);
            return Value::obj(t.name, obj);
        }
        default: return Value::ghost();
    }
}


struct Expr {
    int line{0};
    explicit Expr(int ln): line(ln) {}
    virtual ~Expr() = default;
    virtual Value eval(Ctx& ctx, Env& env) const = 0;
};

struct ExprInt : Expr {
    int64_t x;
    ExprInt(int ln, int64_t v): Expr(ln), x(v) {}
    Value eval(Ctx&, Env&) const override { return Value::leek(x); }
};

struct ExprFloat : Expr {
    double x;
    ExprFloat(int ln, double v): Expr(ln), x(v) {}
    Value eval(Ctx&, Env&) const override { return Value::rin(x); }
};

struct ExprBool : Expr {
    bool x;
    ExprBool(int ln, bool v): Expr(ln), x(v) {}
    Value eval(Ctx&, Env&) const override { return Value::code(x); }
};

struct ExprString : Expr {
    std::string s;
    ExprString(int ln, std::string v): Expr(ln), s(std::move(v)) {}
    Value eval(Ctx&, Env&) const override { return Value::scroll(s); }
};

struct ExprVar : Expr {
    std::string name;
    ExprVar(int ln, std::string n): Expr(ln), name(std::move(n)) {}
    Value eval(Ctx&, Env& env) const override { return env.get(name); }
};

enum class BinOp {
    Add, Sub, Mul, Div, Mod,
    Eq, Neq, Lt, Le, Gt, Ge,
    And, Or
};

enum class UnOp { Neg, Not };

inline void type_err(int ln, const std::string& msg) {
    throw RuntimeError("Line " + std::to_string(ln) + ": " + msg);
}

struct ExprUn : Expr {
    UnOp op;
    ExprPtr e;
    ExprUn(int ln, UnOp o, ExprPtr x): Expr(ln), op(o), e(std::move(x)) {}

    Value eval(Ctx& ctx, Env& env) const override {
        Value v = e->eval(ctx, env);
        if (op == UnOp::Not) {
            if (v.ty.kind != Type::Kind::Code) type_err(line, "! expects code");
            return Value::code(!std::get<bool>(v.v));
        }
        if (op == UnOp::Neg) {
            if (v.ty.kind == Type::Kind::Leek) return Value::leek(-std::get<int64_t>(v.v));
            if (v.ty.kind == Type::Kind::Rin)  return Value::rin(-std::get<double>(v.v));
            type_err(line, "unary - expects leek or rin");
        }
        return Value::ghost();
    }
};

struct ExprBin : Expr {
    BinOp op;
    ExprPtr a, b;
    ExprBin(int ln, BinOp o, ExprPtr x, ExprPtr y): Expr(ln), op(o), a(std::move(x)), b(std::move(y)) {}

    Value eval(Ctx& ctx, Env& env) const override {
        Value va = a->eval(ctx, env);
        Value vb = b->eval(ctx, env);

        auto need = [&](Type::Kind k, const char* msg){
            if (va.ty.kind != k || vb.ty.kind != k) type_err(line, msg);
        };

        switch (op) {
            case BinOp::Add:
                if (va.ty.kind==Type::Kind::Leek && vb.ty.kind==Type::Kind::Leek)
                    return Value::leek(std::get<int64_t>(va.v)+std::get<int64_t>(vb.v));
                if (va.ty.kind==Type::Kind::Rin && vb.ty.kind==Type::Kind::Rin)
                    return Value::rin(std::get<double>(va.v)+std::get<double>(vb.v));
                if (va.ty.kind==Type::Kind::Scroll && vb.ty.kind==Type::Kind::Scroll)
                    return Value::scroll(std::get<std::string>(va.v)+std::get<std::string>(vb.v));
                type_err(line, "type mismatch for +");
                break;

            case BinOp::Sub:
                if (va.ty.kind==Type::Kind::Leek && vb.ty.kind==Type::Kind::Leek)
                    return Value::leek(std::get<int64_t>(va.v)-std::get<int64_t>(vb.v));
                if (va.ty.kind==Type::Kind::Rin && vb.ty.kind==Type::Kind::Rin)
                    return Value::rin(std::get<double>(va.v)-std::get<double>(vb.v));
                type_err(line, "type mismatch for -");
                break;

            case BinOp::Mul:
                if (va.ty.kind==Type::Kind::Leek && vb.ty.kind==Type::Kind::Leek)
                    return Value::leek(std::get<int64_t>(va.v)*std::get<int64_t>(vb.v));
                if (va.ty.kind==Type::Kind::Rin && vb.ty.kind==Type::Kind::Rin)
                    return Value::rin(std::get<double>(va.v)*std::get<double>(vb.v));
                type_err(line, "type mismatch for *");
                break;

            case BinOp::Div:
                if (va.ty.kind==Type::Kind::Leek && vb.ty.kind==Type::Kind::Leek)
                    return Value::leek(std::get<int64_t>(va.v)/std::get<int64_t>(vb.v));
                if (va.ty.kind==Type::Kind::Rin && vb.ty.kind==Type::Kind::Rin)
                    return Value::rin(std::get<double>(va.v)/std::get<double>(vb.v));
                type_err(line, "type mismatch for /");
                break;

            case BinOp::Mod:
                need(Type::Kind::Leek, "% expects leek operands");
                return Value::leek(std::get<int64_t>(va.v) % std::get<int64_t>(vb.v));

            case BinOp::Eq:
                if (va.ty != vb.ty) return Value::code(false);
                if (va.ty.kind==Type::Kind::Leek)   return Value::code(std::get<int64_t>(va.v)==std::get<int64_t>(vb.v));
                if (va.ty.kind==Type::Kind::Rin)    return Value::code(std::get<double>(va.v)==std::get<double>(vb.v));
                if (va.ty.kind==Type::Kind::Scroll) return Value::code(std::get<std::string>(va.v)==std::get<std::string>(vb.v));
                if (va.ty.kind==Type::Kind::Code)   return Value::code(std::get<bool>(va.v)==std::get<bool>(vb.v));
                if (va.ty.kind==Type::Kind::Struct) return Value::code(std::get<std::shared_ptr<Object>>(va.v) == std::get<std::shared_ptr<Object>>(vb.v));
                return Value::code(false);

            case BinOp::Neq:
                if (va.ty != vb.ty) return Value::code(true);
                if (va.ty.kind==Type::Kind::Leek)   return Value::code(std::get<int64_t>(va.v)!=std::get<int64_t>(vb.v));
                if (va.ty.kind==Type::Kind::Rin)    return Value::code(std::get<double>(va.v)!=std::get<double>(vb.v));
                if (va.ty.kind==Type::Kind::Scroll) return Value::code(std::get<std::string>(va.v)!=std::get<std::string>(vb.v));
                if (va.ty.kind==Type::Kind::Code)   return Value::code(std::get<bool>(va.v)!=std::get<bool>(vb.v));
                if (va.ty.kind==Type::Kind::Struct) return Value::code(std::get<std::shared_ptr<Object>>(va.v) != std::get<std::shared_ptr<Object>>(vb.v));
                return Value::code(true);

            case BinOp::Lt:
                if (va.ty.kind==Type::Kind::Leek && vb.ty.kind==Type::Kind::Leek) return Value::code(std::get<int64_t>(va.v) < std::get<int64_t>(vb.v));
                if (va.ty.kind==Type::Kind::Rin && vb.ty.kind==Type::Kind::Rin)   return Value::code(std::get<double>(va.v) < std::get<double>(vb.v));
                type_err(line, "< expects leek/rin operands");
                break;

            case BinOp::Le:
                if (va.ty.kind==Type::Kind::Leek && vb.ty.kind==Type::Kind::Leek) return Value::code(std::get<int64_t>(va.v) <= std::get<int64_t>(vb.v));
                if (va.ty.kind==Type::Kind::Rin && vb.ty.kind==Type::Kind::Rin)   return Value::code(std::get<double>(va.v) <= std::get<double>(vb.v));
                type_err(line, "<= expects leek/rin operands");
                break;

            case BinOp::Gt:
                if (va.ty.kind==Type::Kind::Leek && vb.ty.kind==Type::Kind::Leek) return Value::code(std::get<int64_t>(va.v) > std::get<int64_t>(vb.v));
                if (va.ty.kind==Type::Kind::Rin && vb.ty.kind==Type::Kind::Rin)   return Value::code(std::get<double>(va.v) > std::get<double>(vb.v));
                type_err(line, "> expects leek/rin operands");
                break;

            case BinOp::Ge:
                if (va.ty.kind==Type::Kind::Leek && vb.ty.kind==Type::Kind::Leek) return Value::code(std::get<int64_t>(va.v) >= std::get<int64_t>(vb.v));
                if (va.ty.kind==Type::Kind::Rin && vb.ty.kind==Type::Kind::Rin)   return Value::code(std::get<double>(va.v) >= std::get<double>(vb.v));
                type_err(line, ">= expects leek/rin operands");
                break;

            case BinOp::And:
                need(Type::Kind::Code, "&& expects code operands");
                return Value::code(std::get<bool>(va.v) && std::get<bool>(vb.v));

            case BinOp::Or:
                need(Type::Kind::Code, "|| expects code operands");
                return Value::code(std::get<bool>(va.v) || std::get<bool>(vb.v));
        }

        type_err(line, "unknown binary op");
        return Value::ghost();
    }
};

struct ExprCall : Expr {
    std::string name;
    std::vector<ExprPtr> args;
    ExprCall(int ln, std::string n, std::vector<ExprPtr> a)
        : Expr(ln), name(std::move(n)), args(std::move(a)) {}
    Value eval(Ctx& ctx, Env& env) const override;
};

struct ExprField : Expr {
    ExprPtr base;
    std::string field;
    ExprField(int ln, ExprPtr b, std::string f)
        : Expr(ln), base(std::move(b)), field(std::move(f)) {}
    Value eval(Ctx& ctx, Env& env) const override {
        Value objv = base->eval(ctx, env);
        if (objv.ty.kind != Type::Kind::Struct) type_err(line, "field access requires struct");
        auto o = std::get<std::shared_ptr<Object>>(objv.v);
        auto it = o->fields.find(field);
        if (it == o->fields.end()) type_err(line, "unknown field '" + field + "'");
        return it->second;
    }
};

struct ExprMethodCall : Expr {
    ExprPtr recv;
    std::string method;
    std::vector<ExprPtr> args;
    ExprMethodCall(int ln, ExprPtr r, std::string m, std::vector<ExprPtr> a)
        : Expr(ln), recv(std::move(r)), method(std::move(m)), args(std::move(a)) {}
    Value eval(Ctx& ctx, Env& env) const override;
};

struct FieldInit {
    std::string name;
    ExprPtr expr;
};

struct ExprStructLit : Expr {
    std::string struct_name;
    std::vector<FieldInit> inits;
    ExprStructLit(int ln, std::string n, std::vector<FieldInit> fi)
        : Expr(ln), struct_name(std::move(n)), inits(std::move(fi)) {}
    Value eval(Ctx& ctx, Env& env) const override {
        auto* sd = ctx.prog->get_struct(struct_name);
        if (!sd) type_err(line, "unknown struct: " + struct_name);

        auto obj = std::make_shared<Object>(struct_name);
        for (auto& f : sd->fields) obj->fields[f.name] = default_value(f.ty, *ctx.prog);

        for (auto& it : inits) {
            const FieldDef* fd = sd->find_field(it.name);
            if (!fd) type_err(line, "unknown field '" + it.name + "' in " + struct_name);
            Value v = it.expr->eval(ctx, env);
            if (v.ty != fd->ty) type_err(line, "field '" + it.name + "' type mismatch: expected " + type_name(fd->ty) + " got " + type_name(v.ty));
            obj->fields[it.name] = v;
        }

        return Value::obj(struct_name, obj);
    }
};

struct ExprSummon : Expr {
    std::string struct_name;
    ExprSummon(int ln, std::string n): Expr(ln), struct_name(std::move(n)) {}
    Value eval(Ctx& ctx, Env&) const override {
        auto* sd = ctx.prog->get_struct(struct_name);
        if (!sd) type_err(line, "unknown struct: " + struct_name);
        auto obj = std::make_shared<Object>(struct_name);
        for (auto& f : sd->fields) obj->fields[f.name] = default_value(f.ty, *ctx.prog);
        return Value::obj(struct_name, obj);
    }
};


struct Stmt {
    int line{0};
    explicit Stmt(int ln): line(ln) {}
    virtual ~Stmt() = default;
    virtual void exec(Ctx& ctx, Env& env) const = 0;
};

struct Block {
    int line{0};
    std::vector<StmtPtr> stmts;
    explicit Block(int ln): line(ln) {}
    void exec(Ctx& ctx, Env& env) const {
        for (auto& s : stmts) s->exec(ctx, env);
    }
};

// helper
inline bool env_is_main(const Env& env) {
    for (const Env* e = &env; e; e = e->parent) {
        if (e->vars.find("__miku_main__") != e->vars.end()) return true;
    }
    return false;
}


struct StmtLet : Stmt {
    std::string name;
    std::optional<Type> ann;
    ExprPtr init;
    StmtLet(int ln, std::string n, std::optional<Type> a, ExprPtr i)
        : Stmt(ln), name(std::move(n)), ann(std::move(a)), init(std::move(i)) {}

    void exec(Ctx& ctx, Env& env) const override {
    // Spec: no declarations in main block
    if (env_is_main(env)) {
        throw RuntimeError("Line " + std::to_string(line) +
                           ": variable declarations are not allowed in main block");
    }


    if (env.parent != nullptr) {
        throw RuntimeError("Line " + std::to_string(line) +
                           ": variable declarations are not allowed inside statement blocks");
    }

    Value v = init->eval(ctx, env);
    if (ann.has_value() && v.ty != *ann) {
        throw RuntimeError("Line " + std::to_string(line) + ": let " + name +
                           " expected " + type_name(*ann) + " got " + type_name(v.ty));
    }

    env.define(name, v);
}

};

struct LValue {
    int line{0};
    std::vector<std::string> parts;
};

inline std::shared_ptr<Object> lvalue_get_obj(Ctx& ctx, Env& env, const LValue& lv) {
    (void)ctx;

    if (lv.parts.size() < 2) type_err(lv.line, "internal: expected field lvalue");
    Value cur = env.get(lv.parts[0]);
    if (cur.ty.kind != Type::Kind::Struct) type_err(lv.line, "lvalue base must be struct");
    auto obj = std::get<std::shared_ptr<Object>>(cur.v);

    for (size_t i=1; i+1<lv.parts.size(); i++) {
        auto it = obj->fields.find(lv.parts[i]);
        if (it == obj->fields.end()) type_err(lv.line, "unknown field '" + lv.parts[i] + "'");
        cur = it->second;
        if (cur.ty.kind != Type::Kind::Struct) type_err(lv.line, "intermediate field is not a struct");
        obj = std::get<std::shared_ptr<Object>>(cur.v);
    }
    return obj;
}

struct StmtAssign : Stmt {
    std::unique_ptr<LValue> lv;
    ExprPtr rhs;

    StmtAssign(int ln, std::unique_ptr<LValue> l, ExprPtr r)
        : Stmt(ln), lv(std::move(l)), rhs(std::move(r)) {}

    void exec(Ctx& ctx, Env& env) const override {
        Value v = rhs->eval(ctx, env);

        if (lv->parts.size() == 1) {
            env.set_existing(lv->parts[0], v);
            return;
        }

        auto obj = lvalue_get_obj(ctx, env, *lv);
        const std::string& field = lv->parts.back();
        auto it = obj->fields.find(field);
        if (it == obj->fields.end()) type_err(line, "unknown field '" + field + "'");
        if (it->second.ty != v.ty) type_err(line, "field '" + field + "' type mismatch: " + type_name(it->second.ty) + " vs " + type_name(v.ty));
        obj->fields[field] = v;
    }
};

struct StmtPrint : Stmt {
    ExprPtr e;
    StmtPrint(int ln, ExprPtr x): Stmt(ln), e(std::move(x)) {}
    void exec(Ctx& ctx, Env& env) const override {
        Value v = e->eval(ctx, env);
        std::cout << "[Miku Says]: " << value_to_string(v) << "\n";
        std::cout.flush();
    }
};

struct StmtExpr : Stmt {
    ExprPtr e;
    StmtExpr(int ln, ExprPtr x): Stmt(ln), e(std::move(x)) {}
    void exec(Ctx& ctx, Env& env) const override { (void)e->eval(ctx, env); }
};

struct StmtIf : Stmt {
    ExprPtr cond;
    std::unique_ptr<Block> then_b;
    std::unique_ptr<Block> else_b;
    StmtIf(int ln, ExprPtr c, std::unique_ptr<Block> t, std::unique_ptr<Block> e)
        : Stmt(ln), cond(std::move(c)), then_b(std::move(t)), else_b(std::move(e)) {}
    void exec(Ctx& ctx, Env& env) const override {
        Value v = cond->eval(ctx, env);
        if (v.ty.kind != Type::Kind::Code) type_err(line, "wish condition must be code");
        Env child(&env);
        if (std::get<bool>(v.v)) then_b->exec(ctx, child);
        else if (else_b) else_b->exec(ctx, child);
    }
};

struct StmtWhile : Stmt {
    ExprPtr cond;
    std::unique_ptr<Block> body;
    StmtWhile(int ln, ExprPtr c, std::unique_ptr<Block> b): Stmt(ln), cond(std::move(c)), body(std::move(b)) {}
    void exec(Ctx& ctx, Env& env) const override {
        while (true) {
            Value v = cond->eval(ctx, env);
            if (v.ty.kind != Type::Kind::Code) type_err(line, "rolling condition must be code");
            if (!std::get<bool>(v.v)) break;
            Env child(&env);
            body->exec(ctx, child);
        }
    }
};

struct StmtReturn : Stmt {
    std::optional<ExprPtr> e;
    StmtReturn(int ln, std::optional<ExprPtr> ex): Stmt(ln), e(std::move(ex)) {}
    void exec(Ctx& ctx, Env& env) const override {
        if (!e.has_value()) throw ReturnSignal{Value::ghost()};
        Value v = (*e)->eval(ctx, env);
        throw ReturnSignal{v};
    }
};


inline Value call_function(Ctx& ctx, const Function& fn, const std::vector<Value>& args, int line, std::optional<Value> self_opt) {
    if (args.size() != fn.params.size()) {
        throw RuntimeError("Line " + std::to_string(line) + ": arity mismatch calling " + fn.name);
    }

    Env local(nullptr);

    if (fn.name == "world_is_mine") {
        local.define("__miku_main__", Value::code(true));
    }

    if (fn.is_method) {
        if (!self_opt.has_value()) throw RuntimeError("Line " + std::to_string(line) + ": method call missing self");
        local.define("self", *self_opt);
    }

    for (size_t i=0; i<args.size(); i++) {
        if (args[i].ty != fn.params[i].ty) {
            throw RuntimeError("Line " + std::to_string(line) + ": param type mismatch in call to " + fn.name);
        }
        local.define(fn.params[i].name, args[i]);
    }

    try {
        fn.body->exec(ctx, local);
        return default_value(fn.ret, *ctx.prog);
    } catch (const ReturnSignal& r) {
        if (fn.ret.kind == Type::Kind::Ghost) return Value::ghost();
        if (r.value.ty != fn.ret) {
            throw RuntimeError("Line " + std::to_string(line) + ": return type mismatch in " + fn.name +
                               ": expected " + type_name(fn.ret) + " got " + type_name(r.value.ty));
        }
        return r.value;
    }
}

inline Value ExprCall::eval(Ctx& ctx, Env& env) const {
    std::vector<Value> vals;
    vals.reserve(args.size());
    for (auto& a : args) vals.push_back(a->eval(ctx, env));

    Function* fn = ctx.prog->get_func(name);
    if (!fn) throw RuntimeError("Line " + std::to_string(line) + ": unknown function: " + name);
    if (fn->is_method) throw RuntimeError("Line " + std::to_string(line) + ": method '" + name + "' must be called with receiver");
    return call_function(ctx, *fn, vals, line, std::nullopt);
}

inline Value ExprMethodCall::eval(Ctx& ctx, Env& env) const {
    Value recv_v = recv->eval(ctx, env);
    if (recv_v.ty.kind != Type::Kind::Struct) type_err(line, "method call requires struct receiver");
    std::string recv_name = recv_v.ty.name;

    std::vector<Value> vals;
    vals.reserve(args.size());
    for (auto& a : args) vals.push_back(a->eval(ctx, env));

    Function* fn = ctx.prog->get_method(recv_name, method);
    if (!fn) throw RuntimeError("Line " + std::to_string(line) + ": unknown method '" + method + "' for " + recv_name);
    return call_function(ctx, *fn, vals, line, recv_v);
}
