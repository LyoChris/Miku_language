%{
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include "miku_ast.h"

using namespace std;

// -- External references --
extern int yylex();
extern int yylineno;
extern FILE* yyin;

void yyerror(const char* s);

// -- Global Scoping & AST Variables --
SymbolTable* globalScope = new SymbolTable("Global");
SymbolTable* currentScope = globalScope;

// List to store AST nodes for the main block execution (Part IV)
vector<ASTNode*> mainStatements;

%}

/* -- Yacc Definitions -- */

%union {
    int ival;
    double fval;
    char* sval;
    bool bval;
    
    // Pointers for C++ structures
    ASTNode* node;
    MikuType typeVal;
}

// -- Keywords --
%token FEAT MIKUDATA MIKUCLASS MIKUSEE MIKUBLIND
%token TRACK LET
%token WISH REGRET ROLLING VANISH STEP
%token OFFER ERASE
%token PRINT
%token MAIN
%token SELF

// -- Types --
%token TYPE_LEEK TYPE_SCROLL TYPE_CODE TYPE_GHOST LUKA_PTR TYPE_RIN TYPE_LEN

// -- Operators --
%token ARROW SCOPE
%token EQ NEQ GT LT GE LE

// -- Literals --
%token <ival> INT_LITERAL
%token <fval> LITERAL_RIN LITERAL_LEN
%token <sval> STRING_LITERAL IDENTIFIER
%token <bval> BOOL_TRUE BOOL_FALSE

// -- Non-Terminal Types --
%type <typeVal> type_name return_type
%type <node> expression primary assign_stmt print_stmt stmt_no_decl
%type <node> if_stmt while_stmt return_stmt delete_stmt break_stmt continue_stmt

// -- Precedence (Resolves ambiguity) --
%left EQ NEQ LT LE GT GE
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

/* =======================================================================
   GRAMMAR RULES
   ======================================================================= */

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

/* --- Imports --- */
feat_stmt:
      FEAT path ';'
    ;

path:
      IDENTIFIER
    | path SCOPE IDENTIFIER
    | path '.' IDENTIFIER
    ;

/* --- Class Data (MikuData) --- */
class_data_decl:
      MIKUDATA IDENTIFIER '{' 
      { 
          // Part II: Create Class Scope
          string name = $2;
          if(currentScope->lookup(name)) yyerror("Class Identifier already defined");
          
          currentScope->addSymbol(name, TYPE_CLASS, name);
          currentScope = new SymbolTable("Class_" + name, currentScope);
      }
      field_list '}' 
      {
          // Exit Class Scope
          SymbolTable* old = currentScope;
          currentScope = currentScope->parent;
      }
    ;

field_list:
    | field_list field_def
    ;

field_def:
      IDENTIFIER ':' type_name
      {
          // Part III: Check for field redeclaration
          if(!currentScope->addSymbol($1, $3)) {
              char buf[100]; sprintf(buf, "Field '%s' redeclared", $1); yyerror(buf);
          }
      }
    | IDENTIFIER ':' type_name ',' 
      {
          if(!currentScope->addSymbol($1, $3)) {
              char buf[100]; sprintf(buf, "Field '%s' redeclared", $1); yyerror(buf);
          }
      }
    ;

/* --- Functions --- */
func_decl:
      TRACK IDENTIFIER '(' 
      {
         // Part II: Function Scope & Global Declaration
         if(!currentScope->addFunction($2, TYPE_VOID, {})) { 
             yyerror("Function identifier redeclared");
         }
         currentScope = new SymbolTable("Func_" + string($2), currentScope);
      }
      param_list_opt ')' return_type func_block
      {
         // Exit Scope
         SymbolTable* old = currentScope;
         currentScope = currentScope->parent;
         delete old;
      }
    ;

/* --- Class Implementation (Methods) --- */
class_impl_decl:
      MIKUCLASS IDENTIFIER '{' method_list '}'
    ;

method_list:
    | method_list method
    ;

method:
      access_mod TRACK IDENTIFIER '(' 
      {
          currentScope = new SymbolTable("Method_" + string($3), currentScope);
      }
      param_list_opt ')' return_type func_block
      {
          SymbolTable* old = currentScope;
          currentScope = currentScope->parent;
          delete old;
      }
    ;

access_mod: MIKUSEE | MIKUBLIND ;

/* --- Main Function --- */
main_decl:
      TRACK MAIN '(' ')' return_type 
      {
         // Enter Main Scope
         currentScope = new SymbolTable("Main", currentScope);
         mainStatements.clear();
      }
      main_block
      {
         // Part IV: Execution of Main Block
         cout << endl << ">>> [RUNTIME] Executing Main Block via AST <<<" << endl;
         for(ASTNode* node : mainStatements) {
             if(node) {
                 node->eval(currentScope);
             }
         }
         
         // Cleanup
         SymbolTable* old = currentScope;
         currentScope = currentScope->parent;
         delete old;
      }
    ;

