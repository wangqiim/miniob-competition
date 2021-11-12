/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t join_length;
  size_t join_condition_length;
  size_t from_length;
  size_t value_length;
  size_t aggre_length;
  Value values[MAX_NUM];
  size_t insert_pair_num;
  Condition conditions[MAX_NUM];
  Condition join_conditions[MAX_NUM];
  Join joins[MAX_NUM];
  CompOp comp;
  Aggregate aggregates[MAX_NUM];
  AggreType aggreType;
  char id[MAX_NUM];
  int order; //0: asc, 1: desc
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  // 提前分配一个超过12字节的内存空间用来存放整个日期"xxxx-xx-xx"
  int len = sizeof(char) * (n2 - n1 + 2);
  if (len < 12) {
  	len = 12;
  }
  char *sp = malloc(len);
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.pair_num = 0;
  context->aggre_length = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 143 "yacc_sql.tab.c"

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

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_UNIQUE = 8,                     /* UNIQUE  */
  YYSYMBOL_INDEX = 9,                      /* INDEX  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_UPDATE = 16,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 20,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 21,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 22,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 23,                     /* INT_T  */
  YYSYMBOL_STRING_T = 24,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 25,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 26,                    /* DATE_T  */
  YYSYMBOL_HELP = 27,                      /* HELP  */
  YYSYMBOL_EXIT = 28,                      /* EXIT  */
  YYSYMBOL_DOT = 29,                       /* DOT  */
  YYSYMBOL_INTO = 30,                      /* INTO  */
  YYSYMBOL_VALUES = 31,                    /* VALUES  */
  YYSYMBOL_FROM = 32,                      /* FROM  */
  YYSYMBOL_WHERE = 33,                     /* WHERE  */
  YYSYMBOL_INNER = 34,                     /* INNER  */
  YYSYMBOL_JOIN = 35,                      /* JOIN  */
  YYSYMBOL_AND = 36,                       /* AND  */
  YYSYMBOL_SET = 37,                       /* SET  */
  YYSYMBOL_ON = 38,                        /* ON  */
  YYSYMBOL_LOAD = 39,                      /* LOAD  */
  YYSYMBOL_DATA = 40,                      /* DATA  */
  YYSYMBOL_INFILE = 41,                    /* INFILE  */
  YYSYMBOL_MAX_T = 42,                     /* MAX_T  */
  YYSYMBOL_MIN_T = 43,                     /* MIN_T  */
  YYSYMBOL_AVG_T = 44,                     /* AVG_T  */
  YYSYMBOL_SUM_T = 45,                     /* SUM_T  */
  YYSYMBOL_COUNT_T = 46,                   /* COUNT_T  */
  YYSYMBOL_EQ = 47,                        /* EQ  */
  YYSYMBOL_LT = 48,                        /* LT  */
  YYSYMBOL_GT = 49,                        /* GT  */
  YYSYMBOL_LE = 50,                        /* LE  */
  YYSYMBOL_GE = 51,                        /* GE  */
  YYSYMBOL_NE = 52,                        /* NE  */
  YYSYMBOL_NOT_T = 53,                     /* NOT_T  */
  YYSYMBOL_NULL_T = 54,                    /* NULL_T  */
  YYSYMBOL_NULLABLE_T = 55,                /* NULLABLE_T  */
  YYSYMBOL_IS_T = 56,                      /* IS_T  */
  YYSYMBOL_ORDER = 57,                     /* ORDER  */
  YYSYMBOL_BY = 58,                        /* BY  */
  YYSYMBOL_ASC = 59,                       /* ASC  */
  YYSYMBOL_NUMBER = 60,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 61,                     /* FLOAT  */
  YYSYMBOL_ID = 62,                        /* ID  */
  YYSYMBOL_PATH = 63,                      /* PATH  */
  YYSYMBOL_SSS = 64,                       /* SSS  */
  YYSYMBOL_STAR = 65,                      /* STAR  */
  YYSYMBOL_STRING_V = 66,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 67,                  /* $accept  */
  YYSYMBOL_commands = 68,                  /* commands  */
  YYSYMBOL_command = 69,                   /* command  */
  YYSYMBOL_exit = 70,                      /* exit  */
  YYSYMBOL_help = 71,                      /* help  */
  YYSYMBOL_sync = 72,                      /* sync  */
  YYSYMBOL_begin = 73,                     /* begin  */
  YYSYMBOL_commit = 74,                    /* commit  */
  YYSYMBOL_rollback = 75,                  /* rollback  */
  YYSYMBOL_drop_table = 76,                /* drop_table  */
  YYSYMBOL_show_tables = 77,               /* show_tables  */
  YYSYMBOL_desc_table = 78,                /* desc_table  */
  YYSYMBOL_create_index = 79,              /* create_index  */
  YYSYMBOL_drop_index = 80,                /* drop_index  */
  YYSYMBOL_create_table = 81,              /* create_table  */
  YYSYMBOL_attr_def_list = 82,             /* attr_def_list  */
  YYSYMBOL_attr_def = 83,                  /* attr_def  */
  YYSYMBOL_number = 84,                    /* number  */
  YYSYMBOL_type = 85,                      /* type  */
  YYSYMBOL_ID_get = 86,                    /* ID_get  */
  YYSYMBOL_insert = 87,                    /* insert  */
  YYSYMBOL_value_list = 88,                /* value_list  */
  YYSYMBOL_insert_pair_list = 89,          /* insert_pair_list  */
  YYSYMBOL_value = 90,                     /* value  */
  YYSYMBOL_delete = 91,                    /* delete  */
  YYSYMBOL_update = 92,                    /* update  */
  YYSYMBOL_select = 93,                    /* select  */
  YYSYMBOL_select_attr = 94,               /* select_attr  */
  YYSYMBOL_attr_list = 95,                 /* attr_list  */
  YYSYMBOL_aggre_func = 96,                /* aggre_func  */
  YYSYMBOL_aggre_list = 97,                /* aggre_list  */
  YYSYMBOL_aggre_type = 98,                /* aggre_type  */
  YYSYMBOL_rel_list = 99,                  /* rel_list  */
  YYSYMBOL_inner_join = 100,               /* inner_join  */
  YYSYMBOL_inner_join_list = 101,          /* inner_join_list  */
  YYSYMBOL_join_condition_list = 102,      /* join_condition_list  */
  YYSYMBOL_join_condition = 103,           /* join_condition  */
  YYSYMBOL_where = 104,                    /* where  */
  YYSYMBOL_condition_list = 105,           /* condition_list  */
  YYSYMBOL_condition = 106,                /* condition  */
  YYSYMBOL_comOp = 107,                    /* comOp  */
  YYSYMBOL_order_by = 108,                 /* order_by  */
  YYSYMBOL_order_item = 109,               /* order_item  */
  YYSYMBOL_order = 110,                    /* order  */
  YYSYMBOL_order_item_list = 111,          /* order_item_list  */
  YYSYMBOL_load_data = 112                 /* load_data  */
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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   253

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  251

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   321


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   163,   163,   165,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   189,   194,   199,   205,   211,   217,   223,   229,   235,
     242,   247,   255,   262,   271,   273,   277,   288,   300,   307,
     317,   320,   321,   322,   323,   326,   335,   353,   359,   364,
     366,   371,   374,   377,   381,   387,   397,   407,   429,   434,
     439,   444,   449,   452,   454,   461,   468,   476,   482,   487,
     492,   501,   503,   507,   508,   509,   510,   511,   514,   516,
     522,   531,   533,   538,   540,   545,   566,   587,   606,   628,
     630,   635,   637,   642,   663,   683,   703,   725,   746,   767,
     789,   790,   791,   792,   793,   794,   795,   796,   799,   801,
     805,   810,   818,   821,   824,   829,   831,   835
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
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "UNIQUE", "INDEX", "SELECT", "DESC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "INNER", "JOIN", "AND", "SET", "ON", "LOAD", "DATA", "INFILE",
  "MAX_T", "MIN_T", "AVG_T", "SUM_T", "COUNT_T", "EQ", "LT", "GT", "LE",
  "GE", "NE", "NOT_T", "NULL_T", "NULLABLE_T", "IS_T", "ORDER", "BY",
  "ASC", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V",
  "$accept", "commands", "command", "exit", "help", "sync", "begin",
  "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "insert", "value_list",
  "insert_pair_list", "value", "delete", "update", "select", "select_attr",
  "attr_list", "aggre_func", "aggre_list", "aggre_type", "rel_list",
  "inner_join", "inner_join_list", "join_condition_list", "join_condition",
  "where", "condition_list", "condition", "comOp", "order_by",
  "order_item", "order", "order_item_list", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321
};
#endif

