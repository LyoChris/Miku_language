/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 19 "miku.y"

#include "miku_ast.h"
#include <cstdio>
#include <cstdlib>
#include <string>

extern int yylineno;
int yylex(void);
void yyerror(const char* s);

#line 82 "miku.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "miku.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_KW_INT = 3,                     /* KW_INT  */
  YYSYMBOL_KW_FLOAT = 4,                   /* KW_FLOAT  */
  YYSYMBOL_KW_STRING = 5,                  /* KW_STRING  */
  YYSYMBOL_KW_BOOL = 6,                    /* KW_BOOL  */
  YYSYMBOL_KW_CLASS = 7,                   /* KW_CLASS  */
  YYSYMBOL_KW_FUNC = 8,                    /* KW_FUNC  */
  YYSYMBOL_KW_MAIN = 9,                    /* KW_MAIN  */
  YYSYMBOL_KW_RETURN = 10,                 /* KW_RETURN  */
  YYSYMBOL_KW_IF = 11,                     /* KW_IF  */
  YYSYMBOL_KW_ELSE = 12,                   /* KW_ELSE  */
  YYSYMBOL_KW_WHILE = 13,                  /* KW_WHILE  */
  YYSYMBOL_KW_NEW = 14,                    /* KW_NEW  */
  YYSYMBOL_KW_PRINT = 15,                  /* KW_PRINT  */
  YYSYMBOL_INT_LIT = 16,                   /* INT_LIT  */
  YYSYMBOL_FLOAT_LIT = 17,                 /* FLOAT_LIT  */
  YYSYMBOL_BOOL_LIT = 18,                  /* BOOL_LIT  */
  YYSYMBOL_STRING_LIT = 19,                /* STRING_LIT  */
  YYSYMBOL_ID = 20,                        /* ID  */
  YYSYMBOL_TYPE_NAME = 21,                 /* TYPE_NAME  */
  YYSYMBOL_ASSIGN = 22,                    /* ASSIGN  */
  YYSYMBOL_ARROW = 23,                     /* ARROW  */
  YYSYMBOL_PLUS = 24,                      /* PLUS  */
  YYSYMBOL_MINUS = 25,                     /* MINUS  */
  YYSYMBOL_MUL = 26,                       /* MUL  */
  YYSYMBOL_DIV = 27,                       /* DIV  */
  YYSYMBOL_MOD = 28,                       /* MOD  */
  YYSYMBOL_EQ = 29,                        /* EQ  */
  YYSYMBOL_NEQ = 30,                       /* NEQ  */
  YYSYMBOL_LT = 31,                        /* LT  */
  YYSYMBOL_GT = 32,                        /* GT  */
  YYSYMBOL_LE = 33,                        /* LE  */
  YYSYMBOL_GE = 34,                        /* GE  */
  YYSYMBOL_AND = 35,                       /* AND  */
  YYSYMBOL_OR = 36,                        /* OR  */
  YYSYMBOL_NOT = 37,                       /* NOT  */
  YYSYMBOL_DOT = 38,                       /* DOT  */
  YYSYMBOL_COMMA = 39,                     /* COMMA  */
  YYSYMBOL_SEMI = 40,                      /* SEMI  */
  YYSYMBOL_COLON = 41,                     /* COLON  */
  YYSYMBOL_LPAREN = 42,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 43,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 44,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 45,                    /* RBRACE  */
  YYSYMBOL_UMINUS = 46,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_program = 48,                   /* program  */
  YYSYMBOL_global_items = 49,              /* global_items  */
  YYSYMBOL_global_item = 50,               /* global_item  */
  YYSYMBOL_global_var_decl = 51,           /* global_var_decl  */
  YYSYMBOL_class_def = 52,                 /* class_def  */
  YYSYMBOL_53_1 = 53,                      /* $@1  */
  YYSYMBOL_class_members = 54,             /* class_members  */
  YYSYMBOL_class_member = 55,              /* class_member  */
  YYSYMBOL_method_def = 56,                /* method_def  */
  YYSYMBOL_57_2 = 57,                      /* $@2  */
  YYSYMBOL_func_def = 58,                  /* func_def  */
  YYSYMBOL_59_3 = 59,                      /* $@3  */
  YYSYMBOL_func_block = 60,                /* func_block  */
  YYSYMBOL_local_decls = 61,               /* local_decls  */
  YYSYMBOL_local_decl = 62,                /* local_decl  */
  YYSYMBOL_main_block = 63,                /* main_block  */
  YYSYMBOL_main_stmt_list = 64,            /* main_stmt_list  */
  YYSYMBOL_stmt_list_func = 65,            /* stmt_list_func  */
  YYSYMBOL_stmt_main = 66,                 /* stmt_main  */
  YYSYMBOL_if_stmt_main = 67,              /* if_stmt_main  */
  YYSYMBOL_else_opt_main = 68,             /* else_opt_main  */
  YYSYMBOL_while_stmt_main = 69,           /* while_stmt_main  */
  YYSYMBOL_block_no_decls_main = 70,       /* block_no_decls_main  */
  YYSYMBOL_stmt_list_no_decls_main = 71,   /* stmt_list_no_decls_main  */
  YYSYMBOL_stmt_func = 72,                 /* stmt_func  */
  YYSYMBOL_if_stmt_func = 73,              /* if_stmt_func  */
  YYSYMBOL_else_opt_func = 74,             /* else_opt_func  */
  YYSYMBOL_while_stmt_func = 75,           /* while_stmt_func  */
  YYSYMBOL_block_no_decls_func = 76,       /* block_no_decls_func  */
  YYSYMBOL_stmt_list_no_decls_func = 77,   /* stmt_list_no_decls_func  */
  YYSYMBOL_call_stmt = 78,                 /* call_stmt  */
  YYSYMBOL_return_stmt = 79,               /* return_stmt  */
  YYSYMBOL_assign_stmt = 80,               /* assign_stmt  */
  YYSYMBOL_print_stmt = 81,                /* print_stmt  */
  YYSYMBOL_expr = 82,                      /* expr  */
  YYSYMBOL_atom = 83,                      /* atom  */
  YYSYMBOL_postfix = 84,                   /* postfix  */
  YYSYMBOL_call_expr = 85,                 /* call_expr  */
  YYSYMBOL_object_new = 86,                /* object_new  */
  YYSYMBOL_arg_list_opt = 87,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 88,                  /* arg_list  */
  YYSYMBOL_param_list_opt = 89,            /* param_list_opt  */
  YYSYMBOL_param_list = 90,                /* param_list  */
  YYSYMBOL_type = 91                       /* type  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   395

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  193

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   301


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   100,   100,   104,   105,   109,   110,   111,   119,   126,
     151,   150,   162,   163,   167,   176,   185,   184,   210,   209,
     234,   239,   240,   244,   250,   273,   278,   279,   292,   293,
     306,   307,   308,   309,   310,   315,   326,   327,   331,   343,
     347,   348,   362,   363,   364,   365,   366,   367,   372,   383,
     384,   388,   400,   404,   405,   417,   425,   426,   431,   457,
     471,   472,   473,   474,   475,   477,   478,   479,   480,   481,
     482,   484,   485,   487,   488,   491,   496,   497,   498,   499,
     500,   501,   502,   503,   509,   511,   519,   531,   541,   550,
     551,   555,   556,   564,   565,   569,   575,   588,   589,   590,
     591,   592
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "KW_INT", "KW_FLOAT",
  "KW_STRING", "KW_BOOL", "KW_CLASS", "KW_FUNC", "KW_MAIN", "KW_RETURN",
  "KW_IF", "KW_ELSE", "KW_WHILE", "KW_NEW", "KW_PRINT", "INT_LIT",
  "FLOAT_LIT", "BOOL_LIT", "STRING_LIT", "ID", "TYPE_NAME", "ASSIGN",
  "ARROW", "PLUS", "MINUS", "MUL", "DIV", "MOD", "EQ", "NEQ", "LT", "GT",
  "LE", "GE", "AND", "OR", "NOT", "DOT", "COMMA", "SEMI", "COLON",
  "LPAREN", "RPAREN", "LBRACE", "RBRACE", "UMINUS", "$accept", "program",
  "global_items", "global_item", "global_var_decl", "class_def", "$@1",
  "class_members", "class_member", "method_def", "$@2", "func_def", "$@3",
  "func_block", "local_decls", "local_decl", "main_block",
  "main_stmt_list", "stmt_list_func", "stmt_main", "if_stmt_main",
  "else_opt_main", "while_stmt_main", "block_no_decls_main",
  "stmt_list_no_decls_main", "stmt_func", "if_stmt_func", "else_opt_func",
  "while_stmt_func", "block_no_decls_func", "stmt_list_no_decls_func",
  "call_stmt", "return_stmt", "assign_stmt", "print_stmt", "expr", "atom",
  "postfix", "call_expr", "object_new", "arg_list_opt", "arg_list",
  "param_list_opt", "param_list", "type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-166)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -166,     6,   281,  -166,  -166,  -166,  -166,  -166,     9,    10,
     -12,  -166,  -166,  -166,  -166,  -166,  -166,    14,  -166,     2,
    -166,    -7,    22,    26,   -10,   104,  -166,  -166,    34,    36,
      38,    40,    43,    54,    -6,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,    60,    80,  -166,  -166,  -166,  -166,    61,   104,
     104,   104,   279,  -166,    67,  -166,  -166,    16,    88,    57,
      86,   104,   104,   104,   104,   104,  -166,    69,  -166,  -166,
     140,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,  -166,    93,    94,    75,  -166,  -166,
      96,  -166,    88,    76,   160,   180,   200,   296,   347,    82,
      87,    84,  -166,    42,    42,  -166,  -166,  -166,   128,   128,
     128,   128,   128,   128,   267,   360,    89,    90,  -166,    95,
    -166,    88,    92,    92,    97,  -166,  -166,   104,  -166,   104,
      26,  -166,    98,  -166,  -166,   116,  -166,  -166,   347,   100,
     101,  -166,  -166,    -2,    92,  -166,  -166,   110,    88,  -166,
    -166,  -166,    88,  -166,    52,   118,  -166,    70,   103,   105,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,    59,    98,
    -166,   313,   104,   104,   104,  -166,  -166,  -166,   220,   240,
     330,   133,   133,  -166,  -166,   127,  -166,    63,   133,  -166,
    -166,  -166,  -166
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,    97,    98,    99,   100,     0,     0,
       0,   101,     4,     7,     5,     6,     2,     0,    10,     0,
      26,     0,     0,    93,     0,     0,     8,    12,     0,     0,
      94,     0,     0,     0,     0,    25,    27,    33,    34,    32,
      30,    31,     0,     0,    76,    77,    78,    79,    80,     0,
       0,     0,     0,    84,    75,    82,    83,     0,     0,     0,
       0,     0,     0,     0,     0,    89,    55,     0,    74,    73,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     9,     0,     0,     0,    13,    15,
       0,    95,     0,     0,     0,     0,     0,     0,    91,     0,
      90,     0,    81,    60,    61,    62,    63,    64,    65,    66,
      67,    69,    68,    70,    71,    72,    85,     0,    11,     0,
      18,     0,     0,     0,     0,    58,    87,     0,    88,    89,
      93,    14,     0,    96,    40,    36,    38,    59,    92,     0,
       0,    21,    19,     0,     0,    35,    86,     0,    28,    39,
      41,    37,     0,    22,     0,     0,    16,     0,     0,     0,
      20,    29,    45,    46,    44,    47,    42,    43,     0,     0,
      57,     0,     0,     0,     0,    23,    17,    56,     0,     0,
       0,     0,     0,    24,    53,    49,    51,     0,     0,    48,
      52,    54,    50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,  -166,   -29,  -166,  -166,  -166,  -166,  -166,     5,
    -166,  -166,  -166,  -119,  -166,    -9,  -166,  -166,  -166,  -165,
    -166,  -142,  -166,  -140,  -123,   -23,  -166,  -166,   -24,  -166,
      50,  -166,    51,  -166,   -50
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    12,    13,    14,    22,    57,    88,    89,
     169,    15,   132,   142,   148,   153,    16,    24,   154,    36,
      37,   145,    38,   135,   143,   161,   162,   189,   163,   185,
     187,    39,   165,    40,    41,    98,    53,    54,    55,    56,
      99,   100,    29,    30,    17
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    31,    52,    32,   136,    33,     3,    90,    91,    31,
      34,    32,   164,    33,   166,    25,    64,   186,    34,     4,
       5,     6,     7,   192,    86,   151,    68,    69,    70,    18,
      19,   167,    20,    26,    21,    35,    65,    11,    94,    95,
      96,    97,   120,   149,    23,   164,    28,   166,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,    87,   157,   158,   167,   159,    27,    33,    73,    74,
      75,   133,    34,   157,   158,    58,   159,    60,    33,    59,
      92,   174,    61,    34,    43,    62,    44,    45,    46,    47,
      48,     4,     5,     6,     7,    49,    63,   160,   155,   175,
      66,    67,   156,    65,   138,    85,    93,    50,   190,    11,
     170,   101,    51,   116,   117,   118,   119,   121,    43,    42,
      44,    45,    46,    47,    48,   126,   127,   128,   144,    49,
      42,   129,   130,   152,   171,   131,   134,   137,   168,   188,
     176,    50,   141,   146,   147,   172,    51,   173,   150,   178,
     179,   180,    71,    72,    73,    74,    75,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,   184,   191,   139,
       0,   140,     0,   102,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,     0,     0,
       0,     0,     0,   122,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,     0,     0,
       0,     0,     0,   123,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,     0,     0,
       0,     0,     0,   124,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,     0,     0,
       0,     0,     0,   181,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,     0,     0,
       0,     0,     0,   182,     4,     5,     6,     7,     8,     9,
      10,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    11,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,     0,     0,     0,    84,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,     0,     0,     0,   125,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
       0,     0,     0,   177,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,     0,     0,     0,
     183,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82
};

static const yytype_int16 yycheck[] =
{
      24,    11,    25,    13,   123,    15,     0,    57,    58,    11,
      20,    13,   154,    15,   154,    22,    22,   182,    20,     3,
       4,     5,     6,   188,     8,   144,    49,    50,    51,    20,
      20,   154,    44,    40,    20,    45,    42,    21,    61,    62,
      63,    64,    92,    45,    42,   187,    20,   187,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    45,    10,    11,   187,    13,    44,    15,    26,    27,
      28,   121,    20,    10,    11,    41,    13,    39,    15,    43,
      23,    22,    42,    20,    14,    42,    16,    17,    18,    19,
      20,     3,     4,     5,     6,    25,    42,    45,   148,    40,
      40,    21,   152,    42,   127,    38,    20,    37,    45,    21,
      40,    42,    42,    20,    20,    40,    20,    41,    14,   143,
      16,    17,    18,    19,    20,    43,    39,    43,    12,    25,
     154,    42,    42,    23,   157,    40,    44,    40,    20,    12,
     169,    37,    44,    43,    43,    42,    42,    42,   143,   172,
     173,   174,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,   187,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    44,   187,   129,
      -1,   130,    -1,    43,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    43,     3,     4,     5,     6,     7,     8,
       9,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    21,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    40,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    40,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    40,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      40,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    48,    49,     0,     3,     4,     5,     6,     7,     8,
       9,    21,    50,    51,    52,    58,    63,    91,    20,    20,
      44,    20,    53,    42,    64,    22,    40,    44,    20,    89,
      90,    11,    13,    15,    20,    45,    66,    67,    69,    78,
      80,    81,    85,    14,    16,    17,    18,    19,    20,    25,
      37,    42,    82,    83,    84,    85,    86,    54,    41,    43,
      39,    42,    42,    42,    22,    42,    40,    21,    82,    82,
      82,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    40,    38,     8,    45,    55,    56,
      91,    91,    23,    20,    82,    82,    82,    82,    82,    87,
      88,    42,    43,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    20,    20,    40,    20,
      91,    41,    43,    43,    43,    40,    43,    39,    43,    42,
      42,    40,    59,    91,    44,    70,    70,    40,    82,    87,
      89,    44,    60,    71,    12,    68,    43,    43,    61,    45,
      66,    70,    23,    62,    65,    91,    91,    10,    11,    13,
      45,    72,    73,    75,    78,    79,    80,    81,    20,    57,
      40,    82,    42,    42,    22,    40,    60,    40,    82,    82,
      82,    43,    43,    40,    44,    76,    76,    77,    12,    74,
      45,    72,    76
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    50,    51,    51,
      53,    52,    54,    54,    55,    55,    57,    56,    59,    58,
      60,    61,    61,    62,    62,    63,    64,    64,    65,    65,
      66,    66,    66,    66,    66,    67,    68,    68,    69,    70,
      71,    71,    72,    72,    72,    72,    72,    72,    73,    74,
      74,    75,    76,    77,    77,    78,    79,    79,    80,    81,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    83,    83,    83,    83,
      83,    83,    83,    83,    84,    84,    84,    85,    86,    87,
      87,    88,    88,    89,    89,    90,    90,    91,    91,    91,
      91,    91
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     1,     1,     1,     3,     5,
       0,     7,     0,     2,     3,     1,     0,     9,     0,     9,
       4,     0,     2,     3,     5,     4,     0,     2,     0,     2,
       1,     1,     1,     1,     1,     6,     0,     2,     5,     3,
       0,     2,     1,     1,     1,     1,     1,     1,     6,     0,
       2,     5,     3,     0,     2,     2,     3,     2,     4,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     1,     3,     6,     4,     4,     0,
       1,     1,     3,     0,     1,     3,     5,     1,     1,     1,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 8: /* global_var_decl: type ID SEMI  */
