%option noyywrap nodefault yylineno

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
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"') {
        s = s.substr(1, s.size() - 2);
    }
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
IDRE    [A-Za-z_][A-Za-z0-9_]*
INT     [0-9]+
FLOAT   ([0-9]+"."[0-9]*|[0-9]*"."[0-9]+)([eE][+-]?[0-9]+)?
STR     \"([^\\\"]|\\.)*\"

%%

{WS}            { }
{NL}            { }

"//".*          { }

"/*"            { BEGIN(COMMENT); }
<COMMENT>"*/"   { BEGIN(INITIAL); }
<COMMENT>{NL}   { }
<COMMENT>.      { }
<COMMENT><<EOF>> { std::fprintf(stderr, "[LEX] Unterminated /* */ comment at EOF (line %d)\n", yylineno); return 0; }

"leek"            { return KW_INT; }
"tempo"           { return KW_FLOAT; }
"lyric"           { return KW_STRING; }
"voice"           { return KW_BOOL; }

"MikuData"        { return KW_CLASS; }
"track"           { return KW_FUNC; }
"world_is_mine"   { return KW_MAIN; }
"offer"           { return KW_RETURN; }
"if"              { return KW_IF; }
"else"            { return KW_ELSE; }
"while"           { return KW_WHILE; }
"summon"          { return KW_NEW; }

"tell_your_world" { return KW_PRINT; }

"true"            { yylval.bval = 1; return BOOL_LIT; }
"false"           { yylval.bval = 0; return BOOL_LIT; }

":="              { return ASSIGN; }
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

{FLOAT}           { yylval.fval = std::strtod(yytext, nullptr); return FLOAT_LIT; }
{INT}             { yylval.ival = (long long)std::strtoll(yytext, nullptr, 10); return INT_LIT; }

{STR}             {
                    std::string u = unescape_string(yytext);
                    char* s = (char*)std::malloc(u.size() + 1);
                    std::memcpy(s, u.c_str(), u.size() + 1);
                    yylval.sval = s;
                    return STRING_LIT;
                  }

{IDRE}            {
                    char* s = dup_yytext();
                    if (g_tm.lookup_class(s) != nullptr) {
                        yylval.sval = s;
                        return TYPE_NAME;
                    }
                    yylval.sval = s;
                    return ID;
                  }

.                 { std::fprintf(stderr, "[LEX] Unknown char '%s' at line %d\n", yytext, yylineno); }

%%