#define YYPACT_NINF (-185)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -185,     5,  -185,    79,    25,    24,   -48,    16,    39,    13,
      31,   -14,    61,    68,    71,    72,    73,    42,  -185,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,    36,    95,    51,    56,
      59,  -185,  -185,  -185,  -185,  -185,    -7,  -185,   102,   103,
     118,   133,   134,  -185,    83,    84,   104,  -185,  -185,  -185,
    -185,  -185,   111,   132,    91,   123,   159,   160,   109,    34,
    -185,   110,   124,  -185,   -25,  -185,  -185,   142,   141,   113,
     112,   115,   140,   117,  -185,  -185,    43,   161,   161,   162,
     103,  -185,  -185,  -185,    12,  -185,   164,   165,   167,    19,
     182,   139,   157,  -185,   169,   101,   127,   173,    49,  -185,
    -185,  -185,   129,   158,  -185,  -185,   131,  -185,  -185,    90,
       9,   108,   163,  -185,    90,   188,   115,   177,  -185,  -185,
    -185,  -185,    -6,   179,   135,   161,   161,   162,   166,   158,
     141,   180,   181,   143,  -185,  -185,  -185,  -185,  -185,  -185,
     149,    30,    41,    19,  -185,   141,   144,   169,   200,   147,
     150,  -185,   146,   191,  -185,  -185,  -185,   148,  -185,   154,
    -185,    90,   194,   108,  -185,  -185,  -185,   184,  -185,   163,
     211,   212,  -185,  -185,  -185,   198,  -185,   199,   215,   183,
     168,   216,   181,   201,    46,   170,  -185,  -185,  -185,  -185,
     219,  -185,    55,   171,  -185,  -185,   206,   221,   196,  -185,
    -185,  -185,   202,   108,   192,    -5,   208,    90,  -185,   172,
     174,    69,    55,  -185,  -185,   175,  -185,  -185,   171,  -185,
     181,  -185,   108,   209,  -185,   192,    -4,   208,   217,    78,
     178,  -185,  -185,  -185,   201,   210,  -185,  -185,  -185,   185,
    -185
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,    73,    74,    75,    76,    77,    63,    58,     0,    71,
       0,     0,     0,    23,     0,     0,     0,    24,    25,    26,
      22,    21,     0,     0,     0,     0,     0,     0,     0,     0,
      59,     0,     0,    62,     0,    29,    28,     0,    89,     0,
       0,     0,     0,     0,    27,    32,    63,    63,    63,    78,
      71,    54,    51,    52,     0,    53,     0,     0,     0,     0,
       0,     0,     0,    45,    34,     0,     0,     0,     0,    64,
      60,    61,     0,    81,    72,    68,     0,    70,    67,     0,
       0,     0,    91,    55,     0,     0,     0,     0,    41,    42,
      43,    44,    37,     0,     0,    63,    63,    78,     0,    81,
      89,     0,    47,     0,   100,   101,   102,   103,   104,   105,
     106,     0,     0,     0,    90,    89,     0,    34,     0,     0,
       0,    39,     0,     0,    65,    66,    79,     0,    82,   108,
      69,     0,     0,     0,   107,    95,    93,    96,    94,    91,
       0,     0,    35,    33,    40,     0,    38,     0,     0,     0,
       0,     0,    47,    49,     0,     0,    92,    56,   117,    36,
       0,    30,     0,     0,    57,    48,     0,     0,     0,    97,
      98,    31,     0,     0,    83,   112,   115,     0,    46,     0,
       0,     0,     0,    80,   114,     0,   113,   110,     0,   109,
      47,    99,     0,     0,    88,    83,   112,   115,     0,     0,
       0,    84,   111,   116,    49,     0,    85,    86,    50,     0,
      87
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,  -185,    85,   119,  -185,  -185,  -185,
    -185,  -184,   -15,   -74,  -185,  -185,  -185,  -185,   -84,   176,
     151,  -185,    93,  -185,   105,     8,    27,  -127,    67,    97,
    -120,  -185,    23,    17,    15,  -185
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,   127,   104,   185,   132,   105,
      31,   172,   207,   121,    32,    33,    34,    48,    70,    49,
      73,    50,   113,   139,   140,   223,   214,   100,   154,   122,
     151,   191,   216,   227,   229,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      97,   152,   109,   110,   111,     2,   224,   224,   205,     3,
       4,   159,    68,   169,    51,     5,     6,     7,     8,     9,
      10,    11,    69,    52,   225,    12,    13,    14,   180,    91,
     115,    39,    15,    16,    40,    92,    93,    94,   143,    95,
      96,   116,    53,    54,    17,   142,   238,   160,    56,   161,
     155,   164,   165,   194,   226,   226,   144,   145,   146,   147,
     148,   149,    68,    55,    57,   150,    41,    42,    43,    44,
      45,    58,   108,    91,    59,    60,    61,   176,   178,    92,
      93,   120,    62,    95,    91,    36,    46,    37,    38,    47,
      92,    93,   175,   221,    95,    91,    87,   192,    63,    88,
      91,    92,    93,   177,    64,    95,    92,    93,   208,    91,
      95,   135,   239,    65,   136,    92,    93,   212,    66,    95,
     209,    67,    72,    91,   128,   129,   130,   131,   213,    92,
      93,   233,    91,    95,    71,    74,    75,    76,    92,    93,
     245,    79,    95,   230,    91,    77,    78,   234,   213,    81,
      92,    93,    80,    82,    95,   144,   145,   146,   147,   148,
     149,    83,    84,    85,   150,   246,    41,    42,    43,    44,
      45,    86,    89,    98,    99,   101,   102,   103,   106,   107,
      68,   112,   117,   118,   119,   123,   124,   125,   126,   133,
     134,   137,   138,   141,   156,   158,   162,   163,   170,   153,
     171,   167,   174,   183,   186,   173,   181,   184,   187,   188,
     189,   190,   193,   195,   197,   198,   199,   200,   201,   204,
     206,   202,   211,   217,   218,   219,   203,   228,   222,   248,
     166,   220,   210,   215,   231,   244,   232,   236,   240,   249,
     247,   114,   182,   241,   168,   157,   196,   250,    90,   235,
     179,   237,   243,   242
};