#line 120 "miku.y"
      {
        Type t = *(yyvsp[-2].typep); delete (yyvsp[-2].typep);
        std::string name((yyvsp[-1].sval)); std::free((yyvsp[-1].sval));
        /* global variable declaration */
        declare_var(g_tm, yylineno, name, t, std::nullopt, /*isGlobal=*/true);
      }
#line 1344 "miku.tab.cpp"
    break;

  case 9: /* global_var_decl: type ID ASSIGN expr SEMI  */
#line 127 "miku.y"
      {
        Type t = *(yyvsp[-4].typep); delete (yyvsp[-4].typep);
        std::string name((yyvsp[-3].sval)); std::free((yyvsp[-3].sval));

        /* optional init value (if evaluator supports it) */
        std::optional<Value> initVal;
        if ((yyvsp[-1].expr) && (yyvsp[-1].expr)->type != t) {
            semantic_error(g_tm, yylineno,
                "Type mismatch in init of '" + name + "': declared " +
                type_to_string(t) + " but got " + type_to_string((yyvsp[-1].expr)->type));
        }
        if ((yyvsp[-1].expr) && (yyvsp[-1].expr)->node) initVal = (yyvsp[-1].expr)->node->eval(g_tm);

        declare_var(g_tm, yylineno, name, t, initVal, /*isGlobal=*/true);
        destroy_exprinfo((yyvsp[-1].expr));
      }
