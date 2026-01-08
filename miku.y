%{
#include "miku_ast.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

extern int yylineno;
int yylex(void);
void yyerror(const char* s);

static Program* g_program = nullptr;
%}

%code requires {
#include "miku_ast.h"
#include <string>
#include <vector>


struct LValTmp {
    int line{0};
    std::vector<std::string> parts;
};

struct FieldInitTmp {
    std::string name;
    Expr* expr{nullptr};
};

struct FieldDeclTmp {
    std::string name;
    Type* ty{nullptr};
};


struct StructTmp {
    std::string name;
    std::vector<FieldDeclTmp*> fields;
    std::vector<Function*> methods;
};

struct GlobalTmp {
    std::vector<StructTmp*> structs;
    std::vector<Function*> funcs;
};
}

%union {
    long long ival;
    double fval;
    char* sval;

    Type* typep;

    Expr* expr;
    Stmt* stmt;
    Block* block;
    Function* func;

    std::vector<Expr*>* exprs;
    std::vector<Stmt*>* stmts;
    std::vector<Param>* params;

    LValTmp* lval;
    std::vector<FieldInitTmp>* inits;

    FieldDeclTmp* fdecl;
    StructTmp* stmp;

    GlobalTmp* gtmp;
}

//tokens
%token KW_FEAT KW_SYSTEM
%token KW_MIKUDATA
%token KW_TRACK KW_LET KW_WISH KW_REGRET KW_ROLLING KW_OFFER
%token KW_PRINT
%token KW_SUMMON

%token KW_LEEK KW_RIN KW_SCROLL KW_CODE KW_GHOST
%token ANGEL VIRUS

%token <ival> INT_LIT
%token <fval> FLOAT_LIT
%token <sval> STRING_LIT
%token <sval> ID
%token <sval> TYPE_NAME

%token ARROW
%token ASSIGN
%token PLUS MINUS MUL DIV MOD
%token EQ NEQ LT GT LE GE
%token AND OR NOT
%token DOT COMMA SEMI COLON
%token LPAREN RPAREN LBRACE RBRACE

%left OR
%left AND
%nonassoc EQ NEQ LT GT LE GE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT
%right UMINUS

%type <typep> type

%type <expr> expr atom postfix call struct_lit summon_expr
%type <exprs> arg_list_opt arg_list

%type <stmt> stmt let_stmt assign_stmt print_stmt expr_stmt if_stmt while_stmt return_stmt
%type <stmts> stmt_list

%type <block> block
%type <params> param_list_opt param_list

%type <func> func_def method_def

%type <lval> lvalue
%type <inits> field_inits_opt field_inits

%type <stmp> struct_def struct_members
%type <fdecl> field_decl

%type <gtmp> global_items

// destructori
%destructor { std::free($$); } <sval>
%destructor { delete $$; } <typep>
%destructor { delete $$; } <lval>
%destructor { delete $$; } <inits>
%destructor {
    if ($$) { delete $$->ty; delete $$; }
} <fdecl>
%destructor {
    if ($$) {
        for (auto* f : $$->fields) { if (f) { delete f->ty; delete f; } }
        for (auto* m : $$->methods) { delete m; }
        delete $$;
    }
} <stmp>
%destructor {
    if ($$) {
        for (auto* st : $$->structs) {
            if (!st) continue;
            for (auto* f : st->fields) { if (f) { delete f->ty; delete f; } }
            for (auto* m : st->methods) { delete m; }
            delete st;
        }
        for (auto* fn : $$->funcs) delete fn;
        delete $$;
    }
} <gtmp>

%%