static const yytype_uint8 yycheck[] =
{
      74,   121,    86,    87,    88,     0,    11,    11,   192,     4,
       5,    17,    19,   140,    62,    10,    11,    12,    13,    14,
      15,    16,    29,     7,    29,    20,    21,    22,   155,    54,
      18,     6,    27,    28,     9,    60,    61,    62,    29,    64,
      65,    29,     3,    30,    39,   119,   230,    53,    62,    55,
     124,   135,   136,   173,    59,    59,    47,    48,    49,    50,
      51,    52,    19,    32,     3,    56,    42,    43,    44,    45,
      46,     3,    29,    54,     3,     3,     3,   151,   152,    60,
      61,    62,    40,    64,    54,     6,    62,     8,     9,    65,
      60,    61,    62,   213,    64,    54,    62,   171,    62,    65,
      54,    60,    61,    62,     9,    64,    60,    61,    62,    54,
      64,    62,   232,    62,    65,    60,    61,    62,    62,    64,
     194,    62,    19,    54,    23,    24,    25,    26,   202,    60,
      61,    62,    54,    64,    32,    17,     3,     3,    60,    61,
      62,    37,    64,   217,    54,    62,    62,   221,   222,    17,
      60,    61,    41,    62,    64,    47,    48,    49,    50,    51,
      52,    38,     3,     3,    56,   239,    42,    43,    44,    45,
      46,    62,    62,    31,    33,    62,    64,    62,    38,    62,
      19,    19,    18,    18,    17,     3,    47,    30,    19,    62,
      17,    62,    34,    62,     6,    18,    17,    62,    18,    36,
      19,    35,    53,     3,    54,    62,    62,    60,    62,    18,
      62,    57,    18,    29,     3,     3,    18,    18,     3,     3,
      19,    38,     3,    17,     3,    29,    58,    19,    36,   244,
     137,    29,    62,    62,    62,    18,    62,    62,    29,    29,
      62,    90,   157,   235,   139,   126,   179,    62,    72,   222,
     153,   228,   237,   236
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    68,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    27,    28,    39,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    87,    91,    92,    93,   112,     6,     8,     9,     6,
       9,    42,    43,    44,    45,    46,    62,    65,    94,    96,
      98,    62,     7,     3,    30,    32,    62,     3,     3,     3,
       3,     3,    40,    62,     9,    62,    62,    62,    19,    29,
      95,    32,    19,    97,    17,     3,     3,    62,    62,    37,
      41,    17,    62,    38,     3,     3,    62,    62,    65,    62,
      96,    54,    60,    61,    62,    64,    65,    90,    31,    33,
     104,    62,    64,    62,    83,    86,    38,    62,    29,    95,
      95,    95,    19,    99,    97,    18,    29,    18,    18,    17,
      62,    90,   106,     3,    47,    30,    19,    82,    23,    24,
      25,    26,    85,    62,    17,    62,    65,    62,    34,   100,
     101,    62,    90,    29,    47,    48,    49,    50,    51,    52,
      56,   107,   107,    36,   105,    90,     6,    83,    18,    17,
      53,    55,    17,    62,    95,    95,    99,    35,   101,   104,
      18,    19,    88,    62,    53,    62,    90,    62,    90,   106,
     104,    62,    82,     3,    60,    84,    54,    62,    18,    62,
      57,   108,    90,    18,   107,    29,   105,     3,     3,    18,
      18,     3,    38,    58,     3,    88,    19,    89,    62,    90,
      62,     3,    62,    90,   103,    62,   109,    17,     3,    29,
      29,   107,    36,   102,    11,    29,    59,   110,    19,   111,
      90,    62,    62,    62,    90,   103,    62,   109,    88,   107,
      29,   102,   110,   111,    18,    62,    90,    62,    89,    29,
      62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    67,    68,    68,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    79,    80,    81,    82,    82,    83,    83,    83,    83,
      84,    85,    85,    85,    85,    86,    87,    88,    88,    89,
      89,    90,    90,    90,    90,    91,    92,    93,    94,    94,
      94,    94,    94,    95,    95,    95,    95,    96,    96,    96,
      96,    97,    97,    98,    98,    98,    98,    98,    99,    99,
     100,   101,   101,   102,   102,   103,   103,   103,   103,   104,
     104,   105,   105,   106,   106,   106,   106,   106,   106,   106,
     107,   107,   107,   107,   107,   107,   107,   107,   108,   108,
     109,   109,   110,   110,   110,   111,   111,   112
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,    10,     4,     8,     0,     3,     5,     2,     4,     3,
       1,     1,     1,     1,     1,     1,    10,     0,     3,     0,
       6,     1,     1,     1,     1,     5,     8,     9,     1,     2,
       4,     4,     2,     0,     3,     5,     5,     4,     4,     6,
       4,     0,     3,     1,     1,     1,     1,     1,     0,     3,
       6,     0,     2,     0,     3,     5,     5,     7,     3,     0,
       3,     0,     3,     3,     3,     3,     3,     5,     5,     7,
       1,     1,     1,     1,     1,     1,     1,     2,     0,     4,
       2,     4,     0,     1,     1,     0,     3,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
        yyerror (scanner, YY_("syntax error: cannot back up")); \
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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
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
                 int yyrule, void *scanner)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
      yychar = yylex (&yylval, scanner);
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
  case 21: /* exit: EXIT SEMICOLON  */