#line 1365 "miku.tab.cpp"
    break;

  case 10: /* $@1: %empty  */
#line 151 "miku.y"
      {
        std::string cname((yyvsp[0].sval)); std::free((yyvsp[0].sval));
        declare_class_begin(g_tm, yylineno, cname);
      }
#line 1374 "miku.tab.cpp"
    break;

  case 11: /* class_def: KW_CLASS ID $@1 LBRACE class_members RBRACE SEMI  */
#line 156 "miku.y"
      {
        declare_class_end(g_tm);
      }
#line 1382 "miku.tab.cpp"
    break;

  case 14: /* class_member: type ID SEMI  */
#line 168 "miku.y"
      {
        Type t = *(yyvsp[-2].typep); delete (yyvsp[-2].typep);
        std::string field((yyvsp[-1].sval)); std::free((yyvsp[-1].sval));

        /* current class context should be stored in g_tm;
           if your function expects class name, pass it here instead of "" */
        declare_class_field(g_tm, yylineno, /*className=*/"", field, t);
      }
#line 1395 "miku.tab.cpp"
    break;

  case 16: /* $@2: %empty  */
#line 185 "miku.y"
      {
        std::string mname((yyvsp[-5].sval)); std::free((yyvsp[-5].sval));
        Type ret = *(yyvsp[0].typep); delete (yyvsp[0].typep);
        ParamList params = *(yyvsp[-3].params); destroy_paramlist((yyvsp[-3].params));

        declare_method(g_tm, yylineno, /*className=*/"", mname, ret, params);

        /* enter method scope and bind params */
        g_tm.push_scope("method:" + mname);
        for (const auto& p : params.v) {
            declare_var(g_tm, p.line, p.name, p.type, std::nullopt, /*isGlobal=*/false);
        }
      }
