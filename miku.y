/* ============================================================================
 * miku.y  (Bison grammar)  — spec-driven
 *
 * Key design points implemented:
 *  1) Ambiguity fix (no shift/reduce on ID):
 *       - Types that are class names are returned by the lexer as TYPE_NAME
 *       - Normal identifiers are returned as ID
 *
 *  2) Execution model (per spec):
 *       - Only in MAIN we evaluate AST statements.
 *       - Only ASSIGN and PRINT statements produce AST nodes (and are evaluated).
 *       - if/while/calls/field access are type-checked but do not produce AST.
 *
 *  3) Return (offer) rules:
 *       - offer is allowed in functions/methods, including nested blocks (if/while)
 *       - offer is NOT allowed in main, including inside main's if/while blocks
 * ========================================================================== */

%{
#include "miku_ast.h"
#include <cstdio>
#include <cstdlib>
#include <string>

extern int yylineno;
int yylex(void);
void yyerror(const char* s);
%}

/* ----------------------------------------------------------------------------
 * Semantic value union
 * -------------------------------------------------------------------------- */
%union {
    long long ival;
    double    fval;
    int       bval;   /* 0/1 for bool */
    char*     sval;

    Type*     typep;
    ExprInfo* expr;
    ASTNode*  ast;
    ParamList* params;
    ArgList*  args;
}

/* ----------------------------------------------------------------------------
 * Tokens
 * -------------------------------------------------------------------------- */

/* keywords */
%token KW_INT KW_FLOAT KW_STRING KW_BOOL
%token KW_CLASS KW_FUNC KW_MAIN KW_RETURN KW_IF KW_ELSE KW_WHILE KW_NEW
%token KW_PRINT

/* literals + identifiers */
%token <ival> INT_LIT
%token <fval> FLOAT_LIT
%token <bval> BOOL_LIT
%token <sval> STRING_LIT
%token <sval> ID
%token <sval> TYPE_NAME   /* returned by lexer when ID matches a known class */

/* operators + punctuation */
%token ASSIGN ARROW
%token PLUS MINUS MUL DIV MOD
%token EQ NEQ LT GT LE GE
%token AND OR NOT
%token DOT COMMA SEMI COLON
%token LPAREN RPAREN LBRACE RBRACE

/* ----------------------------------------------------------------------------
 * Precedence (classic)
 * -------------------------------------------------------------------------- */
%left OR
%left AND
%nonassoc EQ NEQ LT GT LE GE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT
%right UMINUS

/* ----------------------------------------------------------------------------
 * Types for nonterminals
 * -------------------------------------------------------------------------- */
%type <typep> type
%type <expr>  expr atom postfix call_expr object_new
%type <ast>   assign_stmt print_stmt
%type <ast>   stmt_main stmt_func

%type <args>   arg_list_opt arg_list
%type <params> param_list_opt param_list

%%

/* ============================================================================
 * Top level
 * ========================================================================== */

program
    : global_items main_block
    ;

global_items
    : /* empty */
    | global_items global_item
    ;

global_item
    : class_def
    | func_def
    | global_var_decl
    ;

/* ============================================================================
 * Global variables
 * ========================================================================== */

global_var_decl
    : type ID SEMI
      {
        Type t = *$1; delete $1;
        std::string name($2); std::free($2);
        /* global variable declaration */
        declare_var(g_tm, yylineno, name, t, std::nullopt, /*isGlobal=*/true);
      }
    | type ID ASSIGN expr SEMI
      {
        Type t = *$1; delete $1;
        std::string name($2); std::free($2);

        /* optional init value (if evaluator supports it) */
        std::optional<Value> initVal;
        if ($4 && $4->type != t) {
            semantic_error(g_tm, yylineno,
                "Type mismatch in init of '" + name + "': declared " +
                type_to_string(t) + " but got " + type_to_string($4->type));
        }
        if ($4 && $4->node) initVal = $4->node->eval(g_tm);

        declare_var(g_tm, yylineno, name, t, initVal, /*isGlobal=*/true);
        destroy_exprinfo($4);
      }
    ;

/* ============================================================================
 * Classes (global scope only)
 * ========================================================================== */

class_def
    : KW_CLASS ID
      {
        std::string cname($2); std::free($2);
        declare_class_begin(g_tm, yylineno, cname);
      }
      LBRACE class_members RBRACE SEMI
      {
        declare_class_end(g_tm);
      }
    ;

class_members
    : /* empty */
    | class_members class_member
    ;

class_member
    : type ID SEMI
      {
        Type t = *$1; delete $1;
        std::string field($2); std::free($2);

        /* current class context should be stored in g_tm;
           if your function expects class name, pass it here instead of "" */
        declare_class_field(g_tm, yylineno, /*className=*/"", field, t);
      }
    | method_def
    ;