program
    : opt_feat global_items
      {
        g_program = new Program();

        for (auto* st : $2->structs) {
            auto sd = std::make_unique<StructDef>();
            sd->name = st->name;

            for (auto* f : st->fields) {
                sd->fields.push_back(FieldDef{f->name, *f->ty});
                delete f->ty;
                delete f;
            }
            st->fields.clear();

            for (auto* m : st->methods) {
                m->is_method = true;
                m->receiver = st->name;
                sd->methods[m->name].reset(m);
            }
            st->methods.clear();

            g_program->structs.emplace_back(std::move(sd));
            delete st;
        }
        $2->structs.clear();

        for (auto* fn : $2->funcs) {
            g_program->funcs.emplace_back(fn);
        }
        $2->funcs.clear();

        delete $2;
        g_program->index();
      }
    ;

opt_feat
    : // empty
    | KW_FEAT KW_SYSTEM SEMI
    ;

global_items
    : /* empty */ { $$ = new GlobalTmp(); }
    | global_items struct_def
      { $1->structs.push_back($2); $$ = $1; }
    | global_items func_def
      { $1->funcs.push_back($2); $$ = $1; }
    ;

// structs
struct_def
    : KW_MIKUDATA TYPE_NAME LBRACE struct_members RBRACE SEMI
      {
        $4->name = std::string($2);
        std::free($2);
        $$ = $4;
      }
    ;

struct_members
    : //empty
      { $$ = new StructTmp(); }
    | struct_members field_decl
      {
        $1->fields.push_back($2);
        $$ = $1;
      }
    | struct_members method_def
      {
        $1->methods.push_back($2);
        $$ = $1;
      }
    ;

field_decl
    : ID COLON type SEMI
      {
        auto* f = new FieldDeclTmp();
        f->name = std::string($1);
        std::free($1);
        f->ty = $3;
        $$ = f;
      }
    ;

method_def
    : KW_TRACK ID LPAREN param_list_opt RPAREN ARROW type block
      {
        auto* fn = new Function();
        fn->name = std::string($2);
        std::free($2);

        fn->params = *$4;
        delete $4;

        fn->ret = *$7;
        delete $7;

        fn->body.reset($8);
        $$ = fn;
      }
    ;

//functions
func_def
    : KW_TRACK ID LPAREN param_list_opt RPAREN ARROW type block
      {
        auto* fn = new Function();
        fn->name = std::string($2);
        std::free($2);

        fn->params = *$4;
        delete $4;

        fn->ret = *$7;
        delete $7;

        fn->body.reset($8);
        $$ = fn;
      }
    ;

// parameters
param_list_opt
    : /* empty */ { $$ = new std::vector<Param>(); }
    | param_list  { $$ = $1; }
    ;

param_list
    : ID COLON type
      {
        auto* p = new std::vector<Param>();
        p->push_back(Param{std::string($1), *$3});
        std::free($1);
        delete $3;
        $$ = p;
      }
    | param_list COMMA ID COLON type
      {
        $1->push_back(Param{std::string($3), *$5});
        std::free($3);
        delete $5;
        $$ = $1;
      }
    ;

type
    : KW_LEEK   { $$ = new Type(Type::Leek()); }
    | KW_RIN    { $$ = new Type(Type::Rin()); }
    | KW_SCROLL { $$ = new Type(Type::Scroll()); }
    | KW_CODE   { $$ = new Type(Type::Code()); }
    | KW_GHOST  { $$ = new Type(Type::Ghost()); }
    | TYPE_NAME { $$ = new Type(Type::Struct(std::string($1))); std::free($1); }
    ;

//blocks and statements
block
    : LBRACE stmt_list RBRACE
      {
        auto* b = new Block(yylineno);
        for (auto* s : *$2) b->stmts.emplace_back(s);
        delete $2;
        $$ = b;
      }
    ;

stmt_list
    : /* empty */ { $$ = new std::vector<Stmt*>(); }
    | stmt_list stmt
      { $1->push_back($2); $$ = $1; }
    ;

stmt
    : let_stmt    { $$ = $1; }
    | assign_stmt { $$ = $1; }
    | print_stmt  { $$ = $1; }
    | if_stmt     { $$ = $1; }
    | while_stmt  { $$ = $1; }
    | return_stmt { $$ = $1; }
    | expr_stmt   { $$ = $1; }
    ;