/* --- Blocks --- */
// Regular functions can have local variables
func_block: '{' local_decls stmt_list_no_decls '}' ;

// Main block: STRICTLY NO local variables allowed (Part I Syntax Constraint)
main_block: '{' stmt_list_main '}' ;

// Special stmt list for main to collect AST nodes
stmt_list_main:
    | stmt_list_main stmt_no_decl 
    {
        if ($2 != nullptr) mainStatements.push_back($2);
    }
    ;

local_decls:
    | local_decls var_decl
    ;

stmt_list_no_decls:
    | stmt_list_no_decls stmt_no_decl
    ;

/* --- Statements --- */
stmt_no_decl:
      assign_stmt   { $$ = $1; } // Returns AST
    | expr_stmt     { $$ = nullptr; }
    | if_stmt       { $$ = nullptr; } 
    | while_stmt    { $$ = nullptr; }
    | return_stmt   { $$ = nullptr; }
    | delete_stmt   { $$ = nullptr; }
    | break_stmt    { $$ = nullptr; }
    | continue_stmt { $$ = nullptr; }
    | print_stmt    { $$ = $1; } // Returns AST
    ;

expr_stmt: expression ';' ;

/* --- Variable Declarations (Part III Checks) --- */
var_decl:
      LET IDENTIFIER '=' expression ';'
      {
          // Infer type from expression
          if (!currentScope->addSymbol($2, $4->dataType)) 
             yyerror("Variable redeclared");
      }
    | LET IDENTIFIER ':' type_name '=' expression ';'
      {
          // Part III: Check type compatibility
          if ($4 != $6->dataType) {
             char buf[100]; 
             sprintf(buf, "Type mismatch in declaration of '%s'", $2);
             yyerror(buf);
          }
          
          if (!currentScope->addSymbol($2, $4)) 
             yyerror("Variable redeclared");
      }
    ;

/* --- Assignment (Part IV AST) --- */
assign_stmt:
      IDENTIFIER '=' expression ';'
      {
          // Part III: Semantic Analysis
          SymbolInfo* info = currentScope->lookup($1);
          if (!info) {
              char buf[100]; sprintf(buf, "Variable '%s' not declared", $1); yyerror(buf);
          } else if (info->type != $3->dataType) {
              yyerror("Type mismatch in assignment");
          }

          // Part IV: Build AST (Node Assign)
          // Left child is a VAR node holding the name
          ASTNode* varNode = new ASTNode(NODE_VAR);
          varNode->varName = $1;
          
          $$ = new ASTNode(NODE_ASSIGN, varNode, $3);
          $$->dataType = (info ? info->type : TYPE_VOID);
      }
    | field_access '=' expression ';' { $$ = nullptr; }
    ;

/* --- Print (Part IV AST) --- */
print_stmt:
      PRINT '(' expression ')' ';'
      {
          $$ = new ASTNode(NODE_PRINT, $3, nullptr);
      }
    ;

/* --- Control Flow (Fixed: explicitly return nullptr) --- */
if_stmt:
      WISH '(' expression ')' block_no_decls { $$ = nullptr; }
    | WISH '(' expression ')' block_no_decls REGRET block_no_decls { $$ = nullptr; }
    ;

while_stmt:
      ROLLING '(' expression ')' block_no_decls { $$ = nullptr; }
    ;

return_stmt: 
      OFFER expression ';' { $$ = nullptr; }
    | OFFER ';' { $$ = nullptr; }
    ;

delete_stmt: ERASE IDENTIFIER ';' { $$ = nullptr; } ;
break_stmt: VANISH ';' { $$ = nullptr; } ;
continue_stmt: STEP ';' { $$ = nullptr; } ;

block_no_decls: '{' stmt_list_no_decls '}' ;

/* --- Expressions (Part IV AST Construction) --- */
expression:
      primary { $$ = $1; }
    | '(' expression ')' { $$ = $2; }
    
    // Arithmetic
    | expression '+' expression 
      { 
        if ($1->dataType != $3->dataType) yyerror("Type mismatch in +");
        $$ = new ASTNode(NODE_OP_ADD, $1, $3); 
        $$->dataType = $1->dataType;
      }
    | expression '-' expression 
      { 
        if ($1->dataType != $3->dataType) yyerror("Type mismatch in -");
        $$ = new ASTNode(NODE_OP_SUB, $1, $3); 
        $$->dataType = $1->dataType;
      }
    | expression '*' expression 
      { 
        if ($1->dataType != $3->dataType) yyerror("Type mismatch in *");
        $$ = new ASTNode(NODE_OP_MUL, $1, $3); 
        $$->dataType = $1->dataType;
      }
    | expression '/' expression 
      { 
        if ($1->dataType != $3->dataType) yyerror("Type mismatch in /");
        $$ = new ASTNode(NODE_OP_DIV, $1, $3); 
        $$->dataType = $1->dataType;
      }
    
    // Unary Minus
    | '-' expression %prec UMINUS
      {
          ASTNode* zero = new ASTNode(NODE_CONST);
          zero->dataType = $2->dataType;
          if($2->dataType == TYPE_INT) zero->val.iVal = 0;
          if($2->dataType == TYPE_FLOAT) zero->val.fVal = 0.0;
          
          $$ = new ASTNode(NODE_OP_SUB, zero, $2);
          $$->dataType = $2->dataType;
      }

    // Boolean Logic
    | expression GT expression { $$ = new ASTNode(NODE_OP_GT, $1, $3); $$->dataType = TYPE_BOOL; }
    | expression LT expression { $$ = new ASTNode(NODE_OP_LT, $1, $3); $$->dataType = TYPE_BOOL; }
    | expression GE expression { $$ = new ASTNode(NODE_OP_GE, $1, $3); $$->dataType = TYPE_BOOL; }
    | expression LE expression { $$ = new ASTNode(NODE_OP_LE, $1, $3); $$->dataType = TYPE_BOOL; }
    | expression EQ expression { $$ = new ASTNode(NODE_OP_EQ, $1, $3); $$->dataType = TYPE_BOOL; }
    | expression NEQ expression { $$ = new ASTNode(NODE_OP_NEQ, $1, $3); $$->dataType = TYPE_BOOL; }
    ;

