%{
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include "miku_ast.h"

using namespace std;

extern int yylex();
extern int yylineno;
extern FILE* yyin;
void yyerror(const char* s);

SymbolTable* globalScope = new SymbolTable("Global");
SymbolTable* currentScope = globalScope;

// Helper to capture param names during parsing
string currentFuncName;
%}

%union {
    int ival;
    double fval;
    char* sval;
    bool bval;
    ASTNode* node;
    MikuType typeVal;
}

%token FEAT MIKUDATA MIKUCLASS MIKUSEE MIKUBLIND TRACK LET
%token WISH REGRET ROLLING VANISH STEP OFFER ERASE PRINT MAIN SELF
%token TYPE_LEEK TYPE_SCROLL TYPE_CODE TYPE_GHOST LUKA_PTR TYPE_RIN TYPE_LEN
%token ARROW SCOPE EQ NEQ GT LT GE LE
%token <ival> INT_LITERAL
%token <fval> LITERAL_RIN LITERAL_LEN
%token <sval> STRING_LITERAL IDENTIFIER
%token <bval> BOOL_TRUE BOOL_FALSE

%type <typeVal> type_name return_type
%type <node> expression primary assign_stmt print_stmt stmt_no_decl func_call field_access expr_stmt
%type <node> if_stmt while_stmt return_stmt delete_stmt break_stmt continue_stmt
%type <node> stmt_list_no_decls block_no_decls func_block main_block local_decls var_decl 
%type <node> arg_list arg_seq

%left EQ NEQ LT LE GT GE
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

program: global_decls main_decl ;
global_decls: | global_decls global_decl ;
global_decl: feat_stmt | class_data_decl | class_impl_decl | func_decl ;

feat_stmt: FEAT path ';' ;
path: IDENTIFIER | path SCOPE IDENTIFIER | path '.' IDENTIFIER ;
class_data_decl: MIKUDATA IDENTIFIER '{' 
      { string n=$2; currentScope->addSymbol(n, TYPE_CLASS); currentScope=new SymbolTable(n, currentScope); }
      field_list '}' { currentScope=currentScope->parent; } ;
field_list: | field_list field_def ;
field_def: IDENTIFIER ':' type_name { currentScope->addSymbol($1, $3); } 
         | IDENTIFIER ':' type_name ',' { currentScope->addSymbol($1, $3); } ;

/* --- FUNCTION DECLARATION --- */
func_decl: TRACK IDENTIFIER '(' 
      { 
         currentFuncName = $2;
         currentScope->addFunction($2, TYPE_VOID, {}, {}); 
         currentScope = new SymbolTable($2, currentScope);
      }
      param_list_opt ')' return_type 
      { 
         SymbolInfo* fn = currentScope->parent->lookup($2);
         if(fn) fn->type = $7;
      }
      func_block
      {
         SymbolInfo* fn = currentScope->parent->lookup($2);
         if(fn) {
             fn->funcBody = $9;
             fn->definitionScope = currentScope;
         }
         currentScope = currentScope->parent;
      }
    ;
class_impl_decl: MIKUCLASS IDENTIFIER '{' method_list '}' ;
method_list: | method_list method ;
method: access_mod TRACK IDENTIFIER '(' 
      { currentScope = new SymbolTable($3, currentScope); }
      param_list_opt ')' return_type func_block
      { currentScope = currentScope->parent; } ;
access_mod: MIKUSEE | MIKUBLIND ;

/* --- MAIN DECLARATION --- */
main_decl: TRACK MAIN '(' ')' return_type 
      { currentScope = new SymbolTable("Main", currentScope); }
      main_block
      { 
         cout << endl << ">>> [RUNTIME] Executing Main Block via AST <<<" << endl;
         if($7) $7->eval(currentScope);
         currentScope = currentScope->parent; 
      } ;

func_block: '{' local_decls stmt_list_no_decls '}' 
    { 
        if ($2 && $3) $$ = new ASTNode(NODE_SEQ, $2, $3);
        else if ($2) $$ = $2;
        else $$ = $3;
    } ;

main_block: '{' stmt_list_no_decls '}' { $$ = $2; } ;

local_decls: 
      /* empty */ { $$ = nullptr; }
    | local_decls var_decl 
      { 
          if ($1 == nullptr) $$ = $2;
          else $$ = new ASTNode(NODE_SEQ, $1, $2);
      }
    ;