/* ============================================================================
 * Methods (inside class)
 * ========================================================================== */

method_def
    : KW_FUNC ID LPAREN param_list_opt RPAREN ARROW type
      {
        std::string mname($2); std::free($2);
        Type ret = *$7; delete $7;
        ParamList params = *$4; destroy_paramlist($4);

        declare_method(g_tm, yylineno, /*className=*/"", mname, ret, params);

        /* enter method scope and bind params */
        g_tm.push_scope("method:" + mname);
        for (const auto& p : params.v) {
            declare_var(g_tm, p.line, p.name, p.type, std::nullopt, /*isGlobal=*/false);
        }
      }
      func_block
      {
        g_tm.pop_scope();
      }
    ;

/* ============================================================================
 * Functions (global scope)
 * ========================================================================== */

func_def
    : KW_FUNC ID LPAREN param_list_opt RPAREN ARROW type
      {
        std::string fname($2); std::free($2);
        Type ret = *$7; delete $7;
        ParamList params = *$4; destroy_paramlist($4);

        declare_func(g_tm, yylineno, fname, ret, params);

        /* enter function scope and bind params */
        g_tm.push_scope("func:" + fname);
        for (const auto& p : params.v) {
            declare_var(g_tm, p.line, p.name, p.type, std::nullopt, /*isGlobal=*/false);
        }
      }
      func_block
      {
        g_tm.pop_scope();
      }
    ;

/* ============================================================================
 * Function block: local decls allowed ONLY at start
 * ========================================================================== */

func_block
    : LBRACE local_decls stmt_list_func RBRACE
    ;

/* locals allowed only before statements */
local_decls
    : /* empty */
    | local_decls local_decl
    ;

local_decl
    : type ID SEMI
      {
        Type t = *$1; delete $1;
        std::string name($2); std::free($2);
        declare_var(g_tm, yylineno, name, t, std::nullopt, /*isGlobal=*/false);
      }
    | type ID ASSIGN expr SEMI
      {
        Type t = *$1; delete $1;
        std::string name($2); std::free($2);

        std::optional<Value> initVal;
        if ($4 && $4->type != t) {
            semantic_error(g_tm, yylineno,
                "Type mismatch in init of '" + name + "': declared " +
                type_to_string(t) + " but got " + type_to_string($4->type));
        }
        if ($4 && $4->node) initVal = $4->node->eval(g_tm);

        declare_var(g_tm, yylineno, name, t, initVal, /*isGlobal=*/false);
        destroy_exprinfo($4);
      }
    ;

/* ============================================================================
 * Main block: NO declarations allowed, and statements are evaluated
 * ========================================================================== */

main_block
    : KW_MAIN LBRACE main_stmt_list RBRACE
    ;

/* In main: each stmt_main that yields AST (assign/print) is eval-ed */
main_stmt_list
    : /* empty */
    | main_stmt_list stmt_main
      {
        if ($2) { $2->eval(g_tm); delete $2; }
      }
    ;

/* ============================================================================
 * Statement lists inside FUNCTIONS (not executed by evaluator)
 * ========================================================================== */

/* In functions: we parse + typecheck, but do NOT execute.
   We still delete any AST we might have created. */
stmt_list_func
    : /* empty */
    | stmt_list_func stmt_func
      {
        if ($2) delete $2;
      }
    ;

/* ============================================================================
 * MAIN statements (no return, no decls)
 *   - assign + print produce AST
 *   - if/while/call exist but do not produce AST
 * ========================================================================== */

stmt_main
    : assign_stmt              { $$ = $1; }
    | print_stmt               { $$ = $1; }
    | call_stmt                { $$ = nullptr; }
    | if_stmt_main             { $$ = nullptr; }
    | while_stmt_main          { $$ = nullptr; }
    ;

/* MAIN if/while blocks must also NOT allow return */
if_stmt_main
    : KW_IF LPAREN expr RPAREN block_no_decls_main else_opt_main
      {
        if ($3 && $3->type.kind != Type::Kind::BOOL) {
            semantic_error(g_tm, $3->line,
                "if() condition must be bool, got " + type_to_string($3->type));
        }
        destroy_exprinfo($3);
      }
    ;

else_opt_main
    : /* empty */
    | KW_ELSE block_no_decls_main
    ;

while_stmt_main
    : KW_WHILE LPAREN expr RPAREN block_no_decls_main
      {
        if ($3 && $3->type.kind != Type::Kind::BOOL) {
            semantic_error(g_tm, $3->line,
                "while() condition must be bool, got " + type_to_string($3->type));
        }
        destroy_exprinfo($3);
      }
    ;