#line 189 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1428 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 194 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1436 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 199 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1444 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 205 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1452 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 211 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1460 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 217 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1468 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 223 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1477 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 229 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1485 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 235 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1494 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 243 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, 0, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1503 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 248 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";(unique)
			create_index_init(&CONTEXT->ssql->sstr.create_index, 1, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1512 "yacc_sql.tab.c"
    break;

  case 32: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 256 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1521 "yacc_sql.tab.c"
    break;

  case 33: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 263 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1533 "yacc_sql.tab.c"
    break;

  case 35: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 273 "yacc_sql.y"
                                   {    }
#line 1539 "yacc_sql.tab.c"
    break;

  case 36: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 278 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number), 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1554 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def: ID_get type  */
#line 289 "yacc_sql.y"
                {
			// default: not null
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4, 0); // TODO(wq): 第4个参数不应该写死是4吧,会导致字符串被截断
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1570 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type NOT_T NULL_T  */
#line 301 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1581 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type NULLABLE_T  */
#line 308 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1592 "yacc_sql.tab.c"
    break;

  case 40: /* number: NUMBER  */
#line 317 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1598 "yacc_sql.tab.c"
    break;

  case 41: /* type: INT_T  */
#line 320 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1604 "yacc_sql.tab.c"
    break;

  case 42: /* type: STRING_T  */
