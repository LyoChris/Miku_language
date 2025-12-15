%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miku.tab.h"
%}

%option noyywrap

%%

"feat"              { return FEAT; } // include (use)

"MikuData"          { return MIKUDATA; } // struct
"MikuClass"         { return MIKUCLASS; } // class
"MikuSee"           { return MIKUSEE; } // public
"MikuBlind"         { return MIKUBLIND; } // private

"track"             { return TRACK; } // function 
"let"               { return LET; } // let (in rust)

"wish"              { return WISH; } // if
"regret"            { return REGRET; } // else
"rolling"           { return ROLLING; } // while
"vanish"            { return VANISH; } // break
"step"              { return STEP; } //continue

"offer"             { return OFFER; } // return
"erase"             { return ERASE; } // delete 

"tell_your_world"   { return PRINT; } // print

"world_is_mine"     { return MAIN; } // main

"leek"              { return TYPE_LEEK; } // int
"scroll"            { return TYPE_SCROLL; } // string
"code"              { return TYPE_CODE; } // bool
"ghost"             { return TYPE_GHOST; } // void
"rin"               { return TYPE_RIN; } // float
"len"               { return TYPE_LEN; } // double
"luka"              { return LUKA_PTR; } // pointer

"angel"             { return BOOL_TRUE; } // true
"virus"             { return BOOL_FALSE; } // false
"self"              { return SELF; } // seld

[0-9]+\.[0-9]+[fF]      { yylval.fval = atof(yytext); return LITERAL_RIN; } // float
[0-9]+\.[0-9]+          { yylval.fval = atof(yytext); return LITERAL_LEN; } // double
[0-9]+                  { yylval.ival = atoi(yytext); return INT_LITERAL; } // int

\"([^\"\\]|\\.)*\"      { yylval.sval = strdup(yytext); return STRING_LITERAL; } // any string

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.sval = strdup(yytext); return IDENTIFIER; } // identifier 

"->"                { return ARROW; }
"::"                { return SCOPE; }
"=="                { return EQ; }
"!="                { return NEQ; }
"<="                { return LE; }
">="                { return GE; }
"<"                 { return LT; }
">"                 { return GT; }

[ \t\r\n]+          ; // spaces and whitespaces
"//".*              ; // comments

.                   { return yytext[0]; } // single character

%%