let_stmt
    : KW_LET ID ASSIGN expr SEMI
      {
        $$ = new StmtLet(yylineno, std::string($2), std::nullopt, ExprPtr($4));
        std::free($2);
      }
    | KW_LET ID COLON type ASSIGN expr SEMI
      {
        $$ = new StmtLet(yylineno, std::string($2), std::optional<Type>(* $4), ExprPtr($6));
        std::free($2);
        delete $4;
      }
    ;

lvalue
    : ID
      {
        auto* lv = new LValTmp();
        lv->line = yylineno;
        lv->parts.push_back(std::string($1));
        std::free($1);
        $$ = lv;
      }
    | lvalue DOT ID
      {
        $1->parts.push_back(std::string($3));
        std::free($3);
        $$ = $1;
      }
    ;

assign_stmt
    : lvalue ASSIGN expr SEMI
      {
        auto lv = std::make_unique<LValue>();
        lv->line = $1->line;
        lv->parts = std::move($1->parts);
        delete $1;
        $$ = new StmtAssign(yylineno, std::move(lv), ExprPtr($3));
      }
    ;

print_stmt
    : KW_PRINT LPAREN expr RPAREN SEMI
      { $$ = new StmtPrint(yylineno, ExprPtr($3)); }
    ;

expr_stmt
    : expr SEMI
      { $$ = new StmtExpr(yylineno, ExprPtr($1)); }
    ;

if_stmt
    : KW_WISH LPAREN expr RPAREN block
      { $$ = new StmtIf(yylineno, ExprPtr($3), std::unique_ptr<Block>($5), nullptr); }
    | KW_WISH LPAREN expr RPAREN block KW_REGRET block
      { $$ = new StmtIf(yylineno, ExprPtr($3), std::unique_ptr<Block>($5), std::unique_ptr<Block>($7)); }
    ;

while_stmt
    : KW_ROLLING LPAREN expr RPAREN block
      { $$ = new StmtWhile(yylineno, ExprPtr($3), std::unique_ptr<Block>($5)); }
    ;

return_stmt
    : KW_OFFER SEMI
      { $$ = new StmtReturn(yylineno, std::nullopt); }
    | KW_OFFER expr SEMI
      {
        std::optional<ExprPtr> ex;
        ex.emplace(ExprPtr($2));
        $$ = new StmtReturn(yylineno, std::move(ex));
      }
    ;

//expressions
expr
    : expr PLUS expr   { $$ = new ExprBin(yylineno, BinOp::Add, ExprPtr($1), ExprPtr($3)); }
    | expr MINUS expr  { $$ = new ExprBin(yylineno, BinOp::Sub, ExprPtr($1), ExprPtr($3)); }
    | expr MUL expr    { $$ = new ExprBin(yylineno, BinOp::Mul, ExprPtr($1), ExprPtr($3)); }
    | expr DIV expr    { $$ = new ExprBin(yylineno, BinOp::Div, ExprPtr($1), ExprPtr($3)); }
    | expr MOD expr    { $$ = new ExprBin(yylineno, BinOp::Mod, ExprPtr($1), ExprPtr($3)); }

    | expr EQ expr     { $$ = new ExprBin(yylineno, BinOp::Eq,  ExprPtr($1), ExprPtr($3)); }
    | expr NEQ expr    { $$ = new ExprBin(yylineno, BinOp::Neq, ExprPtr($1), ExprPtr($3)); }
    | expr LT expr     { $$ = new ExprBin(yylineno, BinOp::Lt,  ExprPtr($1), ExprPtr($3)); }
    | expr LE expr     { $$ = new ExprBin(yylineno, BinOp::Le,  ExprPtr($1), ExprPtr($3)); }
    | expr GT expr     { $$ = new ExprBin(yylineno, BinOp::Gt,  ExprPtr($1), ExprPtr($3)); }
    | expr GE expr     { $$ = new ExprBin(yylineno, BinOp::Ge,  ExprPtr($1), ExprPtr($3)); }

    | expr AND expr    { $$ = new ExprBin(yylineno, BinOp::And, ExprPtr($1), ExprPtr($3)); }
    | expr OR expr     { $$ = new ExprBin(yylineno, BinOp::Or,  ExprPtr($1), ExprPtr($3)); }

    | NOT expr         { $$ = new ExprUn(yylineno, UnOp::Not, ExprPtr($2)); }
    | MINUS expr %prec UMINUS { $$ = new ExprUn(yylineno, UnOp::Neg, ExprPtr($2)); }

    | postfix          { $$ = $1; }
    ;