#line 1413 "miku.tab.cpp"
    break;

  case 17: /* method_def: KW_FUNC ID LPAREN param_list_opt RPAREN ARROW type $@2 func_block  */
#line 199 "miku.y"
      {
        g_tm.pop_scope();
      }
#line 1421 "miku.tab.cpp"
    break;

  case 18: /* $@3: %empty  */
#line 210 "miku.y"
      {
        std::string fname((yyvsp[-5].sval)); std::free((yyvsp[-5].sval));
        Type ret = *(yyvsp[0].typep); delete (yyvsp[0].typep);
        ParamList params = *(yyvsp[-3].params); destroy_paramlist((yyvsp[-3].params));

        declare_func(g_tm, yylineno, fname, ret, params);

        /* enter function scope and bind params */
        g_tm.push_scope("func:" + fname);
        for (const auto& p : params.v) {
            declare_var(g_tm, p.line, p.name, p.type, std::nullopt, /*isGlobal=*/false);
        }
      }
#line 1439 "miku.tab.cpp"
    break;

  case 19: /* func_def: KW_FUNC ID LPAREN param_list_opt RPAREN ARROW type $@3 func_block  */
#line 224 "miku.y"
      {
        g_tm.pop_scope();
      }
#line 1447 "miku.tab.cpp"
    break;

  case 23: /* local_decl: type ID SEMI  */
