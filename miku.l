%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miku.tab.h"
%}

%option noyywrap

%%

"feat"          { return FEAT; }
"MikuData"      { return MIKUDATA; }
"MikuClass"     { return MIKUCLASS; }
"MikuSee"       { return MIKUSEE; }
"MikuBlind"     { return MIKUBLIND; }
"track"         { return TRACK; }
"leek"          { return TYPE_LEEK; }
"scroll"        { return TYPE_SCROLL; }
"code"          { return TYPE_CODE; }
"ghost"         { return TYPE_GHOST; }
"luka"          { return LUKA_PTR; }
"wish"          { return WISH; }
"regret"        { return REGRET; }
"rolling"       { return ROLLING; }
"offer"         { return OFFER; }
"erase"         { return ERASE; }
"angel"         { return BOOL_TRUE; }
"virus"         { return BOOL_FALSE; }
"master"        { return MASTER; }
"self"          { return SELF; }
"rin"           { return TYPE_RIN; }
"len"           { return TYPE_LEN; }



[0-9]+\.[0-9]+[fF]  { yylval.fval = atof(yytext); return LITERAL_RIN; }

[0-9]+\.[0-9]+      { yylval.fval = atof(yytext); return LITERAL_LEN; }

[0-9]+          { yylval.ival = atoi(yytext); return INT_LITERAL; }

\"[^\"]*\"      { yylval.sval = strdup(yytext); return STRING_LITERAL; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = strdup(yytext); return IDENTIFIER; }

"->"            { return ARROW; }
"::"            { return SCOPE; }
"=="            { return EQ; }
"!="            { return NEQ; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return LT; }
">"             { return GT; }

[ \t\n]
"//".* ;

.               { return yytext[0]; } /* Return single chars like { } ( ) ; : , = */

%%