/* MAIN blocks: no decls, and only stmt_main allowed inside */
block_no_decls_main
    : LBRACE stmt_list_no_decls_main RBRACE
    ;

stmt_list_no_decls_main
    : /* empty */
    | stmt_list_no_decls_main stmt_main
      {
        /* main evaluates only the top-level stmt_main list;
           inside blocks, spec says if/while are not executed anyway.
           So we just delete AST if any. */
        if ($2) delete $2;
      }
    ;

/* ============================================================================
 * FUNCTION statements (return allowed anywhere, but still no decls inside blocks)
 * ========================================================================== */

stmt_func
    : assign_stmt              { $$ = $1; }
    | print_stmt               { $$ = $1; }
    | call_stmt                { $$ = nullptr; }
    | if_stmt_func             { $$ = nullptr; }
    | while_stmt_func          { $$ = nullptr; }
    | return_stmt              { $$ = nullptr; }
    ;

/* FUNCTION if/while blocks allow return inside */
if_stmt_func
    : KW_IF LPAREN expr RPAREN block_no_decls_func else_opt_func
      {
        if ($3 && $3->type.kind != Type::Kind::BOOL) {
            semantic_error(g_tm, $3->line,
                "if() condition must be bool, got " + type_to_string($3->type));
        }
        destroy_exprinfo($3);
      }
    ;

else_opt_func
    : /* empty */
    | KW_ELSE block_no_decls_func
    ;

while_stmt_func
    : KW_WHILE LPAREN expr RPAREN block_no_decls_func
      {
        if ($3 && $3->type.kind != Type::Kind::BOOL) {
            semantic_error(g_tm, $3->line,
                "while() condition must be bool, got " + type_to_string($3->type));
        }
        destroy_exprinfo($3);
      }
    ;

/* FUNCTION blocks: no decls, but stmt_func allowed inside */
block_no_decls_func
    : LBRACE stmt_list_no_decls_func RBRACE
    ;

stmt_list_no_decls_func
    : /* empty */
    | stmt_list_no_decls_func stmt_func
      {
        if ($2) delete $2;
      }
    ;

/* ============================================================================
 * Concrete statements that can appear in main/funcs
 * ========================================================================== */

/* Call statement: parsed + checked, but no AST per spec */
call_stmt
    : call_expr SEMI
      {
        destroy_exprinfo($1);
      }
    ;

/* Return statement: allowed only in func/method rules above */
return_stmt
    : KW_RETURN expr SEMI { destroy_exprinfo($2); }
    | KW_RETURN SEMI      { }
    ;

/* Assignment statement: produces AST node, eval-ed in MAIN only */
assign_stmt
    : ID ASSIGN expr SEMI
      {
        std::string name($1); std::free($1);

        /* left side must be declared variable */
        ExprInfo* idinfo = make_ident(g_tm, yylineno, name);
        ASTNode* rhs = ($3 ? $3->node : ASTNode::other(yylineno, Type::Error()));

        if (!idinfo || idinfo->type.kind == Type::Kind::ERROR) {
            $$ = ASTNode::assign(yylineno, name, Type::Error(), rhs);
        } else {
            if ($3 && idinfo->type != $3->type) {
                semantic_error(g_tm, yylineno,
                    "Type mismatch in assignment to '" + name + "': left " +
                    type_to_string(idinfo->type) + ", right " + type_to_string($3->type));
            }
            $$ = ASTNode::assign(yylineno, name, idinfo->type, rhs);
        }

        destroy_exprinfo(idinfo);
        if ($3) { $3->node = nullptr; destroy_exprinfo($3); }
      }
    ;

/* Print statement: produces AST node, eval-ed in MAIN only */
print_stmt
    : KW_PRINT LPAREN expr RPAREN SEMI
      {
        ASTNode* e = ($3 ? $3->node : ASTNode::other(yylineno, Type::Error()));
        $$ = ASTNode::print(yylineno, e);

        if ($3) { $3->node = nullptr; destroy_exprinfo($3); }
      }
    ;

/* ============================================================================
 * Expressions
 * ========================================================================== */

