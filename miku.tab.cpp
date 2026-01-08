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
#line 1 "miku.y"

#include "miku_ast.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

extern int yylineno;
int yylex(void);
void yyerror(const char* s);

static Program* g_program = nullptr;

#line 85 "miku.tab.cpp"

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
  YYSYMBOL_KW_FEAT = 3,                    /* KW_FEAT  */
  YYSYMBOL_KW_SYSTEM = 4,                  /* KW_SYSTEM  */
  YYSYMBOL_KW_MIKUDATA = 5,                /* KW_MIKUDATA  */
  YYSYMBOL_KW_TRACK = 6,                   /* KW_TRACK  */
  YYSYMBOL_KW_LET = 7,                     /* KW_LET  */
  YYSYMBOL_KW_WISH = 8,                    /* KW_WISH  */
  YYSYMBOL_KW_REGRET = 9,                  /* KW_REGRET  */
  YYSYMBOL_KW_ROLLING = 10,                /* KW_ROLLING  */
  YYSYMBOL_KW_OFFER = 11,                  /* KW_OFFER  */
  YYSYMBOL_KW_PRINT = 12,                  /* KW_PRINT  */
  YYSYMBOL_KW_SUMMON = 13,                 /* KW_SUMMON  */
  YYSYMBOL_KW_LEEK = 14,                   /* KW_LEEK  */
  YYSYMBOL_KW_RIN = 15,                    /* KW_RIN  */
  YYSYMBOL_KW_SCROLL = 16,                 /* KW_SCROLL  */
  YYSYMBOL_KW_CODE = 17,                   /* KW_CODE  */
  YYSYMBOL_KW_GHOST = 18,                  /* KW_GHOST  */
  YYSYMBOL_ANGEL = 19,                     /* ANGEL  */
  YYSYMBOL_VIRUS = 20,                     /* VIRUS  */
  YYSYMBOL_INT_LIT = 21,                   /* INT_LIT  */
  YYSYMBOL_FLOAT_LIT = 22,                 /* FLOAT_LIT  */
  YYSYMBOL_STRING_LIT = 23,                /* STRING_LIT  */
  YYSYMBOL_ID = 24,                        /* ID  */
  YYSYMBOL_TYPE_NAME = 25,                 /* TYPE_NAME  */
  YYSYMBOL_ARROW = 26,                     /* ARROW  */
  YYSYMBOL_ASSIGN = 27,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 28,                      /* PLUS  */
  YYSYMBOL_MINUS = 29,                     /* MINUS  */
  YYSYMBOL_MUL = 30,                       /* MUL  */
  YYSYMBOL_DIV = 31,                       /* DIV  */
  YYSYMBOL_MOD = 32,                       /* MOD  */
  YYSYMBOL_EQ = 33,                        /* EQ  */
  YYSYMBOL_NEQ = 34,                       /* NEQ  */
  YYSYMBOL_LT = 35,                        /* LT  */
  YYSYMBOL_GT = 36,                        /* GT  */
  YYSYMBOL_LE = 37,                        /* LE  */
  YYSYMBOL_GE = 38,                        /* GE  */
  YYSYMBOL_AND = 39,                       /* AND  */
  YYSYMBOL_OR = 40,                        /* OR  */
  YYSYMBOL_NOT = 41,                       /* NOT  */
  YYSYMBOL_DOT = 42,                       /* DOT  */
  YYSYMBOL_COMMA = 43,                     /* COMMA  */
  YYSYMBOL_SEMI = 44,                      /* SEMI  */
  YYSYMBOL_COLON = 45,                     /* COLON  */
  YYSYMBOL_LPAREN = 46,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 47,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 48,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 49,                    /* RBRACE  */
  YYSYMBOL_UMINUS = 50,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_program = 52,                   /* program  */
  YYSYMBOL_opt_feat = 53,                  /* opt_feat  */
  YYSYMBOL_global_items = 54,              /* global_items  */
  YYSYMBOL_struct_def = 55,                /* struct_def  */
  YYSYMBOL_struct_members = 56,            /* struct_members  */
  YYSYMBOL_field_decl = 57,                /* field_decl  */
  YYSYMBOL_method_def = 58,                /* method_def  */
  YYSYMBOL_func_def = 59,                  /* func_def  */
  YYSYMBOL_param_list_opt = 60,            /* param_list_opt  */
  YYSYMBOL_param_list = 61,                /* param_list  */
  YYSYMBOL_type = 62,                      /* type  */
  YYSYMBOL_block = 63,                     /* block  */
  YYSYMBOL_stmt_list = 64,                 /* stmt_list  */
  YYSYMBOL_stmt = 65,                      /* stmt  */
  YYSYMBOL_let_stmt = 66,                  /* let_stmt  */
  YYSYMBOL_lvalue = 67,                    /* lvalue  */
  YYSYMBOL_assign_stmt = 68,               /* assign_stmt  */
  YYSYMBOL_print_stmt = 69,                /* print_stmt  */
  YYSYMBOL_expr_stmt = 70,                 /* expr_stmt  */
  YYSYMBOL_if_stmt = 71,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 72,                /* while_stmt  */
  YYSYMBOL_return_stmt = 73,               /* return_stmt  */
  YYSYMBOL_expr = 74,                      /* expr  */
  YYSYMBOL_postfix = 75,                   /* postfix  */
  YYSYMBOL_atom = 76,                      /* atom  */
  YYSYMBOL_call = 77,                      /* call  */
  YYSYMBOL_summon_expr = 78,               /* summon_expr  */
  YYSYMBOL_struct_lit = 79,                /* struct_lit  */
  YYSYMBOL_field_inits_opt = 80,           /* field_inits_opt  */
  YYSYMBOL_field_inits = 81,               /* field_inits  */
  YYSYMBOL_arg_list_opt = 82,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 83                   /* arg_list  */
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   375

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  175

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   158,   158,   196,   197,   201,   202,   204,   210,   220,
     221,   226,   234,   245,   264,   283,   284,   288,   296,   306,
     307,   308,   309,   310,   311,   316,   326,   327,   332,   333,
     334,   335,   336,   337,   338,   342,   347,   356,   364,   373,
     384,   389,   394,   396,   401,   406,   408,   418,   419,   420,
     421,   422,   424,   425,   426,   427,   428,   429,   431,   432,
     434,   435,   437,   441,   442,   444,   455,   456,   457,   458,
     459,   460,   461,   462,   463,   464,   468,   479,   484,   500,
     501,   505,   515,   527,   528,   532,   534
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
  "\"end of file\"", "error", "\"invalid token\"", "KW_FEAT", "KW_SYSTEM",
  "KW_MIKUDATA", "KW_TRACK", "KW_LET", "KW_WISH", "KW_REGRET",
  "KW_ROLLING", "KW_OFFER", "KW_PRINT", "KW_SUMMON", "KW_LEEK", "KW_RIN",
  "KW_SCROLL", "KW_CODE", "KW_GHOST", "ANGEL", "VIRUS", "INT_LIT",
  "FLOAT_LIT", "STRING_LIT", "ID", "TYPE_NAME", "ARROW", "ASSIGN", "PLUS",
  "MINUS", "MUL", "DIV", "MOD", "EQ", "NEQ", "LT", "GT", "LE", "GE", "AND",
  "OR", "NOT", "DOT", "COMMA", "SEMI", "COLON", "LPAREN", "RPAREN",
  "LBRACE", "RBRACE", "UMINUS", "$accept", "program", "opt_feat",
  "global_items", "struct_def", "struct_members", "field_decl",
  "method_def", "func_def", "param_list_opt", "param_list", "type",
  "block", "stmt_list", "stmt", "let_stmt", "lvalue", "assign_stmt",
  "print_stmt", "expr_stmt", "if_stmt", "while_stmt", "return_stmt",
  "expr", "postfix", "atom", "call", "summon_expr", "struct_lit",
  "field_inits_opt", "field_inits", "arg_list_opt", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-82)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-38)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -1,     4,    12,   -82,   -30,   -82,     5,   -82,    -2,    -4,
     -82,   -82,   -24,    -8,   -82,    16,    -5,    -3,     0,     2,
      19,     1,    20,   -82,   -82,    14,    23,    41,    30,    14,
     -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,    14,    32,
      16,    34,    33,    14,    35,   -82,   -82,   -82,   -82,    54,
     104,    14,    59,    38,    39,    50,    40,    62,   -82,   -82,
     -82,   -82,   -82,   -21,    42,   117,   117,   117,   -82,   -82,
     -82,   -20,   -82,   -82,   -82,   -82,   -82,   -82,   216,    47,
     -82,   -82,   -82,   -82,    33,   -18,   117,   117,    49,   -82,
     233,   117,    51,   117,    69,   -82,   -82,   136,   117,    74,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   -82,    75,   -82,   117,    14,   156,   176,
     -82,   196,    53,   301,    55,    58,    60,    57,    64,   -82,
     250,   -82,     3,     3,   -82,   -82,   -82,   326,   326,   326,
     326,   326,   326,   337,   314,    63,   267,    81,    33,    33,
      77,   -82,   -82,   117,   117,   -82,    89,   -82,   117,   -82,
     117,   109,   -82,   -82,   301,   301,    86,    72,   284,    33,
     117,   -82,   -82,   -82,   301
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     5,     0,     1,     2,     4,     0,     0,
       6,     7,     0,     0,     9,    15,     0,     0,     0,    16,
       0,     0,     0,    10,    11,     0,     0,     0,     0,     0,
       8,    19,    20,    21,    22,    23,    24,    17,     0,     0,
      15,     0,     0,     0,     0,    12,    26,    14,    18,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    69,    70,
      66,    67,    68,    71,     0,     0,     0,     0,    25,    27,
      28,     0,    29,    30,    34,    31,    32,    33,     0,    62,
      63,    72,    74,    73,     0,     0,     0,     0,    71,    45,
       0,     0,     0,    83,    79,    61,    60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    41,     0,    13,     0,     0,     0,     0,
      46,     0,     0,    85,     0,    84,     0,     0,    80,    75,
       0,    38,    47,    48,    49,    50,    51,    52,    53,    54,
      56,    55,    57,    58,    59,    64,     0,     0,     0,     0,
       0,    77,    76,     0,     0,    78,     0,    39,    83,    35,
       0,    42,    44,    40,    86,    81,     0,     0,     0,     0,
       0,    65,    36,    43,    82
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,   -82,    82,
     -82,   -25,   -81,   -82,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -82,   -82,   -50,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -26,   -82
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     6,    10,    16,    23,    24,    11,    18,
      19,    37,    47,    50,    69,    70,    71,    72,    73,    74,
      75,    76,    77,   123,    79,    80,    81,    82,    83,   127,
     128,   124,   125
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      78,    20,     1,   115,    41,    90,   -37,    98,     4,   116,
       8,     9,     5,    42,     7,    95,    96,    97,    48,    21,
      13,   -37,    99,    12,    14,    93,    84,   117,    31,    32,
      33,    34,    35,   102,   103,   104,   118,   119,    15,    36,
      17,   121,    25,    28,    22,    27,    29,    26,   130,    38,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,    57,    30,    39,   146,   161,   162,    58,
      59,    60,    61,    62,    88,    64,    40,    43,    45,    65,
      51,    46,    49,    85,    86,    87,    91,    92,   173,   114,
      94,    66,   147,   126,    89,    93,    67,   122,   131,   145,
     151,   153,   152,   164,   165,   154,   155,   156,   160,   158,
     168,    52,    53,   166,    54,    55,    56,    57,   169,   171,
     174,   163,    44,    58,    59,    60,    61,    62,    63,    64,
      57,   170,   167,    65,     0,     0,    58,    59,    60,    61,
      62,    88,    64,     0,     0,    66,    65,     0,     0,     0,
      67,     0,     0,    68,     0,     0,     0,     0,    66,     0,
       0,     0,     0,    67,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,   129,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,   148,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,   149,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,   150,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,     0,     0,     0,
     113,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,     0,     0,     0,   120,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,     0,     0,     0,   157,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,     0,     0,
       0,   159,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,     0,     0,     0,   172,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   100,   101,   102,   103,   104,   -38,
     -38,   -38,   -38,   -38,   -38,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110
};