stmt_list_no_decls: 
      /* empty */ { $$ = nullptr; }
    | stmt_list_no_decls stmt_no_decl 
      { 
          if ($1 == nullptr) $$ = $2;
          else $$ = new ASTNode(NODE_SEQ, $1, $2);
      }
    ;

stmt_no_decl: assign_stmt { $$ = $1; } 
    | expr_stmt { $$ = $1; }   
    | if_stmt { $$ = $1; } 
    | while_stmt { $$ = $1; }
    | return_stmt { $$ = $1; } 
    | delete_stmt { $$ = nullptr; }
    | break_stmt { $$ = nullptr; } 
    | continue_stmt { $$ = nullptr; }
    | print_stmt { $$ = $1; } ;

expr_stmt: expression ';' { $$ = $1; } ;

var_decl: 
      LET IDENTIFIER '=' expression ';'
      { 
          currentScope->addSymbol($2, $4->dataType); 
          $$ = new ASTNode(NODE_DECL, nullptr, $4);
          $$->varName = $2;
          $$->dataType = $4->dataType;
      }
    | LET IDENTIFIER ':' type_name '=' expression ';' 
      { 
          currentScope->addSymbol($2, $4);
          $$ = new ASTNode(NODE_DECL, nullptr, $6);
          $$->varName = $2;
          $$->dataType = $4;
      } ;

assign_stmt: IDENTIFIER '=' expression ';' 
      { 
        SymbolInfo* s = currentScope->lookup($1); 
        if (s == nullptr) {
            string errorMsg = "Variable '" + string($1) + "' not declared!";
            yyerror(errorMsg.c_str());
            YYERROR; 
        }
        ASTNode* v = new ASTNode(NODE_VAR); v->varName = $1;
        $$ = new ASTNode(NODE_ASSIGN, v, $3); 
        $$->dataType = s->type; 
      }
    | field_access '=' expression ';'
      { $$ = nullptr; } ;

print_stmt: PRINT '(' expression ')' ';' { $$ = new ASTNode(NODE_PRINT, $3); } ;

if_stmt: WISH '(' expression ')' block_no_decls 
         { $$ = new ASTNode(NODE_IF, $3, $5); }
       | WISH '(' expression ')' block_no_decls REGRET block_no_decls 
         { $$ = new ASTNode(NODE_IF, $3, $5, $7); } ;

while_stmt: ROLLING '(' expression ')' block_no_decls 
          { $$ = new ASTNode(NODE_WHILE, $3, $5); } ;

return_stmt: OFFER expression ';' { $$ = new ASTNode(NODE_RETURN, $2); } 
           | OFFER ';' { $$ = new ASTNode(NODE_RETURN); } ;

delete_stmt: ERASE IDENTIFIER ';' { $$ = nullptr; } ;
break_stmt: VANISH ';' { $$ = nullptr; } ;
continue_stmt: STEP ';' { $$ = nullptr; } ;

block_no_decls: '{' stmt_list_no_decls '}' { $$ = $2; } ;

expression: primary { $$ = $1; } | '(' expression ')' { $$ = $2; }
    | expression '+' expression { $$ = new ASTNode(NODE_OP_ADD, $1, $3); $$->dataType = $1->dataType; }
    | expression '-' expression { $$ = new ASTNode(NODE_OP_SUB, $1, $3); $$->dataType = $1->dataType; }
    | expression '*' expression { $$ = new ASTNode(NODE_OP_MUL, $1, $3); $$->dataType = $1->dataType; }
    | expression '/' expression { $$ = new ASTNode(NODE_OP_DIV, $1, $3); $$->dataType = $1->dataType; }
    | '-' expression %prec UMINUS { ASTNode* z=new ASTNode(NODE_CONST); if($2->dataType==TYPE_INT)z->val.iVal=0; 
                                    $$ = new ASTNode(NODE_OP_SUB, z, $2); $$->dataType=$2->dataType; }
    | expression GT expression { $$=new ASTNode(NODE_OP_GT, $1, $3); $$->dataType=TYPE_BOOL; }
    | expression LT expression { $$=new ASTNode(NODE_OP_LT, $1, $3); $$->dataType=TYPE_BOOL; }
    | expression GE expression { $$=new ASTNode(NODE_OP_GE, $1, $3); $$->dataType=TYPE_BOOL; }
    | expression LE expression { $$=new ASTNode(NODE_OP_LE, $1, $3); $$->dataType=TYPE_BOOL; }
    | expression EQ expression { $$=new ASTNode(NODE_OP_EQ, $1, $3); $$->dataType=TYPE_BOOL; }
    | expression NEQ expression { $$=new ASTNode(NODE_OP_NEQ, $1, $3); $$->dataType=TYPE_BOOL; } ;

