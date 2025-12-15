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

#ifndef YY_YY_MIKU_TAB_H_INCLUDED
# define YY_YY_MIKU_TAB_H_INCLUDED
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
    FEAT = 258,                    /* FEAT  */
    MIKUDATA = 259,                /* MIKUDATA  */
    MIKUCLASS = 260,               /* MIKUCLASS  */
    MIKUSEE = 261,                 /* MIKUSEE  */
    MIKUBLIND = 262,               /* MIKUBLIND  */
    TRACK = 263,                   /* TRACK  */
    LET = 264,                     /* LET  */
    WISH = 265,                    /* WISH  */
    REGRET = 266,                  /* REGRET  */
    ROLLING = 267,                 /* ROLLING  */
    VANISH = 268,                  /* VANISH  */
    STEP = 269,                    /* STEP  */
    OFFER = 270,                   /* OFFER  */
    ERASE = 271,                   /* ERASE  */
    PRINT = 272,                   /* PRINT  */
    MAIN = 273,                    /* MAIN  */
    SELF = 274,                    /* SELF  */
    BOOL_TRUE = 275,               /* BOOL_TRUE  */
    BOOL_FALSE = 276,              /* BOOL_FALSE  */
    TYPE_LEEK = 277,               /* TYPE_LEEK  */
    TYPE_SCROLL = 278,             /* TYPE_SCROLL  */
    TYPE_CODE = 279,               /* TYPE_CODE  */
    TYPE_GHOST = 280,              /* TYPE_GHOST  */
    LUKA_PTR = 281,                /* LUKA_PTR  */
    TYPE_RIN = 282,                /* TYPE_RIN  */
    TYPE_LEN = 283,                /* TYPE_LEN  */
    ARROW = 284,                   /* ARROW  */
    SCOPE = 285,                   /* SCOPE  */
    EQ = 286,                      /* EQ  */
    NEQ = 287,                     /* NEQ  */
    GT = 288,                      /* GT  */
    LT = 289,                      /* LT  */
    GE = 290,                      /* GE  */
    LE = 291,                      /* LE  */
    INT_LITERAL = 292,             /* INT_LITERAL  */
    LITERAL_RIN = 293,             /* LITERAL_RIN  */
    LITERAL_LEN = 294,             /* LITERAL_LEN  */
    STRING_LITERAL = 295,          /* STRING_LITERAL  */
    IDENTIFIER = 296,              /* IDENTIFIER  */
    UMINUS = 297                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 13 "miku.y"

    int ival;
    double fval;
    char* sval;

#line 112 "miku.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MIKU_TAB_H_INCLUDED  */