primary:
      IDENTIFIER 
      { 
        SymbolInfo* info = currentScope->lookup($1);
        if (!info) { 
            char buf[100]; sprintf(buf, "Identifier '%s' not defined", $1); yyerror(buf);
        }
        
        $$ = new ASTNode(NODE_VAR);
        $$->varName = $1;
        $$->dataType = info ? info->type : TYPE_UNKNOWN;
      }
    | INT_LITERAL 
      { 
        $$ = new ASTNode(NODE_CONST); 
        $$->val.type = TYPE_INT; $$->val.iVal = $1; 
        $$->dataType = TYPE_INT;
      }
    | LITERAL_RIN 
      { 
        $$ = new ASTNode(NODE_CONST); 
        $$->val.type = TYPE_FLOAT; $$->val.fVal = $1; 
        $$->dataType = TYPE_FLOAT;
      }
    | LITERAL_LEN { $$ = new ASTNode(NODE_CONST); $$->val.type = TYPE_FLOAT; $$->val.fVal = $1; $$->dataType = TYPE_FLOAT; }
    | STRING_LITERAL { $$ = new ASTNode(NODE_CONST); $$->val.type = TYPE_STRING; $$->val.sVal = $1; $$->dataType = TYPE_STRING; }
    | BOOL_TRUE { $$ = new ASTNode(NODE_CONST); $$->val.type = TYPE_BOOL; $$->val.bVal = true; $$->dataType = TYPE_BOOL; }
    | BOOL_FALSE { $$ = new ASTNode(NODE_CONST); $$->val.type = TYPE_BOOL; $$->val.bVal = false; $$->dataType = TYPE_BOOL; }
    
    | func_call { $$ = new ASTNode(NODE_OTHER); }
    | field_access { $$ = new ASTNode(NODE_OTHER); }
    ;

field_access:
      IDENTIFIER '.' IDENTIFIER
    | SELF '.' IDENTIFIER
    ;

func_call: IDENTIFIER '(' arg_list ')' ;
arg_list: | arg_seq ;
arg_seq: expression | arg_seq ',' expression ;

type_name:
      TYPE_LEEK { $$ = TYPE_INT; }
    | TYPE_SCROLL { $$ = TYPE_STRING; }
    | TYPE_CODE { $$ = TYPE_BOOL; }
    | TYPE_RIN { $$ = TYPE_FLOAT; }
    | TYPE_LEN { $$ = TYPE_FLOAT; }
    | TYPE_GHOST { $$ = TYPE_VOID; }
    | IDENTIFIER { $$ = TYPE_CLASS; } 
    ;

param_list_opt: | param_list;
param_list: param | param_list ',' param;

// --- PARAM FIXED: Registers symbols in scope ---
param: 
      IDENTIFIER ':' type_name 
      {
          if(!currentScope->addSymbol($1, $3)) {
              char buf[100]; sprintf(buf, "Parameter '%s' redeclared", $1); yyerror(buf);
          }
      }
    | LUKA_PTR IDENTIFIER 
      {
          if(!currentScope->addSymbol($2, TYPE_VOID)) {
               char buf[100]; sprintf(buf, "Parameter '%s' redeclared", $2); yyerror(buf);
          }
      }
    ;

return_type: { $$ = TYPE_VOID; } | ARROW type_name { $$ = $2; };

%%

void yyerror(const char* s) {
    fprintf(stderr, "[Error] Line %d: %s\n", yylineno, s);
}

int main(int argc, char** argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) { perror("fopen"); return 1; }
    }
    
    // Clear output file
    remove("tables.txt");
    
    printf("Starting Miku Compiler...\n");
    yyparse();
    printf("\nParsing completed.\nCheck 'tables.txt' for Symbol Table output.\n");
    
    return 0;
}