#line 321 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1610 "yacc_sql.tab.c"
    break;

  case 43: /* type: FLOAT_T  */
#line 322 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1616 "yacc_sql.tab.c"
    break;

  case 44: /* type: DATE_T  */
#line 323 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1622 "yacc_sql.tab.c"
    break;

  case 45: /* ID_get: ID  */
#line 327 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1631 "yacc_sql.tab.c"
    break;

  case 46: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE insert_pair_list SEMICOLON  */
#line 336 "yacc_sql.y"
                {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string));

			//临时变量清零
			CONTEXT->insert_pair_num=0;
			CONTEXT->value_length=0;
    }
#line 1651 "yacc_sql.tab.c"
    break;

  case 47: /* value_list: %empty  */
#line 353 "yacc_sql.y"
                {
		// TODO(wq): 插入数据
		// 递增pair_num, 清零value_length
		inserts_append_values(&CONTEXT->ssql->sstr.insertion, CONTEXT->insert_pair_num++, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1662 "yacc_sql.tab.c"
    break;

  case 48: /* value_list: COMMA value value_list  */
#line 359 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	}
#line 1670 "yacc_sql.tab.c"
    break;

  case 50: /* insert_pair_list: COMMA LBRACE value value_list RBRACE insert_pair_list  */
#line 366 "yacc_sql.y"
                                                                {
		}
#line 1677 "yacc_sql.tab.c"
    break;

  case 51: /* value: NUMBER  */
#line 371 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1685 "yacc_sql.tab.c"
    break;

  case 52: /* value: FLOAT  */
#line 374 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1693 "yacc_sql.tab.c"
    break;

  case 53: /* value: SSS  */
#line 377 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1702 "yacc_sql.tab.c"
    break;

  case 54: /* value: NULL_T  */
#line 381 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		}
#line 1710 "yacc_sql.tab.c"
    break;

  case 55: /* delete: DELETE FROM ID where SEMICOLON  */
#line 388 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1722 "yacc_sql.tab.c"
    break;

  case 56: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 398 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1734 "yacc_sql.tab.c"
    break;

  case 57: /* select: SELECT select_attr FROM ID rel_list inner_join_list where order_by SEMICOLON  */
#line 408 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			selects_append_joins(&CONTEXT->ssql->sstr.selection, CONTEXT->joins, CONTEXT->join_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
			CONTEXT->join_length=0;
	}
#line 1757 "yacc_sql.tab.c"
    break;

  case 58: /* select_attr: STAR  */
#line 429 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1767 "yacc_sql.tab.c"
    break;

  case 59: /* select_attr: ID attr_list  */
#line 434 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1777 "yacc_sql.tab.c"
    break;

  case 60: /* select_attr: ID DOT ID attr_list  */
#line 439 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1787 "yacc_sql.tab.c"
    break;

  case 61: /* select_attr: ID DOT STAR attr_list  */
#line 444 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1797 "yacc_sql.tab.c"
    break;

  case 64: /* attr_list: COMMA ID attr_list  */
#line 454 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1809 "yacc_sql.tab.c"
    break;

  case 65: /* attr_list: COMMA ID DOT ID attr_list  */
#line 461 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1821 "yacc_sql.tab.c"
    break;

  case 66: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 468 "yacc_sql.y"
                                  {
    			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    	}
#line 1831 "yacc_sql.tab.c"
    break;

  case 67: /* aggre_func: aggre_type LBRACE value RBRACE  */
#line 476 "yacc_sql.y"
                                       {
		Aggregate aggre;
		Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
		relation_aggre_init(&aggre, CONTEXT->aggreType, 0, NULL, NULL, value);
		selects_append_aggregate(&CONTEXT->ssql->sstr.selection, &aggre);
	  }
#line 1842 "yacc_sql.tab.c"
    break;

  case 68: /* aggre_func: aggre_type LBRACE ID RBRACE  */
#line 482 "yacc_sql.y"
                                      {
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType, 1, NULL, (yyvsp[-1].string), NULL);
		selects_append_aggregate(&CONTEXT->ssql->sstr.selection, &aggre);
	  }