#line 245 "miku.y"
      {
        Type t = *(yyvsp[-2].typep); delete (yyvsp[-2].typep);
        std::string name((yyvsp[-1].sval)); std::free((yyvsp[-1].sval));
        declare_var(g_tm, yylineno, name, t, std::nullopt, /*isGlobal=*/false);
      }
#line 1457 "miku.tab.cpp"
    break;

  case 24: /* local_decl: type ID ASSIGN expr SEMI  */
#line 251 "miku.y"
      {
        Type t = *(yyvsp[-4].typep); delete (yyvsp[-4].typep);
        std::string name((yyvsp[-3].sval)); std::free((yyvsp[-3].sval));

        std::optional<Value> initVal;
        if ((yyvsp[-1].expr) && (yyvsp[-1].expr)->type != t) {
            semantic_error(g_tm, yylineno,
                "Type mismatch in init of '" + name + "': declared " +
                type_to_string(t) + " but got " + type_to_string((yyvsp[-1].expr)->type));
        }
        if ((yyvsp[-1].expr) && (yyvsp[-1].expr)->node) initVal = (yyvsp[-1].expr)->node->eval(g_tm);

        declare_var(g_tm, yylineno, name, t, initVal, /*isGlobal=*/false);
        destroy_exprinfo((yyvsp[-1].expr));
      }
#line 1477 "miku.tab.cpp"
    break;

  case 27: /* main_stmt_list: main_stmt_list stmt_main  */
#line 280 "miku.y"
      {
        if ((yyvsp[0].ast)) { (yyvsp[0].ast)->eval(g_tm); delete (yyvsp[0].ast); }
      }
#line 1485 "miku.tab.cpp"
    break;

  case 29: /* stmt_list_func: stmt_list_func stmt_func  */
#line 294 "miku.y"
      {
        if ((yyvsp[0].ast)) delete (yyvsp[0].ast);
      }
#line 1493 "miku.tab.cpp"
    break;

  case 30: /* stmt_main: assign_stmt  */
#line 306 "miku.y"
                               { (yyval.ast) = (yyvsp[0].ast); }
#line 1499 "miku.tab.cpp"
    break;

  case 31: /* stmt_main: print_stmt  */
#line 307 "miku.y"
                               { (yyval.ast) = (yyvsp[0].ast); }
#line 1505 "miku.tab.cpp"
    break;

  case 32: /* stmt_main: call_stmt  */
#line 308 "miku.y"
                               { (yyval.ast) = nullptr; }
#line 1511 "miku.tab.cpp"
    break;

  case 33: /* stmt_main: if_stmt_main  */
#line 309 "miku.y"
                               { (yyval.ast) = nullptr; }
#line 1517 "miku.tab.cpp"
    break;

  case 34: /* stmt_main: while_stmt_main  */
#line 310 "miku.y"
                               { (yyval.ast) = nullptr; }
#line 1523 "miku.tab.cpp"
    break;

  case 35: /* if_stmt_main: KW_IF LPAREN expr RPAREN block_no_decls_main else_opt_main  */
#line 316 "miku.y"
      {
        if ((yyvsp[-3].expr) && (yyvsp[-3].expr)->type.kind != Type::Kind::BOOL) {
            semantic_error(g_tm, (yyvsp[-3].expr)->line,
                "if() condition must be bool, got " + type_to_string((yyvsp[-3].expr)->type));
        }
        destroy_exprinfo((yyvsp[-3].expr));
      }
#line 1535 "miku.tab.cpp"
    break;

  case 38: /* while_stmt_main: KW_WHILE LPAREN expr RPAREN block_no_decls_main  */
