/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MIKU_TAB_HPP_INCLUDED
# define YY_YY_MIKU_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    KW_INT = 258,                  /* KW_INT  */
    KW_FLOAT = 259,                /* KW_FLOAT  */
    KW_STRING = 260,               /* KW_STRING  */
    KW_BOOL = 261,                 /* KW_BOOL  */
    KW_CLASS = 262,                /* KW_CLASS  */
    KW_FUNC = 263,                 /* KW_FUNC  */
    KW_MAIN = 264,                 /* KW_MAIN  */
    KW_RETURN = 265,               /* KW_RETURN  */
    KW_IF = 266,                   /* KW_IF  */
    KW_ELSE = 267,                 /* KW_ELSE  */
    KW_WHILE = 268,                /* KW_WHILE  */
    KW_NEW = 269,                  /* KW_NEW  */
    KW_PRINT = 270,                /* KW_PRINT  */
    INT_LIT = 271,                 /* INT_LIT  */
    FLOAT_LIT = 272,               /* FLOAT_LIT  */
    BOOL_LIT = 273,                /* BOOL_LIT  */
    STRING_LIT = 274,              /* STRING_LIT  */
    ID = 275,                      /* ID  */
    TYPE_NAME = 276,               /* TYPE_NAME  */
    ASSIGN = 277,                  /* ASSIGN  */
    ARROW = 278,                   /* ARROW  */
    PLUS = 279,                    /* PLUS  */
    MINUS = 280,                   /* MINUS  */
    MUL = 281,                     /* MUL  */
    DIV = 282,                     /* DIV  */
    MOD = 283,                     /* MOD  */
    EQ = 284,                      /* EQ  */
    NEQ = 285,                     /* NEQ  */
    LT = 286,                      /* LT  */
    GT = 287,                      /* GT  */
    LE = 288,                      /* LE  */
    GE = 289,                      /* GE  */
    AND = 290,                     /* AND  */
    OR = 291,                      /* OR  */
    NOT = 292,                     /* NOT  */
    DOT = 293,                     /* DOT  */
    COMMA = 294,                   /* COMMA  */
    SEMI = 295,                    /* SEMI  */
    COLON = 296,                   /* COLON  */
    LPAREN = 297,                  /* LPAREN  */
    RPAREN = 298,                  /* RPAREN  */
    LBRACE = 299,                  /* LBRACE  */
    RBRACE = 300,                  /* RBRACE  */
    UMINUS = 301                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 33 "miku.y"

    long long ival;
    double    fval;
    int       bval;   /* 0/1 for bool */
    char*     sval;

    Type*     typep;
    ExprInfo* expr;
    ASTNode*  ast;
    ParamList* params;
    ArgList*  args;

#line 123 "miku.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MIKU_TAB_HPP_INCLUDED  */
