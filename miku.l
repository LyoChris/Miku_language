%{
#include <iostream>
#include <string>
#include <cstring>
#include "miku_ast.h"
#include "miku.tab.h"
using namespace std;
%}

%option noyywrap
%option yylineno

%%

"feat"              { return FEAT; }

"MikuData"          { return MIKUDATA; }
"MikuClass"         { return MIKUCLASS; }
"MikuSee"           { return MIKUSEE; }
"MikuBlind"         { return MIKUBLIND; }

"track"             { return TRACK; }
"let"               { return LET; }

"wish"              { return WISH; }
"regret"            { return REGRET; }
"rolling"           { return ROLLING; }
"vanish"            { return VANISH; }
"step"              { return STEP; }

"offer"             { return OFFER; }
"erase"             { return ERASE; }

"tell_your_world"   { return PRINT; }

"world_is_mine"     { return MAIN; }

"leek"              { return TYPE_LEEK; }
"scroll"            { return TYPE_SCROLL; }
"code"              { return TYPE_CODE; }
"ghost"             { return TYPE_GHOST; }
"rin"               { return TYPE_RIN; }
"len"               { return TYPE_LEN; }
"luka"              { return LUKA_PTR; }

"angel"             { yylval.bval = true; return BOOL_TRUE; }
"virus"             { yylval.bval = false; return BOOL_FALSE; }
"self"              { return SELF; }

[0-9]+\.[0-9]+[fF]      { yylval.fval = atof(yytext); return LITERAL_RIN; }
[0-9]+\.[0-9]+          { yylval.fval = atof(yytext); return LITERAL_LEN; }
[0-9]+                  { yylval.ival = atoi(yytext); return INT_LITERAL; }

\"([^\"\\]|\\.)*\"      { yylval.sval = strdup(yytext); return STRING_LITERAL; }

[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = strdup(yytext); return IDENTIFIER; }

"->"                { return ARROW; }
"::"                { return SCOPE; }
"=="                { return EQ; }
"!="                { return NEQ; }
"<="                { return LE; }
">="                { return GE; }
"<"                 { return LT; }
">"                 { return GT; }

[ \t\r\n]+          ;
"//".* ;
.                   { return yytext[0]; }

%%