expr
    : expr PLUS expr        { $$ = make_binary_expr(g_tm, yylineno, "+",  $1, $3); }
    | expr MINUS expr       { $$ = make_binary_expr(g_tm, yylineno, "-",  $1, $3); }
    | expr MUL expr         { $$ = make_binary_expr(g_tm, yylineno, "*",  $1, $3); }
    | expr DIV expr         { $$ = make_binary_expr(g_tm, yylineno, "/",  $1, $3); }
    | expr MOD expr         { $$ = make_binary_expr(g_tm, yylineno, "%",  $1, $3); }

    | expr EQ expr          { $$ = make_binary_expr(g_tm, yylineno, "==", $1, $3); }
    | expr NEQ expr         { $$ = make_binary_expr(g_tm, yylineno, "!=", $1, $3); }
    | expr LT expr          { $$ = make_binary_expr(g_tm, yylineno, "<",  $1, $3); }
    | expr LE expr          { $$ = make_binary_expr(g_tm, yylineno, "<=", $1, $3); }
    | expr GT expr          { $$ = make_binary_expr(g_tm, yylineno, ">",  $1, $3); }
    | expr GE expr          { $$ = make_binary_expr(g_tm, yylineno, ">=", $1, $3); }

    | expr AND expr         { $$ = make_binary_expr(g_tm, yylineno, "&&", $1, $3); }
    | expr OR expr          { $$ = make_binary_expr(g_tm, yylineno, "||", $1, $3); }

    | NOT expr              { $$ = make_unary_expr (g_tm, yylineno, "!",  $2); }
    | MINUS expr %prec UMINUS
                            { $$ = make_unary_expr (g_tm, yylineno, "u-", $2); }

    | postfix               { $$ = $1; }
    ;

/* atom: base values */
atom
    : INT_LIT               { $$ = make_lit_int   (yylineno, $1); }
    | FLOAT_LIT             { $$ = make_lit_float (yylineno, $1); }
    | BOOL_LIT              { $$ = make_lit_bool  (yylineno, $1 != 0); }
    | STRING_LIT            { std::string s($1); std::free($1); $$ = make_lit_string(yylineno, s); }
    | ID                    { std::string n($1); std::free($1); $$ = make_ident(g_tm, yylineno, n); }
    | LPAREN expr RPAREN    { $$ = $2; }
    | call_expr             { $$ = $1; }
    | object_new            { $$ = $1; }
    ;

/* postfix: field access / method call become OTHER leaves by spec,
   but we still type-check and compute resulting type */
postfix
    : atom { $$ = $1; }

    | postfix DOT ID
      {
        std::string field($3); std::free($3);
        ExprInfo* out = make_other_from_field_access(g_tm, yylineno, *$1, field);
        destroy_exprinfo($1);
        $$ = out;
      }

    | postfix DOT ID LPAREN arg_list_opt RPAREN
      {
        std::string m($3); std::free($3);
        ArgList args = *$5; destroy_arglist($5);
        ExprInfo* out = make_other_from_method_call(g_tm, yylineno, *$1, m, args);
        destroy_exprinfo($1);
        $$ = out;
      }
    ;

/* free function call: OTHER leaf */
call_expr
    : ID LPAREN arg_list_opt RPAREN
      {
        std::string fname($1); std::free($1);
        ArgList args = *$3; destroy_arglist($3);
        $$ = make_other_from_func_call(g_tm, yylineno, fname, args);
      }
    ;

/* object creation: OTHER leaf */
object_new
    : KW_NEW TYPE_NAME LPAREN RPAREN
      {
        std::string cname($2); std::free($2);
        $$ = make_other_from_object_new(g_tm, yylineno, cname);
      }
    ;

/* args */
arg_list_opt
    : /* empty */           { $$ = arglist_empty(); }
    | arg_list              { $$ = $1; }
    ;

arg_list
    : expr                  { $$ = arglist_single($1); }
    | arg_list COMMA expr    { $$ = arglist_append($1, $3); }
    ;

/* ============================================================================
 * Parameters
 * ========================================================================== */

param_list_opt
    : /* empty */             { $$ = paramlist_empty(); }
    | param_list              { $$ = $1; }
    ;

param_list
    : ID COLON type
      {
        std::string n($1); std::free($1);
        Type t = *$3; delete $3;
        $$ = paramlist_single(n, t, yylineno);
      }
    | param_list COMMA ID COLON type
      {
        std::string n($3); std::free($3);
        Type t = *$5; delete $5;
        $$ = paramlist_append($1, n, t, yylineno);
      }
    ;

/* ============================================================================
 * Types
 * ========================================================================== */

type
    : KW_INT                 { $$ = new Type(Type::Int()); }
    | KW_FLOAT               { $$ = new Type(Type::Float()); }
    | KW_STRING              { $$ = new Type(Type::String()); }
    | KW_BOOL                { $$ = new Type(Type::Bool()); }
    | TYPE_NAME
      {
        std::string tn($1); std::free($1);
        Type t = resolve_type_name(g_tm, yylineno, tn);
        $$ = new Type(t);
      }
    ;

%%

void yyerror(const char* s) {
    std::fprintf(stderr, "[PARSE] %s at line %d\n", s, yylineno);
}