#line 1852 "yacc_sql.tab.c"
    break;

  case 69: /* aggre_func: aggre_type LBRACE ID DOT ID RBRACE  */
#line 487 "yacc_sql.y"
                                             {
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType, 1, (yyvsp[-3].string), (yyvsp[-1].string), NULL);
		selects_append_aggregate(&CONTEXT->ssql->sstr.selection, &aggre);
	  }
#line 1862 "yacc_sql.tab.c"
    break;

  case 70: /* aggre_func: aggre_type LBRACE STAR RBRACE  */
#line 492 "yacc_sql.y"
                                        {
		// TODO(wq):仅需要支持 select COUNT(*)，不需要支持select other_aggre(*) 以及select aggre_func(table_name.*);
		// 由于如果在语法解析里处理该问题的话，代码写的比较冗余丑陋，所以这里不检查sum(*)等这种不合法情况，丢给parse之后的stage去检验
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType, 1, NULL, "*", NULL);
		selects_append_aggregate(&CONTEXT->ssql->sstr.selection, &aggre);
	}
#line 1874 "yacc_sql.tab.c"
    break;

  case 73: /* aggre_type: MAX_T  */
#line 507 "yacc_sql.y"
                { CONTEXT->aggreType = MAXS; }
#line 1880 "yacc_sql.tab.c"
    break;

  case 74: /* aggre_type: MIN_T  */