#line 332 "miku.y"
      {
        if ((yyvsp[-2].expr) && (yyvsp[-2].expr)->type.kind != Type::Kind::BOOL) {
            semantic_error(g_tm, (yyvsp[-2].expr)->line,
                "while() condition must be bool, got " + type_to_string((yyvsp[-2].expr)->type));
        }
        destroy_exprinfo((yyvsp[-2].expr));
      }
#line 1547 "miku.tab.cpp"
    break;

  case 41: /* stmt_list_no_decls_main: stmt_list_no_decls_main stmt_main  */
#line 349 "miku.y"
      {
        /* main evaluates only the top-level stmt_main list;
           inside blocks, spec says if/while are not executed anyway.
           So we just delete AST if any. */
        if ((yyvsp[0].ast)) delete (yyvsp[0].ast);
      }
#line 1558 "miku.tab.cpp"
    break;

  case 42: /* stmt_func: assign_stmt  */
#line 362 "miku.y"
                               { (yyval.ast) = (yyvsp[0].ast); }
#line 1564 "miku.tab.cpp"
    break;

  case 43: /* stmt_func: print_stmt  */
#line 363 "miku.y"
                               { (yyval.ast) = (yyvsp[0].ast); }
#line 1570 "miku.tab.cpp"
    break;

  case 44: /* stmt_func: call_stmt  */
#line 364 "miku.y"
                               { (yyval.ast) = nullptr; }
#line 1576 "miku.tab.cpp"
    break;

  case 45: /* stmt_func: if_stmt_func  */
#line 365 "miku.y"
                               { (yyval.ast) = nullptr; }
#line 1582 "miku.tab.cpp"
    break;

  case 46: /* stmt_func: while_stmt_func  */
#line 366 "miku.y"
                               { (yyval.ast) = nullptr; }
#line 1588 "miku.tab.cpp"
    break;

  case 47: /* stmt_func: return_stmt  */
#line 367 "miku.y"
                               { (yyval.ast) = nullptr; }
#line 1594 "miku.tab.cpp"
    break;

  case 48: /* if_stmt_func: KW_IF LPAREN expr RPAREN block_no_decls_func else_opt_func  */
#line 373 "miku.y"
      {
        if ((yyvsp[-3].expr) && (yyvsp[-3].expr)->type.kind != Type::Kind::BOOL) {
            semantic_error(g_tm, (yyvsp[-3].expr)->line,
                "if() condition must be bool, got " + type_to_string((yyvsp[-3].expr)->type));
        }
        destroy_exprinfo((yyvsp[-3].expr));
      }
#line 1606 "miku.tab.cpp"
    break;

  case 51: /* while_stmt_func: KW_WHILE LPAREN expr RPAREN block_no_decls_func  */
#line 389 "miku.y"
      {
        if ((yyvsp[-2].expr) && (yyvsp[-2].expr)->type.kind != Type::Kind::BOOL) {
            semantic_error(g_tm, (yyvsp[-2].expr)->line,
                "while() condition must be bool, got " + type_to_string((yyvsp[-2].expr)->type));
        }
        destroy_exprinfo((yyvsp[-2].expr));
      }
#line 1618 "miku.tab.cpp"
    break;

  case 54: /* stmt_list_no_decls_func: stmt_list_no_decls_func stmt_func  */
#line 406 "miku.y"
      {
        if ((yyvsp[0].ast)) delete (yyvsp[0].ast);
      }
#line 1626 "miku.tab.cpp"
    break;

  case 55: /* call_stmt: call_expr SEMI  */
#line 418 "miku.y"
      {
        destroy_exprinfo((yyvsp[-1].expr));
      }
#line 1634 "miku.tab.cpp"
    break;

  case 56: /* return_stmt: KW_RETURN expr SEMI  */
#line 425 "miku.y"
                          { destroy_exprinfo((yyvsp[-1].expr)); }
#line 1640 "miku.tab.cpp"
    break;

  case 57: /* return_stmt: KW_RETURN SEMI  */
#line 426 "miku.y"
                          { }
#line 1646 "miku.tab.cpp"
    break;

  case 58: /* assign_stmt: ID ASSIGN expr SEMI  */
#line 432 "miku.y"
      {
        std::string name((yyvsp[-3].sval)); std::free((yyvsp[-3].sval));

        /* left side must be declared variable */
        ExprInfo* idinfo = make_ident(g_tm, yylineno, name);
        ASTNode* rhs = ((yyvsp[-1].expr) ? (yyvsp[-1].expr)->node : ASTNode::other(yylineno, Type::Error()));

        if (!idinfo || idinfo->type.kind == Type::Kind::ERROR) {
            (yyval.ast) = ASTNode::assign(yylineno, name, Type::Error(), rhs);
        } else {
            if ((yyvsp[-1].expr) && idinfo->type != (yyvsp[-1].expr)->type) {
                semantic_error(g_tm, yylineno,
                    "Type mismatch in assignment to '" + name + "': left " +
                    type_to_string(idinfo->type) + ", right " + type_to_string((yyvsp[-1].expr)->type));
            }
            (yyval.ast) = ASTNode::assign(yylineno, name, idinfo->type, rhs);
        }

        destroy_exprinfo(idinfo);
        if ((yyvsp[-1].expr)) { (yyvsp[-1].expr)->node = nullptr; destroy_exprinfo((yyvsp[-1].expr)); }
      }
