%option noyywrap nodefault yylineno nounput noinput

%{
#include "miku_ast.h"
#include "miku.tab.hpp"
#include <cstdlib>
#include <cstring>
#include <string>

static char* dup_yytext() {
    size_t n = std::strlen(yytext);
    char* s = (char*)std::malloc(n + 1);
    std::memcpy(s, yytext, n + 1);
    return s;
}

static std::string unescape_string(const char* in) {
    std::string s(in);
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
        s = s.substr(1, s.size() - 2);

    std::string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '\\' && i + 1 < s.size()) {
            char c = s[++i];
            switch (c) {
                case 'n': out.push_back('\n'); break;
                case 't': out.push_back('\t'); break;
                case 'r': out.push_back('\r'); break;
                case '\\': out.push_back('\\'); break;
                case '"': out.push_back('"'); break;
                default: out.push_back(c); break;
            }
        } else {
            out.push_back(s[i]);
        }
    }
    return out;
}
%}

%x COMMENT

WS      [ \t\r]+
NL      \n+
IDLOW   [a-z_][A-Za-z0-9_]*
IDCAP   [A-Z][A-Za-z0-9_]*
INT     [0-9]+
FLOAT   ([0-9]+"."[0-9]*|[0-9]*"."[0-9]+)([eE][+-]?[0-9]+)?([fF])?
STR     \"([^\\\"]|\\.)*\"

%%

{WS}    { }
{NL}    { }

"//".*          { }

"/*"            { BEGIN(COMMENT); }
<COMMENT>"*/"   { BEGIN(INITIAL); }
<COMMENT>{NL}   { }
<COMMENT>.      { }
<COMMENT><<EOF>> { std::fprintf(stderr, "[LEX] unterminated block comment at EOF\n"); return 0; }

"feat"            { return KW_FEAT; }
"system"          { return KW_SYSTEM; }

"MikuData"        { return KW_MIKUDATA; }

"track"           { return KW_TRACK; }
"let"             { return KW_LET; }
"wish"            { return KW_WISH; }
"regret"          { return KW_REGRET; }
"rolling"         { return KW_ROLLING; }
"offer"           { return KW_OFFER; }

"tell_your_world" { return KW_PRINT; }

"summon"          { return KW_SUMMON; }

"leek"            { return KW_LEEK; }
"rin"             { return KW_RIN; }
"scroll"          { return KW_SCROLL; }
"code"            { return KW_CODE; }
"ghost"           { return KW_GHOST; }

"angel"           { return ANGEL; }
"virus"           { return VIRUS; }

"->"              { return ARROW; }
"=="              { return EQ; }
"!="              { return NEQ; }
"<="              { return LE; }
">="              { return GE; }
"<"               { return LT; }
">"               { return GT; }
"&&"              { return AND; }
"||"              { return OR; }
"!"               { return NOT; }

"="               { return ASSIGN; }

"+"               { return PLUS; }
"-"               { return MINUS; }
"*"               { return MUL; }
"/"               { return DIV; }
"%"               { return MOD; }

"."               { return DOT; }
","               { return COMMA; }
";"               { return SEMI; }
":"               { return COLON; }

"("               { return LPAREN; }
")"               { return RPAREN; }
"{"               { return LBRACE; }
"}"               { return RBRACE; }

{FLOAT}           {
                    std::string t(yytext);
                    if (!t.empty() && (t.back()=='f' || t.back()=='F')) t.pop_back();
                    yylval.fval = std::strtod(t.c_str(), nullptr);
                    return FLOAT_LIT;
                  }

{INT}             {
                    yylval.ival = (long long)std::strtoll(yytext, nullptr, 10);
                    return INT_LIT;
                  }

{STR}             {
                    std::string u = unescape_string(yytext);
                    char* s = (char*)std::malloc(u.size() + 1);
                    std::memcpy(s, u.c_str(), u.size() + 1);
                    yylval.sval = s;
                    return STRING_LIT;
                  }

{IDCAP}           { yylval.sval = dup_yytext(); return TYPE_NAME; }
{IDLOW}           { yylval.sval = dup_yytext(); return ID; }

.                 { std::fprintf(stderr, "[LEX] unknown char '%s' at line %d\n", yytext, yylineno); }

%%