#line 508 "yacc_sql.y"
                { CONTEXT->aggreType = MINS; }
#line 1886 "yacc_sql.tab.c"
    break;

  case 75: /* aggre_type: AVG_T  */
#line 509 "yacc_sql.y"
                { CONTEXT->aggreType = AVGS; }
#line 1892 "yacc_sql.tab.c"
    break;

  case 76: /* aggre_type: SUM_T  */
#line 510 "yacc_sql.y"
                { CONTEXT->aggreType = SUMS; }
#line 1898 "yacc_sql.tab.c"
    break;

  case 77: /* aggre_type: COUNT_T  */
#line 511 "yacc_sql.y"
                  { CONTEXT->aggreType = COUNTS; }
#line 1904 "yacc_sql.tab.c"
    break;

  case 79: /* rel_list: COMMA ID rel_list  */
#line 516 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 1912 "yacc_sql.tab.c"
    break;

  case 80: /* inner_join: INNER JOIN ID ON join_condition join_condition_list  */
#line 522 "yacc_sql.y"
                                                        {
    	Join join;
    	join_init(&join, INNER_JOIN, (yyvsp[-3].string), CONTEXT->join_conditions, CONTEXT->join_condition_length);
    	CONTEXT->joins[CONTEXT->join_length++] = join;
    	// 清空变量
    	CONTEXT->join_condition_length = 0;
    }
#line 1924 "yacc_sql.tab.c"
    break;

  case 82: /* inner_join_list: inner_join inner_join_list  */
#line 533 "yacc_sql.y"
                                  {

    }
#line 1932 "yacc_sql.tab.c"
    break;

  case 84: /* join_condition_list: AND join_condition join_condition_list  */
#line 540 "yacc_sql.y"
                                              {

     }
#line 1940 "yacc_sql.tab.c"
    break;

  case 85: /* join_condition: ID DOT ID comOp value  */
#line 546 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->join_conditions[CONTEXT->join_condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;

    }
#line 1965 "yacc_sql.tab.c"
    break;

  case 86: /* join_condition: value comOp ID DOT ID  */
#line 567 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->join_conditions[CONTEXT->join_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;

    }
#line 1990 "yacc_sql.tab.c"
    break;

  case 87: /* join_condition: ID DOT ID comOp ID DOT ID  */
