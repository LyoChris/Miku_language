%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union // data types
{
    int ival;
    double fval;
    char* sval;
}

// keywords 
%token FEAT MIKUDATA MIKUCLASS MIKUSEE MIKUBLIND
%token TRACK LET
%token WISH REGRET ROLLING VANISH STEP
%token OFFER ERASE
%token PRINT
%token MAIN
%token SELF
%token BOOL_TRUE BOOL_FALSE

// types
%token TYPE_LEEK TYPE_SCROLL TYPE_CODE TYPE_GHOST LUKA_PTR TYPE_RIN TYPE_LEN

// operators
%token ARROW SCOPE EQ NEQ GT LT GE LE

// literals
%token <ival> INT_LITERAL
%token <fval> LITERAL_RIN LITERAL_LEN
%token <sval> STRING_LITERAL IDENTIFIER

// prcedence (expresii de tip a < b == c and everything)
%left EQ NEQ LT LE GT GE
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

/* PROGRAM:
   - global scope: imports, MikuData, MikuClass, normal functions
   - mandatory main: track world_is_mine() ... { ... }
   - inside main: NO `let ...` declarations
*/
program:
      global_decls main_decl
    ;

global_decls:

    | global_decls global_decl
    ;

global_decl:
      feat_stmt
    | class_data_decl
    | class_impl_decl
    | func_decl
    ;

// imports
feat_stmt:
      FEAT path ';'
    ;

path:
      IDENTIFIER
    | path SCOPE IDENTIFIER
    | path '.' IDENTIFIER
    ;

// structs / classes
class_data_decl:
      MIKUDATA IDENTIFIER '{' field_list '}'
    ;

field_list:

    | field_list field_def
    ;

field_def:
      IDENTIFIER ':' type_name
    | IDENTIFIER ':' type_name ','
    ;

type_name:
      TYPE_LEEK
    | TYPE_SCROLL
    | TYPE_CODE
    | TYPE_GHOST
    | TYPE_RIN
    | TYPE_LEN
    | LUKA_PTR
    | IDENTIFIER
    ;

// functions
class_impl_decl:
      MIKUCLASS IDENTIFIER '{' method_list '}'
    ;

method_list:

    | method_list method
    ;

access_mod:
      MIKUSEE
    | MIKUBLIND
    ;

method:
      access_mod TRACK IDENTIFIER '(' param_list_opt ')' return_type func_block
    ;

func_decl:
      TRACK IDENTIFIER '(' param_list_opt ')' return_type func_block
    ;

// main
main_decl:
      TRACK MAIN '(' ')' return_type main_block
    ;

param_list_opt:

    | param_list
    ;

param_list:
      param
    | param_list ',' param
    ;

param:
      IDENTIFIER ':' type_name
    | LUKA_PTR IDENTIFIER
    | LUKA_PTR SELF
    ;

return_type:

    | ARROW type_name
    ;

// Function block: locals only at the top 
func_block:
      '{' local_decls stmt_list_no_decls '}'
    ;

// Main block: no locals 
main_block:
      '{' stmt_list_no_decls '}'
    ;

local_decls:

    | local_decls var_decl
    ;

// statements (no declarations here) 
stmt_list_no_decls:

    | stmt_list_no_decls stmt_no_decl
    ;

stmt_no_decl:
      assign_stmt   
    | expr_stmt
    | if_stmt
    | while_stmt
    | return_stmt
    | delete_stmt
    | break_stmt
    | continue_stmt
    | print_stmt
    ;

expr_stmt:
      expression ';'
    ;

print_stmt:
      PRINT '(' arg_list ')' ';'
    ;

// local var decl 
var_decl:
      LET IDENTIFIER '=' expression ';'
    ;

assign_stmt:
      IDENTIFIER '=' expression ';'
    | field_access '=' expression ';'
    ;

if_stmt:
      WISH '(' expression ')' block_no_decls
    | WISH '(' expression ')' block_no_decls REGRET block_no_decls
    ;

while_stmt:
      ROLLING '(' expression ')' block_no_decls
    ;

block_no_decls:
      '{' stmt_list_no_decls '}'
    ;

break_stmt:
      VANISH ';'
    ;

continue_stmt:
      STEP ';'
    ;

return_stmt:
      OFFER expression ';'
    | OFFER ';'
    ;

delete_stmt:
      ERASE IDENTIFIER ';'
    ;

// expressions 
expression:
      primary
    | '(' expression ')'
    | '-' expression %prec UMINUS
    | expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression GT expression
    | expression GE expression
    | expression LT expression
    | expression LE expression
    | expression EQ expression
    | expression NEQ expression
    ;

primary:
      IDENTIFIER
    | SELF
    | INT_LITERAL
    | LITERAL_RIN
    | LITERAL_LEN
    | STRING_LITERAL
    | BOOL_TRUE
    | BOOL_FALSE
    | func_call
    | struct_init
    | field_access
    ;

// object / method access 
field_access:
      IDENTIFIER '.' IDENTIFIER
    | SELF '.' IDENTIFIER
    ;

func_call:
      IDENTIFIER '(' arg_list ')'
    | IDENTIFIER SCOPE IDENTIFIER '(' arg_list ')'
    | field_access '(' arg_list ')'
    ;

// object init 
struct_init:
      IDENTIFIER '{' field_init_list_opt '}'
    ;

field_init_list_opt:

    | field_init_list
    ;

field_init_list:
      field_init
    | field_init_list ',' field_init
    | field_init_list ','             
    ;

field_init:
      IDENTIFIER ':' expression
    ;

// args 
arg_list:

    | arg_seq
    ;

arg_seq:
      expression
    | arg_seq ',' expression
    ;

%%

void yyerror(const char* s) 
{
    fprintf(stderr, "Miku Syntax Error: %s\n", s);
}

int main(int argc, char** argv) 
{
    if (argc > 1) 
    {
        yyin = fopen(argv[1], "r");
        if (!yyin) 
        {
            perror("fopen"); return 1; 
        }
    }
    yyparse();

    printf("Completed successfully.\n");
    return 0;
}