#line 1672 "miku.tab.cpp"
    break;

  case 59: /* print_stmt: KW_PRINT LPAREN expr RPAREN SEMI  */
#line 458 "miku.y"
      {
        ASTNode* e = ((yyvsp[-2].expr) ? (yyvsp[-2].expr)->node : ASTNode::other(yylineno, Type::Error()));
        (yyval.ast) = ASTNode::print(yylineno, e);

        if ((yyvsp[-2].expr)) { (yyvsp[-2].expr)->node = nullptr; destroy_exprinfo((yyvsp[-2].expr)); }
      }
#line 1683 "miku.tab.cpp"
    break;

  case 60: /* expr: expr PLUS expr  */
#line 471 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, "+",  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1689 "miku.tab.cpp"
    break;

  case 61: /* expr: expr MINUS expr  */
#line 472 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, "-",  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1695 "miku.tab.cpp"
    break;

  case 62: /* expr: expr MUL expr  */
#line 473 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, "*",  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1701 "miku.tab.cpp"
    break;

  case 63: /* expr: expr DIV expr  */
#line 474 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, "/",  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1707 "miku.tab.cpp"
    break;

  case 64: /* expr: expr MOD expr  */
#line 475 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, "%",  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1713 "miku.tab.cpp"
    break;

  case 65: /* expr: expr EQ expr  */
#line 477 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, "==", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1719 "miku.tab.cpp"
    break;

  case 66: /* expr: expr NEQ expr  */
#line 478 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, "!=", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1725 "miku.tab.cpp"
    break;

  case 67: /* expr: expr LT expr  */
#line 479 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, "<",  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1731 "miku.tab.cpp"
    break;

  case 68: /* expr: expr LE expr  */
#line 480 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, "<=", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1737 "miku.tab.cpp"
    break;

  case 69: /* expr: expr GT expr  */
#line 481 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, ">",  (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1743 "miku.tab.cpp"
    break;

  case 70: /* expr: expr GE expr  */
#line 482 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, ">=", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1749 "miku.tab.cpp"
    break;

  case 71: /* expr: expr AND expr  */
#line 484 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, "&&", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1755 "miku.tab.cpp"
    break;

  case 72: /* expr: expr OR expr  */