primary: IDENTIFIER { 
             SymbolInfo* s = currentScope->lookup($1); 
             if (s == nullptr) {
                 string errorMsg = "Variable '" + string($1) + "' used but not declared!";
                 yyerror(errorMsg.c_str());
                 YYERROR;
             }
             ASTNode* n = new ASTNode(NODE_VAR); n->varName=$1;
             n->dataType = s->type; $$=n; 
       }
       | INT_LITERAL { $$=new ASTNode(NODE_CONST); $$->val.type=TYPE_INT; $$->val.iVal=$1; $$->dataType=TYPE_INT; }
       | LITERAL_RIN { $$=new ASTNode(NODE_CONST); $$->val.type=TYPE_FLOAT; $$->val.fVal=$1; $$->dataType=TYPE_FLOAT; }
       | LITERAL_LEN { $$=new ASTNode(NODE_CONST); $$->val.type=TYPE_FLOAT; $$->val.fVal=$1; $$->dataType=TYPE_FLOAT; }
       | STRING_LITERAL { $$=new ASTNode(NODE_CONST); $$->val.type=TYPE_STRING; $$->val.sVal=$1; $$->dataType=TYPE_STRING; }
       | BOOL_TRUE { $$=new ASTNode(NODE_CONST); $$->val.type=TYPE_BOOL; $$->val.bVal=true; $$->dataType=TYPE_BOOL; }
       | BOOL_FALSE { $$=new ASTNode(NODE_CONST); $$->val.type=TYPE_BOOL; $$->val.bVal=false; $$->dataType=TYPE_BOOL; }
       | func_call { $$ = $1; }
       | field_access { $$ = $1; } ;

field_access: IDENTIFIER '.' IDENTIFIER { $$=new ASTNode(NODE_OTHER); } | SELF '.' IDENTIFIER { $$=new ASTNode(NODE_OTHER); } ;

func_call: IDENTIFIER '(' arg_list ')' 
      { 
         SymbolInfo* s=currentScope->lookup($1);
         $$ = new ASTNode(NODE_FUNC_CALL, nullptr, nullptr, $3); 
         $$->varName = $1; 
         $$->dataType = s?s->type:TYPE_VOID;
      } ;

arg_list: /* empty */ { $$ = nullptr; } 
        | arg_seq { $$ = $1; } ;

arg_seq: expression 
         { $$ = new ASTNode(NODE_ARG_LIST, $1, nullptr); }
       | expression ',' arg_seq 
         { $$ = new ASTNode(NODE_ARG_LIST, $1, $3); } ;

type_name: TYPE_LEEK {$$=TYPE_INT;} | TYPE_SCROLL {$$=TYPE_STRING;} |
           TYPE_CODE {$$=TYPE_BOOL;} | TYPE_RIN {$$=TYPE_FLOAT;} | TYPE_LEN {$$=TYPE_FLOAT;} | TYPE_GHOST {$$=TYPE_VOID;} | IDENTIFIER {$$=TYPE_CLASS;} ;
param_list_opt: | param_list;
param_list: param | param_list ',' param;

/* --- FIX BELOW: Pushing both name AND type --- */
param: IDENTIFIER ':' type_name 
      { 
         currentScope->addSymbol($1, $3); 
         SymbolInfo* fn = currentScope->parent->lookup(currentFuncName);
         if(fn) {
             fn->paramNames.push_back($1);
             fn->paramTypes.push_back($3); // <-- THIS LINE WAS MISSING
         }
      } 
    | LUKA_PTR IDENTIFIER { currentScope->addSymbol($2, TYPE_VOID); } ;
return_type: {$$=TYPE_VOID;} | ARROW type_name {$$=$2;} ;

%%
void yyerror(const char* s) { fprintf(stderr, "[Error] Line %d: %s\n", yylineno, s); }
int main(int argc, char** argv) { if(argc>1)yyin=fopen(argv[1],"r"); remove("tables.txt"); yyparse(); return 0; }