#line 588 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->join_conditions[CONTEXT->join_condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2013 "yacc_sql.tab.c"
    break;

  case 88: /* join_condition: value comOp value  */
#line 607 "yacc_sql.y"
                {
    			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
    			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

    			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->join_conditions[CONTEXT->join_condition_length++] = condition;

    			// $$ = ( Condition *)malloc(sizeof( Condition));
    			// $$->left_is_attr = 0;
    			// $$->left_attr.relation_name=NULL;
    			// $$->left_attr.attribute_name=NULL;
    			// $$->left_value = *$1;
    			// $$->comp = CONTEXT->comp;
    			// $$->right_is_attr = 0;
    			// $$->right_attr.relation_name = NULL;
    			// $$->right_attr.attribute_name = NULL;
    			// $$->right_value = *$3;

    		}
#line 2038 "yacc_sql.tab.c"
    break;

  case 90: /* where: WHERE condition condition_list  */
#line 630 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2046 "yacc_sql.tab.c"
    break;

  case 92: /* condition_list: AND condition condition_list  */
#line 637 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2054 "yacc_sql.tab.c"
    break;

  case 93: /* condition: ID comOp value  */
#line 643 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2079 "yacc_sql.tab.c"
    break;

  case 94: /* condition: value comOp value  */
#line 664 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2103 "yacc_sql.tab.c"
    break;

  case 95: /* condition: ID comOp ID  */
#line 684 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2127 "yacc_sql.tab.c"
    break;

  case 96: /* condition: value comOp ID  */
#line 704 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 2153 "yacc_sql.tab.c"
    break;

  case 97: /* condition: ID DOT ID comOp value  */
#line 726 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2178 "yacc_sql.tab.c"
    break;

  case 98: /* condition: value comOp ID DOT ID  */
#line 747 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2203 "yacc_sql.tab.c"
    break;

  case 99: /* condition: ID DOT ID comOp ID DOT ID  */
#line 768 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2226 "yacc_sql.tab.c"
    break;

  case 100: /* comOp: EQ  */
#line 789 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2232 "yacc_sql.tab.c"
    break;

  case 101: /* comOp: LT  */
#line 790 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2238 "yacc_sql.tab.c"
    break;

  case 102: /* comOp: GT  */
#line 791 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2244 "yacc_sql.tab.c"
    break;

  case 103: /* comOp: LE  */
#line 792 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2250 "yacc_sql.tab.c"
    break;

  case 104: /* comOp: GE  */
#line 793 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2256 "yacc_sql.tab.c"
    break;

  case 105: /* comOp: NE  */
#line 794 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2262 "yacc_sql.tab.c"
    break;

  case 106: /* comOp: IS_T  */
#line 795 "yacc_sql.y"
               { CONTEXT->comp = IS; }
#line 2268 "yacc_sql.tab.c"
    break;

  case 107: /* comOp: IS_T NOT_T  */
#line 796 "yacc_sql.y"
                     { CONTEXT->comp = IS_NOT; }
#line 2274 "yacc_sql.tab.c"
    break;

  case 110: /* order_item: ID order  */
#line 805 "yacc_sql.y"
                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_order(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->order);
	}
#line 2284 "yacc_sql.tab.c"
    break;

  case 111: /* order_item: ID DOT ID order  */
#line 810 "yacc_sql.y"
                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_order(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->order);
	}
#line 2294 "yacc_sql.tab.c"
    break;

  case 112: /* order: %empty  */
#line 818 "yacc_sql.y"
                    {
		CONTEXT->order = 0;
	}
#line 2302 "yacc_sql.tab.c"
    break;

  case 113: /* order: ASC  */
#line 821 "yacc_sql.y"
              {
		CONTEXT->order = 0;
	}
#line 2310 "yacc_sql.tab.c"
    break;

  case 114: /* order: DESC  */
#line 824 "yacc_sql.y"
               {
		CONTEXT->order = 1;
	}
#line 2318 "yacc_sql.tab.c"
    break;

  case 117: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 836 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2327 "yacc_sql.tab.c"
    break;


#line 2331 "yacc_sql.tab.c"

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
      yyerror (scanner, YY_("syntax error"));
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
                      yytoken, &yylval, scanner);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 841 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