#line 485 "miku.y"
                            { (yyval.expr) = make_binary_expr(g_tm, yylineno, "||", (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 1761 "miku.tab.cpp"
    break;

  case 73: /* expr: NOT expr  */
#line 487 "miku.y"
                            { (yyval.expr) = make_unary_expr (g_tm, yylineno, "!",  (yyvsp[0].expr)); }
#line 1767 "miku.tab.cpp"
    break;

  case 74: /* expr: MINUS expr  */
#line 489 "miku.y"
                            { (yyval.expr) = make_unary_expr (g_tm, yylineno, "u-", (yyvsp[0].expr)); }
#line 1773 "miku.tab.cpp"
    break;

  case 75: /* expr: postfix  */
#line 491 "miku.y"
                            { (yyval.expr) = (yyvsp[0].expr); }
#line 1779 "miku.tab.cpp"
    break;

  case 76: /* atom: INT_LIT  */
#line 496 "miku.y"
                            { (yyval.expr) = make_lit_int   (yylineno, (yyvsp[0].ival)); }
#line 1785 "miku.tab.cpp"
    break;

  case 77: /* atom: FLOAT_LIT  */
#line 497 "miku.y"
                            { (yyval.expr) = make_lit_float (yylineno, (yyvsp[0].fval)); }
#line 1791 "miku.tab.cpp"
    break;

  case 78: /* atom: BOOL_LIT  */
#line 498 "miku.y"
                            { (yyval.expr) = make_lit_bool  (yylineno, (yyvsp[0].bval) != 0); }
#line 1797 "miku.tab.cpp"
    break;

  case 79: /* atom: STRING_LIT  */
#line 499 "miku.y"
                            { std::string s((yyvsp[0].sval)); std::free((yyvsp[0].sval)); (yyval.expr) = make_lit_string(yylineno, s); }
#line 1803 "miku.tab.cpp"
    break;

  case 80: /* atom: ID  */
#line 500 "miku.y"
                            { std::string n((yyvsp[0].sval)); std::free((yyvsp[0].sval)); (yyval.expr) = make_ident(g_tm, yylineno, n); }
#line 1809 "miku.tab.cpp"
    break;

  case 81: /* atom: LPAREN expr RPAREN  */
#line 501 "miku.y"
                            { (yyval.expr) = (yyvsp[-1].expr); }
#line 1815 "miku.tab.cpp"
    break;

  case 82: /* atom: call_expr  */
#line 502 "miku.y"
                            { (yyval.expr) = (yyvsp[0].expr); }
#line 1821 "miku.tab.cpp"
    break;

  case 83: /* atom: object_new  */
#line 503 "miku.y"
                            { (yyval.expr) = (yyvsp[0].expr); }
#line 1827 "miku.tab.cpp"
    break;

  case 84: /* postfix: atom  */
#line 509 "miku.y"
           { (yyval.expr) = (yyvsp[0].expr); }
#line 1833 "miku.tab.cpp"
    break;

  case 85: /* postfix: postfix DOT ID  */
#line 512 "miku.y"
      {
        std::string field((yyvsp[0].sval)); std::free((yyvsp[0].sval));
        ExprInfo* out = make_other_from_field_access(g_tm, yylineno, *(yyvsp[-2].expr), field);
        destroy_exprinfo((yyvsp[-2].expr));
        (yyval.expr) = out;
      }
#line 1844 "miku.tab.cpp"
    break;

  case 86: /* postfix: postfix DOT ID LPAREN arg_list_opt RPAREN  */
#line 520 "miku.y"
      {
        std::string m((yyvsp[-3].sval)); std::free((yyvsp[-3].sval));
        ArgList args = *(yyvsp[-1].args); destroy_arglist((yyvsp[-1].args));
        ExprInfo* out = make_other_from_method_call(g_tm, yylineno, *(yyvsp[-5].expr), m, args);
        destroy_exprinfo((yyvsp[-5].expr));
        (yyval.expr) = out;
      }
#line 1856 "miku.tab.cpp"
    break;

  case 87: /* call_expr: ID LPAREN arg_list_opt RPAREN  */
#line 532 "miku.y"
      {
        std::string fname((yyvsp[-3].sval)); std::free((yyvsp[-3].sval));
        ArgList args = *(yyvsp[-1].args); destroy_arglist((yyvsp[-1].args));
        (yyval.expr) = make_other_from_func_call(g_tm, yylineno, fname, args);
      }
#line 1866 "miku.tab.cpp"
    break;

  case 88: /* object_new: KW_NEW TYPE_NAME LPAREN RPAREN  */
#line 542 "miku.y"
      {
        std::string cname((yyvsp[-2].sval)); std::free((yyvsp[-2].sval));
        (yyval.expr) = make_other_from_object_new(g_tm, yylineno, cname);
      }
#line 1875 "miku.tab.cpp"
    break;

  case 89: /* arg_list_opt: %empty  */
#line 550 "miku.y"
                            { (yyval.args) = arglist_empty(); }
#line 1881 "miku.tab.cpp"
    break;

  case 90: /* arg_list_opt: arg_list  */
#line 551 "miku.y"
                            { (yyval.args) = (yyvsp[0].args); }
#line 1887 "miku.tab.cpp"
    break;

  case 91: /* arg_list: expr  */
#line 555 "miku.y"
                            { (yyval.args) = arglist_single((yyvsp[0].expr)); }
#line 1893 "miku.tab.cpp"
    break;

  case 92: /* arg_list: arg_list COMMA expr  */
#line 556 "miku.y"
                             { (yyval.args) = arglist_append((yyvsp[-2].args), (yyvsp[0].expr)); }
#line 1899 "miku.tab.cpp"
    break;

  case 93: /* param_list_opt: %empty  */
#line 564 "miku.y"
                              { (yyval.params) = paramlist_empty(); }
#line 1905 "miku.tab.cpp"
    break;

  case 94: /* param_list_opt: param_list  */
#line 565 "miku.y"
                              { (yyval.params) = (yyvsp[0].params); }
#line 1911 "miku.tab.cpp"
    break;

  case 95: /* param_list: ID COLON type  */
#line 570 "miku.y"
      {
        std::string n((yyvsp[-2].sval)); std::free((yyvsp[-2].sval));
        Type t = *(yyvsp[0].typep); delete (yyvsp[0].typep);
        (yyval.params) = paramlist_single(n, t, yylineno);
      }
#line 1921 "miku.tab.cpp"
    break;

  case 96: /* param_list: param_list COMMA ID COLON type  */
#line 576 "miku.y"
      {
        std::string n((yyvsp[-2].sval)); std::free((yyvsp[-2].sval));
        Type t = *(yyvsp[0].typep); delete (yyvsp[0].typep);
        (yyval.params) = paramlist_append((yyvsp[-4].params), n, t, yylineno);
      }
#line 1931 "miku.tab.cpp"
    break;

  case 97: /* type: KW_INT  */
#line 588 "miku.y"
                             { (yyval.typep) = new Type(Type::Int()); }
#line 1937 "miku.tab.cpp"
    break;

  case 98: /* type: KW_FLOAT  */
#line 589 "miku.y"
                             { (yyval.typep) = new Type(Type::Float()); }
#line 1943 "miku.tab.cpp"
    break;

  case 99: /* type: KW_STRING  */
#line 590 "miku.y"
                             { (yyval.typep) = new Type(Type::String()); }
#line 1949 "miku.tab.cpp"
    break;

  case 100: /* type: KW_BOOL  */
#line 591 "miku.y"
                             { (yyval.typep) = new Type(Type::Bool()); }
#line 1955 "miku.tab.cpp"
    break;

  case 101: /* type: TYPE_NAME  */
#line 593 "miku.y"
      {
        std::string tn((yyvsp[0].sval)); std::free((yyvsp[0].sval));
        Type t = resolve_type_name(g_tm, yylineno, tn);
        (yyval.typep) = new Type(t);
      }
#line 1965 "miku.tab.cpp"
    break;


#line 1969 "miku.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 600 "miku.y"


void yyerror(const char* s) {
    std::fprintf(stderr, "[PARSE] %s at line %d\n", s, yylineno);
}