postfix
    : atom { $$ = $1; }
    | postfix DOT ID
      { $$ = new ExprField(yylineno, ExprPtr($1), std::string($3)); std::free($3); }
    | postfix DOT ID LPAREN arg_list_opt RPAREN
      {
        std::vector<ExprPtr> args;
        for (auto* e : *$5) args.emplace_back(e);
        delete $5;
        $$ = new ExprMethodCall(yylineno, ExprPtr($1), std::string($3), std::move(args));
        std::free($3);
      }
    ;

atom
    : INT_LIT           { $$ = new ExprInt(yylineno, $1); }
    | FLOAT_LIT         { $$ = new ExprFloat(yylineno, $1); }
    | STRING_LIT        { $$ = new ExprString(yylineno, std::string($1)); std::free($1); }
    | ANGEL             { $$ = new ExprBool(yylineno, true); }
    | VIRUS             { $$ = new ExprBool(yylineno, false); }
    | ID                { $$ = new ExprVar(yylineno, std::string($1)); std::free($1); }
    | call              { $$ = $1; }
    | struct_lit        { $$ = $1; }
    | summon_expr       { $$ = $1; }
    | LPAREN expr RPAREN { $$ = $2; }
    ;

call
    : ID LPAREN arg_list_opt RPAREN
      {
        std::vector<ExprPtr> args;
        for (auto* e : *$3) args.emplace_back(e);
        delete $3;
        $$ = new ExprCall(yylineno, std::string($1), std::move(args));
        std::free($1);
      }
    ;

summon_expr
    : KW_SUMMON TYPE_NAME LPAREN RPAREN
      { $$ = new ExprSummon(yylineno, std::string($2)); std::free($2); }
    ;

struct_lit
    : TYPE_NAME LBRACE field_inits_opt RBRACE
      {
        std::vector<FieldInit> v;
        for (auto& it : *$3) {
            FieldInit fi;
            fi.name = it.name;
            fi.expr.reset(it.expr);
            v.push_back(std::move(fi));
        }
        delete $3;
        $$ = new ExprStructLit(yylineno, std::string($1), std::move(v));
        std::free($1);
      }
    ;

field_inits_opt
    : /* empty */ { $$ = new std::vector<FieldInitTmp>(); }
    | field_inits { $$ = $1; }
    ;

field_inits
    : ID COLON expr
      {
        auto* v = new std::vector<FieldInitTmp>();
        FieldInitTmp it;
        it.name = std::string($1);
        std::free($1);
        it.expr = $3;
        v->push_back(std::move(it));
        $$ = v;
      }
    | field_inits COMMA ID COLON expr
      {
        FieldInitTmp it;
        it.name = std::string($3);
        std::free($3);
        it.expr = $5;
        $1->push_back(std::move(it));
        $$ = $1;
      }
    ;

arg_list_opt
    : /* empty */ { $$ = new std::vector<Expr*>(); }
    | arg_list    { $$ = $1; }
    ;

arg_list
    : expr
      { auto* v = new std::vector<Expr*>(); v->push_back($1); $$ = v; }
    | arg_list COMMA expr
      { $1->push_back($3); $$ = $1; }
    ;

%%

Program* miku_get_program() { return g_program; }

void yyerror(const char* s) {
    std::fprintf(stderr, "[PARSE] %s at line %d\n", s, yylineno);
}