static const yytype_int16 yycheck[] =
{
      50,     6,     3,    84,    29,    55,    27,    27,     4,    27,
       5,     6,     0,    38,    44,    65,    66,    67,    43,    24,
      24,    42,    42,    25,    48,    46,    51,    45,    14,    15,
      16,    17,    18,    30,    31,    32,    86,    87,    46,    25,
      24,    91,    45,    24,    49,    43,    45,    47,    98,    26,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,    13,    44,    24,   116,   148,   149,    19,
      20,    21,    22,    23,    24,    25,    46,    45,    44,    29,
      26,    48,    47,    24,    46,    46,    46,    25,   169,    42,
      48,    41,   117,    24,    44,    46,    46,    46,    24,    24,
      47,    43,    47,   153,   154,    45,    49,    43,    27,    46,
     160,     7,     8,    24,    10,    11,    12,    13,     9,    47,
     170,    44,    40,    19,    20,    21,    22,    23,    24,    25,
      13,    45,   158,    29,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    41,    29,    -1,    -1,    -1,
      46,    -1,    -1,    49,    -1,    -1,    -1,    -1,    41,    -1,
      -1,    -1,    -1,    46,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      44,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    -1,    -1,    44,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    -1,    -1,    -1,    44,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    -1,    -1,
      -1,    44,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    -1,    -1,    -1,    44,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    52,    53,     4,     0,    54,    44,     5,     6,
      55,    59,    25,    24,    48,    46,    56,    24,    60,    61,
       6,    24,    49,    57,    58,    45,    47,    43,    24,    45,
      44,    14,    15,    16,    17,    18,    25,    62,    26,    24,
      46,    62,    62,    45,    60,    44,    48,    63,    62,    47,
      64,    26,     7,     8,    10,    11,    12,    13,    19,    20,
      21,    22,    23,    24,    25,    29,    41,    46,    49,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    62,    24,    46,    46,    24,    44,
      74,    46,    25,    46,    48,    74,    74,    74,    27,    42,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    44,    42,    63,    27,    45,    74,    74,
      44,    74,    46,    74,    82,    83,    24,    80,    81,    47,
      74,    24,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    24,    74,    62,    47,    47,
      47,    47,    47,    43,    45,    49,    43,    44,    46,    44,
      27,    63,    63,    44,    74,    74,    24,    82,    74,     9,
      45,    47,    44,    63,    74
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    55,    56,
      56,    56,    57,    58,    59,    60,    60,    61,    61,    62,
      62,    62,    62,    62,    62,    63,    64,    64,    65,    65,
      65,    65,    65,    65,    65,    66,    66,    67,    67,    68,
      69,    70,    71,    71,    72,    73,    73,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    75,    75,    75,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    77,    78,    79,    80,
      80,    81,    81,    82,    82,    83,    83
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     3,     0,     2,     2,     6,     0,
       2,     2,     4,     8,     8,     0,     1,     3,     5,     1,
       1,     1,     1,     1,     1,     3,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     5,     7,     1,     3,     4,
       5,     2,     5,     7,     5,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     1,     3,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     4,     4,     4,     0,
       1,     3,     5,     0,     1,     1,     3
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
  switch (yykind)
    {
    case YYSYMBOL_STRING_LIT: /* STRING_LIT  */
#line 128 "miku.y"
            { std::free(((*yyvaluep).sval)); }
#line 1053 "miku.tab.cpp"
        break;

    case YYSYMBOL_ID: /* ID  */
#line 128 "miku.y"
            { std::free(((*yyvaluep).sval)); }
#line 1059 "miku.tab.cpp"
        break;

    case YYSYMBOL_TYPE_NAME: /* TYPE_NAME  */
#line 128 "miku.y"
            { std::free(((*yyvaluep).sval)); }
#line 1065 "miku.tab.cpp"
        break;

    case YYSYMBOL_global_items: /* global_items  */
#line 142 "miku.y"
            {
    if (((*yyvaluep).gtmp)) {
        for (auto* st : ((*yyvaluep).gtmp)->structs) {
            if (!st) continue;
            for (auto* f : st->fields) { if (f) { delete f->ty; delete f; } }
            for (auto* m : st->methods) { delete m; }
            delete st;
        }
        for (auto* fn : ((*yyvaluep).gtmp)->funcs) delete fn;
        delete ((*yyvaluep).gtmp);
    }
}
#line 1082 "miku.tab.cpp"
        break;

    case YYSYMBOL_struct_def: /* struct_def  */
#line 135 "miku.y"
            {
    if (((*yyvaluep).stmp)) {
        for (auto* f : ((*yyvaluep).stmp)->fields) { if (f) { delete f->ty; delete f; } }
        for (auto* m : ((*yyvaluep).stmp)->methods) { delete m; }
        delete ((*yyvaluep).stmp);
    }
}
#line 1094 "miku.tab.cpp"
        break;

    case YYSYMBOL_struct_members: /* struct_members  */
#line 135 "miku.y"
            {
    if (((*yyvaluep).stmp)) {
        for (auto* f : ((*yyvaluep).stmp)->fields) { if (f) { delete f->ty; delete f; } }
        for (auto* m : ((*yyvaluep).stmp)->methods) { delete m; }
        delete ((*yyvaluep).stmp);
    }
}
#line 1106 "miku.tab.cpp"
        break;

    case YYSYMBOL_field_decl: /* field_decl  */
#line 132 "miku.y"
            {
    if (((*yyvaluep).fdecl)) { delete ((*yyvaluep).fdecl)->ty; delete ((*yyvaluep).fdecl); }
}
#line 1114 "miku.tab.cpp"
        break;

    case YYSYMBOL_type: /* type  */
#line 129 "miku.y"
            { delete ((*yyvaluep).typep); }
#line 1120 "miku.tab.cpp"
        break;

    case YYSYMBOL_lvalue: /* lvalue  */
#line 130 "miku.y"
            { delete ((*yyvaluep).lval); }
#line 1126 "miku.tab.cpp"
        break;

    case YYSYMBOL_field_inits_opt: /* field_inits_opt  */
#line 131 "miku.y"
            { delete ((*yyvaluep).inits); }
#line 1132 "miku.tab.cpp"
        break;

    case YYSYMBOL_field_inits: /* field_inits  */
#line 131 "miku.y"
            { delete ((*yyvaluep).inits); }
#line 1138 "miku.tab.cpp"
        break;

      default:
        break;
    }
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
  case 2: /* program: opt_feat global_items  */
#line 159 "miku.y"
      {
        g_program = new Program();

        for (auto* st : (yyvsp[0].gtmp)->structs) {
            auto sd = std::make_unique<StructDef>();
            sd->name = st->name;

            for (auto* f : st->fields) {
                sd->fields.push_back(FieldDef{f->name, *f->ty});
                delete f->ty;
                delete f;
            }
            st->fields.clear();

            for (auto* m : st->methods) {
                m->is_method = true;
                m->receiver = st->name;
                sd->methods[m->name].reset(m);
            }
            st->methods.clear();

            g_program->structs.emplace_back(std::move(sd));
            delete st;
        }
        (yyvsp[0].gtmp)->structs.clear();

        for (auto* fn : (yyvsp[0].gtmp)->funcs) {
            g_program->funcs.emplace_back(fn);
        }
        (yyvsp[0].gtmp)->funcs.clear();

        delete (yyvsp[0].gtmp);
        g_program->index();
      }
#line 1441 "miku.tab.cpp"
    break;

  case 5: /* global_items: %empty  */
#line 201 "miku.y"
                  { (yyval.gtmp) = new GlobalTmp(); }
#line 1447 "miku.tab.cpp"
    break;

  case 6: /* global_items: global_items struct_def  */
#line 203 "miku.y"
      { (yyvsp[-1].gtmp)->structs.push_back((yyvsp[0].stmp)); (yyval.gtmp) = (yyvsp[-1].gtmp); }
#line 1453 "miku.tab.cpp"
    break;

  case 7: /* global_items: global_items func_def  */
#line 205 "miku.y"
      { (yyvsp[-1].gtmp)->funcs.push_back((yyvsp[0].func)); (yyval.gtmp) = (yyvsp[-1].gtmp); }
#line 1459 "miku.tab.cpp"
    break;

  case 8: /* struct_def: KW_MIKUDATA TYPE_NAME LBRACE struct_members RBRACE SEMI  */
#line 211 "miku.y"
      {
        (yyvsp[-2].stmp)->name = std::string((yyvsp[-4].sval));
        std::free((yyvsp[-4].sval));
        (yyval.stmp) = (yyvsp[-2].stmp);
      }
#line 1469 "miku.tab.cpp"
    break;

  case 9: /* struct_members: %empty  */
#line 220 "miku.y"
      { (yyval.stmp) = new StructTmp(); }
#line 1475 "miku.tab.cpp"
    break;

  case 10: /* struct_members: struct_members field_decl  */
#line 222 "miku.y"
      {
        (yyvsp[-1].stmp)->fields.push_back((yyvsp[0].fdecl));
        (yyval.stmp) = (yyvsp[-1].stmp);
      }
#line 1484 "miku.tab.cpp"
    break;

  case 11: /* struct_members: struct_members method_def  */
#line 227 "miku.y"
      {
        (yyvsp[-1].stmp)->methods.push_back((yyvsp[0].func));
        (yyval.stmp) = (yyvsp[-1].stmp);
      }
#line 1493 "miku.tab.cpp"
    break;

  case 12: /* field_decl: ID COLON type SEMI  */
#line 235 "miku.y"
      {
        auto* f = new FieldDeclTmp();
        f->name = std::string((yyvsp[-3].sval));
        std::free((yyvsp[-3].sval));
        f->ty = (yyvsp[-1].typep);
        (yyval.fdecl) = f;
      }
#line 1505 "miku.tab.cpp"
    break;

  case 13: /* method_def: KW_TRACK ID LPAREN param_list_opt RPAREN ARROW type block  */
#line 246 "miku.y"
      {
        auto* fn = new Function();
        fn->name = std::string((yyvsp[-6].sval));
        std::free((yyvsp[-6].sval));

        fn->params = *(yyvsp[-4].params);
        delete (yyvsp[-4].params);

        fn->ret = *(yyvsp[-1].typep);
        delete (yyvsp[-1].typep);

        fn->body.reset((yyvsp[0].block));
        (yyval.func) = fn;
      }
#line 1524 "miku.tab.cpp"
    break;

  case 14: /* func_def: KW_TRACK ID LPAREN param_list_opt RPAREN ARROW type block  */
#line 265 "miku.y"
      {
        auto* fn = new Function();
        fn->name = std::string((yyvsp[-6].sval));
        std::free((yyvsp[-6].sval));

        fn->params = *(yyvsp[-4].params);
        delete (yyvsp[-4].params);

        fn->ret = *(yyvsp[-1].typep);
        delete (yyvsp[-1].typep);

        fn->body.reset((yyvsp[0].block));
        (yyval.func) = fn;
      }
#line 1543 "miku.tab.cpp"
    break;

  case 15: /* param_list_opt: %empty  */
#line 283 "miku.y"
                  { (yyval.params) = new std::vector<Param>(); }
#line 1549 "miku.tab.cpp"
    break;

  case 16: /* param_list_opt: param_list  */
#line 284 "miku.y"
                  { (yyval.params) = (yyvsp[0].params); }
#line 1555 "miku.tab.cpp"
    break;

  case 17: /* param_list: ID COLON type  */
#line 289 "miku.y"
      {
        auto* p = new std::vector<Param>();
        p->push_back(Param{std::string((yyvsp[-2].sval)), *(yyvsp[0].typep)});
        std::free((yyvsp[-2].sval));
        delete (yyvsp[0].typep);
        (yyval.params) = p;
      }
#line 1567 "miku.tab.cpp"
    break;

  case 18: /* param_list: param_list COMMA ID COLON type  */
#line 297 "miku.y"
      {
        (yyvsp[-4].params)->push_back(Param{std::string((yyvsp[-2].sval)), *(yyvsp[0].typep)});
        std::free((yyvsp[-2].sval));
        delete (yyvsp[0].typep);
        (yyval.params) = (yyvsp[-4].params);
      }
#line 1578 "miku.tab.cpp"
    break;

  case 19: /* type: KW_LEEK  */
#line 306 "miku.y"
                { (yyval.typep) = new Type(Type::Leek()); }
#line 1584 "miku.tab.cpp"
    break;

  case 20: /* type: KW_RIN  */
#line 307 "miku.y"
                { (yyval.typep) = new Type(Type::Rin()); }
#line 1590 "miku.tab.cpp"
    break;

  case 21: /* type: KW_SCROLL  */
#line 308 "miku.y"
                { (yyval.typep) = new Type(Type::Scroll()); }
#line 1596 "miku.tab.cpp"
    break;

  case 22: /* type: KW_CODE  */
#line 309 "miku.y"
                { (yyval.typep) = new Type(Type::Code()); }
#line 1602 "miku.tab.cpp"
    break;

  case 23: /* type: KW_GHOST  */
#line 310 "miku.y"
                { (yyval.typep) = new Type(Type::Ghost()); }
#line 1608 "miku.tab.cpp"
    break;

  case 24: /* type: TYPE_NAME  */
#line 311 "miku.y"
                { (yyval.typep) = new Type(Type::Struct(std::string((yyvsp[0].sval)))); std::free((yyvsp[0].sval)); }
#line 1614 "miku.tab.cpp"
    break;

  case 25: /* block: LBRACE stmt_list RBRACE  */
#line 317 "miku.y"
      {
        auto* b = new Block(yylineno);
        for (auto* s : *(yyvsp[-1].stmts)) b->stmts.emplace_back(s);
        delete (yyvsp[-1].stmts);
        (yyval.block) = b;
      }
#line 1625 "miku.tab.cpp"
    break;

  case 26: /* stmt_list: %empty  */
#line 326 "miku.y"
                  { (yyval.stmts) = new std::vector<Stmt*>(); }
#line 1631 "miku.tab.cpp"
    break;

  case 27: /* stmt_list: stmt_list stmt  */
#line 328 "miku.y"
      { (yyvsp[-1].stmts)->push_back((yyvsp[0].stmt)); (yyval.stmts) = (yyvsp[-1].stmts); }
#line 1637 "miku.tab.cpp"
    break;

  case 28: /* stmt: let_stmt  */
#line 332 "miku.y"
                  { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1643 "miku.tab.cpp"
    break;

  case 29: /* stmt: assign_stmt  */
#line 333 "miku.y"
                  { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1649 "miku.tab.cpp"
    break;

  case 30: /* stmt: print_stmt  */
#line 334 "miku.y"
                  { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1655 "miku.tab.cpp"
    break;

  case 31: /* stmt: if_stmt  */
#line 335 "miku.y"
                  { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1661 "miku.tab.cpp"
    break;

  case 32: /* stmt: while_stmt  */
#line 336 "miku.y"
                  { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1667 "miku.tab.cpp"
    break;

  case 33: /* stmt: return_stmt  */
#line 337 "miku.y"
                  { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1673 "miku.tab.cpp"
    break;

  case 34: /* stmt: expr_stmt  */
#line 338 "miku.y"
                  { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1679 "miku.tab.cpp"
    break;

  case 35: /* let_stmt: KW_LET ID ASSIGN expr SEMI  */
#line 343 "miku.y"
      {
        (yyval.stmt) = new StmtLet(yylineno, std::string((yyvsp[-3].sval)), std::nullopt, ExprPtr((yyvsp[-1].expr)));
        std::free((yyvsp[-3].sval));
      }
#line 1688 "miku.tab.cpp"
    break;

  case 36: /* let_stmt: KW_LET ID COLON type ASSIGN expr SEMI  */
#line 348 "miku.y"
      {
        (yyval.stmt) = new StmtLet(yylineno, std::string((yyvsp[-5].sval)), std::optional<Type>(* (yyvsp[-3].typep)), ExprPtr((yyvsp[-1].expr)));
        std::free((yyvsp[-5].sval));
        delete (yyvsp[-3].typep);
      }
#line 1698 "miku.tab.cpp"
    break;

  case 37: /* lvalue: ID  */
#line 357 "miku.y"
      {
        auto* lv = new LValTmp();
        lv->line = yylineno;
        lv->parts.push_back(std::string((yyvsp[0].sval)));
        std::free((yyvsp[0].sval));
        (yyval.lval) = lv;
      }
#line 1710 "miku.tab.cpp"
    break;

  case 38: /* lvalue: lvalue DOT ID  */
#line 365 "miku.y"
      {
        (yyvsp[-2].lval)->parts.push_back(std::string((yyvsp[0].sval)));
        std::free((yyvsp[0].sval));
        (yyval.lval) = (yyvsp[-2].lval);
      }
#line 1720 "miku.tab.cpp"
    break;

  case 39: /* assign_stmt: lvalue ASSIGN expr SEMI  */
#line 374 "miku.y"
      {
        auto lv = std::make_unique<LValue>();
        lv->line = (yyvsp[-3].lval)->line;
        lv->parts = std::move((yyvsp[-3].lval)->parts);
        delete (yyvsp[-3].lval);
        (yyval.stmt) = new StmtAssign(yylineno, std::move(lv), ExprPtr((yyvsp[-1].expr)));
      }
#line 1732 "miku.tab.cpp"
    break;

  case 40: /* print_stmt: KW_PRINT LPAREN expr RPAREN SEMI  */
#line 385 "miku.y"
      { (yyval.stmt) = new StmtPrint(yylineno, ExprPtr((yyvsp[-2].expr))); }
#line 1738 "miku.tab.cpp"
    break;

  case 41: /* expr_stmt: expr SEMI  */
#line 390 "miku.y"
      { (yyval.stmt) = new StmtExpr(yylineno, ExprPtr((yyvsp[-1].expr))); }
#line 1744 "miku.tab.cpp"
    break;

  case 42: /* if_stmt: KW_WISH LPAREN expr RPAREN block  */
#line 395 "miku.y"
      { (yyval.stmt) = new StmtIf(yylineno, ExprPtr((yyvsp[-2].expr)), std::unique_ptr<Block>((yyvsp[0].block)), nullptr); }
#line 1750 "miku.tab.cpp"
    break;

  case 43: /* if_stmt: KW_WISH LPAREN expr RPAREN block KW_REGRET block  */
#line 397 "miku.y"
      { (yyval.stmt) = new StmtIf(yylineno, ExprPtr((yyvsp[-4].expr)), std::unique_ptr<Block>((yyvsp[-2].block)), std::unique_ptr<Block>((yyvsp[0].block))); }
#line 1756 "miku.tab.cpp"
    break;

  case 44: /* while_stmt: KW_ROLLING LPAREN expr RPAREN block  */
#line 402 "miku.y"
      { (yyval.stmt) = new StmtWhile(yylineno, ExprPtr((yyvsp[-2].expr)), std::unique_ptr<Block>((yyvsp[0].block))); }
#line 1762 "miku.tab.cpp"
    break;

  case 45: /* return_stmt: KW_OFFER SEMI  */
#line 407 "miku.y"
      { (yyval.stmt) = new StmtReturn(yylineno, std::nullopt); }
#line 1768 "miku.tab.cpp"
    break;

  case 46: /* return_stmt: KW_OFFER expr SEMI  */
#line 409 "miku.y"
      {
        std::optional<ExprPtr> ex;
        ex.emplace(ExprPtr((yyvsp[-1].expr)));
        (yyval.stmt) = new StmtReturn(yylineno, std::move(ex));
      }
#line 1778 "miku.tab.cpp"
    break;

  case 47: /* expr: expr PLUS expr  */
#line 418 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::Add, ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1784 "miku.tab.cpp"
    break;

  case 48: /* expr: expr MINUS expr  */
#line 419 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::Sub, ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1790 "miku.tab.cpp"
    break;

  case 49: /* expr: expr MUL expr  */
#line 420 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::Mul, ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1796 "miku.tab.cpp"
    break;

  case 50: /* expr: expr DIV expr  */
#line 421 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::Div, ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1802 "miku.tab.cpp"
    break;

  case 51: /* expr: expr MOD expr  */
#line 422 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::Mod, ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1808 "miku.tab.cpp"
    break;

  case 52: /* expr: expr EQ expr  */
#line 424 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::Eq,  ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1814 "miku.tab.cpp"
    break;

  case 53: /* expr: expr NEQ expr  */
#line 425 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::Neq, ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1820 "miku.tab.cpp"
    break;

  case 54: /* expr: expr LT expr  */
#line 426 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::Lt,  ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1826 "miku.tab.cpp"
    break;

  case 55: /* expr: expr LE expr  */
#line 427 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::Le,  ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1832 "miku.tab.cpp"
    break;

  case 56: /* expr: expr GT expr  */
#line 428 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::Gt,  ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1838 "miku.tab.cpp"
    break;

  case 57: /* expr: expr GE expr  */
#line 429 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::Ge,  ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1844 "miku.tab.cpp"
    break;

  case 58: /* expr: expr AND expr  */
#line 431 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::And, ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1850 "miku.tab.cpp"
    break;

  case 59: /* expr: expr OR expr  */
#line 432 "miku.y"
                       { (yyval.expr) = new ExprBin(yylineno, BinOp::Or,  ExprPtr((yyvsp[-2].expr)), ExprPtr((yyvsp[0].expr))); }
#line 1856 "miku.tab.cpp"
    break;

  case 60: /* expr: NOT expr  */
#line 434 "miku.y"
                       { (yyval.expr) = new ExprUn(yylineno, UnOp::Not, ExprPtr((yyvsp[0].expr))); }
#line 1862 "miku.tab.cpp"
    break;

  case 61: /* expr: MINUS expr  */
#line 435 "miku.y"
                              { (yyval.expr) = new ExprUn(yylineno, UnOp::Neg, ExprPtr((yyvsp[0].expr))); }
#line 1868 "miku.tab.cpp"
    break;

  case 62: /* expr: postfix  */
#line 437 "miku.y"
                       { (yyval.expr) = (yyvsp[0].expr); }
#line 1874 "miku.tab.cpp"
    break;

  case 63: /* postfix: atom  */
#line 441 "miku.y"
           { (yyval.expr) = (yyvsp[0].expr); }
#line 1880 "miku.tab.cpp"
    break;

  case 64: /* postfix: postfix DOT ID  */
#line 443 "miku.y"
      { (yyval.expr) = new ExprField(yylineno, ExprPtr((yyvsp[-2].expr)), std::string((yyvsp[0].sval))); std::free((yyvsp[0].sval)); }
#line 1886 "miku.tab.cpp"
    break;

  case 65: /* postfix: postfix DOT ID LPAREN arg_list_opt RPAREN  */
#line 445 "miku.y"
      {
        std::vector<ExprPtr> args;
        for (auto* e : *(yyvsp[-1].exprs)) args.emplace_back(e);
        delete (yyvsp[-1].exprs);
        (yyval.expr) = new ExprMethodCall(yylineno, ExprPtr((yyvsp[-5].expr)), std::string((yyvsp[-3].sval)), std::move(args));
        std::free((yyvsp[-3].sval));
      }
#line 1898 "miku.tab.cpp"
    break;

  case 66: /* atom: INT_LIT  */
#line 455 "miku.y"
                        { (yyval.expr) = new ExprInt(yylineno, (yyvsp[0].ival)); }
#line 1904 "miku.tab.cpp"
    break;

  case 67: /* atom: FLOAT_LIT  */
#line 456 "miku.y"
                        { (yyval.expr) = new ExprFloat(yylineno, (yyvsp[0].fval)); }
#line 1910 "miku.tab.cpp"
    break;

  case 68: /* atom: STRING_LIT  */
#line 457 "miku.y"
                        { (yyval.expr) = new ExprString(yylineno, std::string((yyvsp[0].sval))); std::free((yyvsp[0].sval)); }
#line 1916 "miku.tab.cpp"
    break;

  case 69: /* atom: ANGEL  */
#line 458 "miku.y"
                        { (yyval.expr) = new ExprBool(yylineno, true); }
#line 1922 "miku.tab.cpp"
    break;

  case 70: /* atom: VIRUS  */
#line 459 "miku.y"
                        { (yyval.expr) = new ExprBool(yylineno, false); }
#line 1928 "miku.tab.cpp"
    break;

  case 71: /* atom: ID  */
#line 460 "miku.y"
                        { (yyval.expr) = new ExprVar(yylineno, std::string((yyvsp[0].sval))); std::free((yyvsp[0].sval)); }
#line 1934 "miku.tab.cpp"
    break;

  case 72: /* atom: call  */
#line 461 "miku.y"
                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1940 "miku.tab.cpp"
    break;

  case 73: /* atom: struct_lit  */
#line 462 "miku.y"
                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1946 "miku.tab.cpp"
    break;

  case 74: /* atom: summon_expr  */
#line 463 "miku.y"
                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1952 "miku.tab.cpp"
    break;

  case 75: /* atom: LPAREN expr RPAREN  */
#line 464 "miku.y"
                         { (yyval.expr) = (yyvsp[-1].expr); }
#line 1958 "miku.tab.cpp"
    break;

  case 76: /* call: ID LPAREN arg_list_opt RPAREN  */
#line 469 "miku.y"
      {
        std::vector<ExprPtr> args;
        for (auto* e : *(yyvsp[-1].exprs)) args.emplace_back(e);
        delete (yyvsp[-1].exprs);
        (yyval.expr) = new ExprCall(yylineno, std::string((yyvsp[-3].sval)), std::move(args));
        std::free((yyvsp[-3].sval));
      }
#line 1970 "miku.tab.cpp"
    break;

  case 77: /* summon_expr: KW_SUMMON TYPE_NAME LPAREN RPAREN  */
#line 480 "miku.y"
      { (yyval.expr) = new ExprSummon(yylineno, std::string((yyvsp[-2].sval))); std::free((yyvsp[-2].sval)); }
#line 1976 "miku.tab.cpp"
    break;

  case 78: /* struct_lit: TYPE_NAME LBRACE field_inits_opt RBRACE  */
#line 485 "miku.y"
      {
        std::vector<FieldInit> v;
        for (auto& it : *(yyvsp[-1].inits)) {
            FieldInit fi;
            fi.name = it.name;
            fi.expr.reset(it.expr);
            v.push_back(std::move(fi));
        }
        delete (yyvsp[-1].inits);
        (yyval.expr) = new ExprStructLit(yylineno, std::string((yyvsp[-3].sval)), std::move(v));
        std::free((yyvsp[-3].sval));
      }
#line 1993 "miku.tab.cpp"
    break;

  case 79: /* field_inits_opt: %empty  */
#line 500 "miku.y"
                  { (yyval.inits) = new std::vector<FieldInitTmp>(); }
#line 1999 "miku.tab.cpp"
    break;

  case 80: /* field_inits_opt: field_inits  */
#line 501 "miku.y"
                  { (yyval.inits) = (yyvsp[0].inits); }
#line 2005 "miku.tab.cpp"
    break;

  case 81: /* field_inits: ID COLON expr  */
#line 506 "miku.y"
      {
        auto* v = new std::vector<FieldInitTmp>();
        FieldInitTmp it;
        it.name = std::string((yyvsp[-2].sval));
        std::free((yyvsp[-2].sval));
        it.expr = (yyvsp[0].expr);
        v->push_back(std::move(it));
        (yyval.inits) = v;
      }
#line 2019 "miku.tab.cpp"
    break;

  case 82: /* field_inits: field_inits COMMA ID COLON expr  */
#line 516 "miku.y"
      {
        FieldInitTmp it;
        it.name = std::string((yyvsp[-2].sval));
        std::free((yyvsp[-2].sval));
        it.expr = (yyvsp[0].expr);
        (yyvsp[-4].inits)->push_back(std::move(it));
        (yyval.inits) = (yyvsp[-4].inits);
      }
#line 2032 "miku.tab.cpp"
    break;

  case 83: /* arg_list_opt: %empty  */
#line 527 "miku.y"
                  { (yyval.exprs) = new std::vector<Expr*>(); }
#line 2038 "miku.tab.cpp"
    break;

  case 84: /* arg_list_opt: arg_list  */
#line 528 "miku.y"
                  { (yyval.exprs) = (yyvsp[0].exprs); }
#line 2044 "miku.tab.cpp"
    break;

  case 85: /* arg_list: expr  */
#line 533 "miku.y"
      { auto* v = new std::vector<Expr*>(); v->push_back((yyvsp[0].expr)); (yyval.exprs) = v; }
#line 2050 "miku.tab.cpp"
    break;

  case 86: /* arg_list: arg_list COMMA expr  */
#line 535 "miku.y"
      { (yyvsp[-2].exprs)->push_back((yyvsp[0].expr)); (yyval.exprs) = (yyvsp[-2].exprs); }
#line 2056 "miku.tab.cpp"
    break;


#line 2060 "miku.tab.cpp"

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

#line 538 "miku.y"


Program* miku_get_program() { return g_program; }

void yyerror(const char* s) {
    std::fprintf(stderr, "[PARSE] %s at line %d\n", s, yylineno);
}
