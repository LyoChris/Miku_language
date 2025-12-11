%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
    int ival;
    double fval;
    char* sval;
}

/* Tokens */
%token FEAT MIKUDATA MIKUCLASS MIKUSEE TRACK LET OFFER ERASE
%token WISH REGRET BOOL_TRUE BOOL_FALSE
%token TYPE_LEEK TYPE_SCROLL TYPE_CODE TYPE_GHOST LUKA_PTR TYPE_RIN TYPE_LEN
%token ARROW SCOPE EQ GT LT GE LE
%token <ival> INT_LITERAL
%token <fval> LITERAL_RIN LITERAL_LEN
%token <sval> STRING_LITERAL IDENTIFIER

%%

program:
    declaration_list
    ;

declaration_list:
    declaration
    | declaration_list declaration
    ;

declaration:
    feat_stmt
    | class_data_decl   /* MikuData */
    | class_impl_decl   /* MikuClass */
    | func_decl         /* track world_is_mine */
    ;

/* --- 1. Imports --- */
feat_stmt:
    FEAT path ';'
    ;

path:
    IDENTIFIER
    | path SCOPE IDENTIFIER
    | path '.' IDENTIFIER
    ;

/* --- 2. Data Types & Classes (Task: MikuData) --- */
class_data_decl:
    MIKUDATA IDENTIFIER '{' field_list '}'
    ;

field_list:
    /* empty */
    | field_list field_def
    ;

field_def:
    IDENTIFIER ':' type_name ',' 
    | IDENTIFIER ':' type_name
    ;

type_name:
    TYPE_LEEK | TYPE_SCROLL | TYPE_CODE | TYPE_GHOST 
    | TYPE_RIN | TYPE_LEN | LUKA_PTR | IDENTIFIER
    ;

/* --- 3. Methods & Implementation (Task: MikuClass) --- */
class_impl_decl:
    MIKUCLASS IDENTIFIER '{' method_list '}'
    ;

method_list:
    /* empty */
    | method_list method
    ;

method:
    MIKUSEE TRACK IDENTIFIER '(' param_list ')' return_type block
    ;

/* --- Functions (Main) --- */
func_decl:
    TRACK IDENTIFIER '(' param_list ')' return_type block
    ;

param_list:
    /* empty */
    | param
    | param_list ',' param
    ;

param:
    IDENTIFIER ':' type_name
    | LUKA_PTR IDENTIFIER
    ;

return_type:
    /* empty */
    | ARROW type_name
    ;

/* --- Blocks & Statements --- */
block:
    '{' statement_list '}'
    ;

statement_list:
    /* empty */
    | statement_list statement
    ;

statement:
    var_decl
    | assign_stmt
    | expr_stmt
    | if_stmt
    | return_stmt
    | delete_stmt
    ;

/* Task: Syntax for accessing fields/methods is used here */
expr_stmt:
    expression ';'
    ;

/* Task: Initialization logic (let x = ...) */
var_decl:
    LET IDENTIFIER '=' expression ';'
    ;

assign_stmt:
    IDENTIFIER '=' expression ';'
    | field_access '=' expression ';'
    ;

if_stmt:
    WISH expression block
    | WISH expression block REGRET block
    ;

/* Task: Initialization Syntax (offer Song { ... }) */
return_stmt:
    OFFER expression ';'
    | OFFER struct_init ';'
    ;

delete_stmt:
    ERASE IDENTIFIER ';'
    ;

/* --- Expressions --- */
expression:
    term
    | expression '+' expression
    | expression '-' expression
    | expression GT expression
    | expression EQ expression
    | expression LT expression
    | expression GE expression
    | expression LE expression
    ;

term:
    IDENTIFIER
    | INT_LITERAL
    | LITERAL_RIN
    | LITERAL_LEN
    | STRING_LITERAL
    | BOOL_TRUE
    | BOOL_FALSE
    | func_call     /* method use */
    | struct_init   /* object init */
    | field_access  /* field access */
    ;

/* Task: Accessing Fields (self.title) */
field_access:
    IDENTIFIER '.' IDENTIFIER
    ;

/* Task: Using Objects/Methods (my_song.play() or Song::append()) */
func_call:
    IDENTIFIER '(' arg_list ')'
    | IDENTIFIER SCOPE IDENTIFIER '(' arg_list ')'
    | field_access '(' arg_list ')'
    ;

/* Task: Object Initialization Syntax */
struct_init:
    IDENTIFIER '{' field_init_list '}'
    ;

field_init_list:
    field_init
    | field_init_list ',' field_init
    | field_init_list ',' 
    ;

field_init:
    IDENTIFIER ':' expression
    ;

arg_list:
    /* empty */
    | expression
    | arg_list ',' expression
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Miku Syntax Error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}