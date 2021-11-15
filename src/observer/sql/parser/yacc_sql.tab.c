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

  Selects selects[MAX_NUM];
  size_t select_length;

  RelAttr attrs[MAX_NUM][MAX_NUM];
  size_t attr_length[MAX_NUM];

  Aggregate aggregates[MAX_NUM][MAX_NUM];
//  size_t aggre_length[MAX_NUM];
  AggreType aggreType[MAX_NUM];

  char *  relations[MAX_NUM][MAX_NUM];
  size_t from_length[MAX_NUM];

  Join joins[MAX_NUM][MAX_NUM];
  size_t join_length[MAX_NUM];

  Condition join_conditions[MAX_NUM][MAX_NUM];
  size_t join_condition_length[MAX_NUM];

  Condition conditions[MAX_NUM][MAX_NUM];
  size_t condition_length[MAX_NUM];

  size_t value_length;
  Value values[MAX_NUM];
  size_t insert_pair_num;
  CompOp comp;
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
  context->condition_length[0] = 0;
  context->from_length[0] = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.pair_num = 0;
//  context->aggre_length = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 155 "yacc_sql.tab.c"

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
  YYSYMBOL_TEXT_T = 27,                    /* TEXT_T  */
  YYSYMBOL_HELP = 28,                      /* HELP  */
  YYSYMBOL_EXIT = 29,                      /* EXIT  */
  YYSYMBOL_DOT = 30,                       /* DOT  */
  YYSYMBOL_INTO = 31,                      /* INTO  */
  YYSYMBOL_VALUES = 32,                    /* VALUES  */
  YYSYMBOL_FROM = 33,                      /* FROM  */
  YYSYMBOL_WHERE = 34,                     /* WHERE  */
  YYSYMBOL_INNER = 35,                     /* INNER  */
  YYSYMBOL_JOIN = 36,                      /* JOIN  */
  YYSYMBOL_AND = 37,                       /* AND  */
  YYSYMBOL_SET = 38,                       /* SET  */
  YYSYMBOL_ON = 39,                        /* ON  */
  YYSYMBOL_LOAD = 40,                      /* LOAD  */
  YYSYMBOL_DATA = 41,                      /* DATA  */
  YYSYMBOL_INFILE = 42,                    /* INFILE  */
  YYSYMBOL_MAX_T = 43,                     /* MAX_T  */
  YYSYMBOL_MIN_T = 44,                     /* MIN_T  */
  YYSYMBOL_AVG_T = 45,                     /* AVG_T  */
  YYSYMBOL_SUM_T = 46,                     /* SUM_T  */
  YYSYMBOL_COUNT_T = 47,                   /* COUNT_T  */
  YYSYMBOL_EQ = 48,                        /* EQ  */
  YYSYMBOL_LT = 49,                        /* LT  */
  YYSYMBOL_GT = 50,                        /* GT  */
  YYSYMBOL_LE = 51,                        /* LE  */
  YYSYMBOL_GE = 52,                        /* GE  */
  YYSYMBOL_NE = 53,                        /* NE  */
  YYSYMBOL_NOT_T = 54,                     /* NOT_T  */
  YYSYMBOL_NULL_T = 55,                    /* NULL_T  */
  YYSYMBOL_NULLABLE_T = 56,                /* NULLABLE_T  */
  YYSYMBOL_IS_T = 57,                      /* IS_T  */
  YYSYMBOL_ORDER = 58,                     /* ORDER  */
  YYSYMBOL_BY = 59,                        /* BY  */
  YYSYMBOL_ASC = 60,                       /* ASC  */
  YYSYMBOL_IN = 61,                        /* IN  */
  YYSYMBOL_GROUP = 62,                     /* GROUP  */
  YYSYMBOL_NUMBER = 63,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 64,                     /* FLOAT  */
  YYSYMBOL_ID = 65,                        /* ID  */
  YYSYMBOL_PATH = 66,                      /* PATH  */
  YYSYMBOL_SSS = 67,                       /* SSS  */
  YYSYMBOL_STAR = 68,                      /* STAR  */
  YYSYMBOL_STRING_V = 69,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 70,                  /* $accept  */
  YYSYMBOL_commands = 71,                  /* commands  */
  YYSYMBOL_command = 72,                   /* command  */
  YYSYMBOL_exit = 73,                      /* exit  */
  YYSYMBOL_help = 74,                      /* help  */
  YYSYMBOL_sync = 75,                      /* sync  */
  YYSYMBOL_begin = 76,                     /* begin  */
  YYSYMBOL_commit = 77,                    /* commit  */
  YYSYMBOL_rollback = 78,                  /* rollback  */
  YYSYMBOL_drop_table = 79,                /* drop_table  */
  YYSYMBOL_show_tables = 80,               /* show_tables  */
  YYSYMBOL_desc_table = 81,                /* desc_table  */
  YYSYMBOL_create_index = 82,              /* create_index  */
  YYSYMBOL_id_list = 83,                   /* id_list  */
  YYSYMBOL_drop_index = 84,                /* drop_index  */
  YYSYMBOL_create_table = 85,              /* create_table  */
  YYSYMBOL_attr_def_list = 86,             /* attr_def_list  */
  YYSYMBOL_attr_def = 87,                  /* attr_def  */
  YYSYMBOL_number = 88,                    /* number  */
  YYSYMBOL_type = 89,                      /* type  */
  YYSYMBOL_ID_get = 90,                    /* ID_get  */
  YYSYMBOL_insert = 91,                    /* insert  */
  YYSYMBOL_value_list = 92,                /* value_list  */
  YYSYMBOL_insert_pair_list = 93,          /* insert_pair_list  */
  YYSYMBOL_value = 94,                     /* value  */
  YYSYMBOL_delete = 95,                    /* delete  */
  YYSYMBOL_update = 96,                    /* update  */
  YYSYMBOL_select_begin = 97,              /* select_begin  */
  YYSYMBOL_select_end = 98,                /* select_end  */
  YYSYMBOL_select = 99,                    /* select  */
  YYSYMBOL_select_attr = 100,              /* select_attr  */
  YYSYMBOL_attr_list = 101,                /* attr_list  */
  YYSYMBOL_aggre_func = 102,               /* aggre_func  */
  YYSYMBOL_aggre_type = 103,               /* aggre_type  */
  YYSYMBOL_rel_list = 104,                 /* rel_list  */
  YYSYMBOL_inner_join = 105,               /* inner_join  */
  YYSYMBOL_inner_join_list = 106,          /* inner_join_list  */
  YYSYMBOL_join_condition_list = 107,      /* join_condition_list  */
  YYSYMBOL_join_condition = 108,           /* join_condition  */
  YYSYMBOL_where = 109,                    /* where  */
  YYSYMBOL_condition_list = 110,           /* condition_list  */
  YYSYMBOL_condition = 111,                /* condition  */
  YYSYMBOL_comOp = 112,                    /* comOp  */
  YYSYMBOL_order_by = 113,                 /* order_by  */
  YYSYMBOL_order_item = 114,               /* order_item  */
  YYSYMBOL_order = 115,                    /* order  */
  YYSYMBOL_order_item_list = 116,          /* order_item_list  */
  YYSYMBOL_group_by = 117,                 /* group_by  */
  YYSYMBOL_group_item = 118,               /* group_item  */
  YYSYMBOL_group_item_list = 119,          /* group_item_list  */
  YYSYMBOL_load_data = 120                 /* load_data  */
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
typedef yytype_int16 yy_state_t;

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
#define YYLAST   281

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  131
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  274

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


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
      65,    66,    67,    68,    69
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   178,   178,   180,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   204,   209,   214,   220,   226,   232,   238,   244,   250,
     257,   263,   271,   273,   279,   286,   295,   297,   301,   312,
     324,   331,   341,   344,   345,   346,   347,   348,   351,   360,
     378,   384,   389,   391,   396,   399,   402,   406,   412,   422,
     433,   440,   442,   447,   469,   474,   479,   484,   489,   492,
     494,   501,   508,   513,   517,   523,   528,   533,   543,   544,
     545,   546,   547,   550,   552,   558,   567,   569,   574,   576,
     581,   602,   623,   642,   664,   666,   671,   673,   678,   699,
     719,   739,   761,   782,   803,   822,   832,   833,   834,   835,
     836,   837,   838,   839,   840,   841,   844,   846,   850,   855,
     863,   866,   869,   874,   876,   879,   881,   885,   890,   897,
     899,   904
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
  "FLOAT_T", "DATE_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "INNER", "JOIN", "AND", "SET", "ON", "LOAD", "DATA",
  "INFILE", "MAX_T", "MIN_T", "AVG_T", "SUM_T", "COUNT_T", "EQ", "LT",
  "GT", "LE", "GE", "NE", "NOT_T", "NULL_T", "NULLABLE_T", "IS_T", "ORDER",
  "BY", "ASC", "IN", "GROUP", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
  "STAR", "STRING_V", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "desc_table", "create_index", "id_list", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "insert",
  "value_list", "insert_pair_list", "value", "delete", "update",
  "select_begin", "select_end", "select", "select_attr", "attr_list",
  "aggre_func", "aggre_type", "rel_list", "inner_join", "inner_join_list",
  "join_condition_list", "join_condition", "where", "condition_list",
  "condition", "comOp", "order_by", "order_item", "order",
  "order_item_list", "group_by", "group_item", "group_item_list",
  "load_data", YY_NULLPTR
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324
};
#endif

#define YYPACT_NINF (-192)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -192,    61,  -192,   104,    18,  -192,   -50,    22,    44,    27,
      24,    -2,    66,    67,    75,    77,    83,    23,  -192,  -192,
    -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,
    -192,  -192,  -192,  -192,   -27,  -192,  -192,    14,    79,    20,
      33,    34,   106,   111,  -192,    35,    52,    88,  -192,  -192,
    -192,  -192,  -192,    85,  -192,  -192,  -192,  -192,  -192,    12,
    -192,    96,   114,   113,   117,    86,   109,   133,   147,  -192,
    -192,   121,   120,    90,    89,   -35,   -14,  -192,   103,  -192,
      76,   105,   137,   112,  -192,  -192,   161,    82,   178,   142,
     154,    26,   114,   114,   114,   173,  -192,  -192,  -192,    -4,
    -192,   175,   176,  -192,   177,    68,   130,   180,   -42,    54,
      71,   162,  -192,   -42,   192,    -6,  -192,  -192,  -192,  -192,
     135,   166,  -192,   138,  -192,  -192,   105,   184,  -192,  -192,
    -192,  -192,  -192,   -10,   187,   140,   188,   141,  -192,  -192,
    -192,  -192,  -192,  -192,   148,   156,  -192,    97,   102,    82,
    -192,   120,   143,   114,   114,   173,   179,   166,   120,   193,
     177,   209,   150,   159,  -192,   151,   198,   -42,   200,    71,
    -192,  -192,  -192,  -192,   189,  -192,   162,   217,   218,  -192,
    -192,  -192,   157,  -192,   163,  -192,  -192,  -192,  -192,   205,
    -192,   206,   164,   208,   188,   211,   -15,   167,  -192,  -192,
    -192,   194,   168,   170,  -192,   228,   198,   231,  -192,   219,
     232,   227,   210,  -192,  -192,   108,   174,   182,   235,  -192,
    -192,  -192,   -42,  -192,   224,   181,   213,    71,   207,   215,
     229,   185,  -192,  -192,   188,  -192,  -192,   186,   119,   108,
    -192,   190,   174,  -192,    -7,   230,   234,    71,   223,  -192,
     207,  -192,   229,  -192,   191,  -192,  -192,   185,  -192,   211,
     124,   195,  -192,  -192,    -5,   230,  -192,   233,  -192,  -192,
    -192,  -192,   196,  -192
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     0,     4,    18,     0,     0,     0,
       0,     0,     0,     0,    23,     0,     0,     0,    24,    25,
      26,    22,    21,     0,    78,    79,    80,    81,    82,    69,
      64,     0,    69,     0,     0,     0,     0,     0,     0,    29,
      28,     0,    94,     0,     0,     0,     0,    65,     0,    68,
       0,     0,     0,     0,    27,    34,     0,     0,     0,     0,
       0,    69,    69,    69,    69,    83,    57,    54,    55,     0,
      56,     0,     0,    48,    36,     0,     0,     0,     0,     0,
       0,    96,    58,     0,     0,     0,    70,    73,    66,    67,
       0,    86,    75,     0,    77,    74,     0,     0,    43,    44,
      45,    46,    47,    39,     0,     0,    50,     0,   106,   107,
     108,   109,   110,   111,     0,   112,   114,     0,     0,     0,
      95,    94,     0,    69,    69,    83,     0,    86,    94,     0,
      36,     0,     0,     0,    41,     0,    32,     0,     0,     0,
     115,   113,   100,    98,   101,    99,    96,     0,     0,    71,
      72,    84,     0,    87,   125,    76,    37,    35,    42,     0,
      40,     0,     0,     0,    50,    52,     0,     0,    97,    59,
     131,     0,     0,   116,    38,     0,    32,     0,    51,     0,
       0,     0,     0,   102,   103,     0,     0,     0,    61,    31,
      33,    30,     0,    49,     0,     0,     0,     0,    88,   127,
     129,     0,    62,    63,    50,   105,   104,     0,     0,     0,
      85,     0,     0,   126,   120,   123,     0,     0,     0,    93,
      88,   128,   129,   122,     0,   121,   118,     0,   117,    52,
       0,     0,    89,   130,   120,   123,    53,     0,    90,    91,
     119,   124,     0,    92
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,  -192,
    -192,  -192,  -192,    41,  -192,  -192,    94,   131,  -192,  -192,
    -192,  -192,  -191,    -1,   -80,  -192,  -192,  -192,  -192,    48,
    -192,   -57,   197,  -192,   107,  -192,   110,    15,    25,  -119,
      92,   122,  -109,  -192,     9,     5,     8,  -192,    28,    29,
    -192
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   193,    29,    30,   127,   104,   189,   133,
     105,    31,   168,   210,   110,    32,    33,    34,   233,    35,
      61,    77,    62,    63,   121,   157,   158,   240,   228,    88,
     150,   111,   147,   218,   245,   256,   258,   203,   230,   243,
      36
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     102,   148,   211,   208,   253,    79,   253,   162,    54,    55,
      56,    57,    58,    96,   122,    42,    54,    55,    56,    57,
      58,    97,    98,   254,    40,   100,   123,    41,   136,    43,
      91,    75,   177,   151,   116,   117,   118,   119,    59,   184,
      96,    60,    76,   246,   163,    75,   164,    44,    97,    98,
     212,    93,   100,   255,    94,   255,   115,    46,    45,   153,
     196,     2,   154,    47,    53,     3,     4,   173,   175,    48,
      49,     5,     6,     7,     8,     9,    10,    11,    50,    64,
      51,    12,    13,    14,   137,    66,    52,   194,    65,    15,
      16,   128,   129,   130,   131,   132,   179,   180,    67,    68,
      71,    17,   138,   139,   140,   141,   142,   143,   144,    69,
      37,   145,    38,    39,    70,   146,   213,    72,   238,   138,
     139,   140,   141,   142,   143,   144,    73,    74,   145,    78,
      80,    96,   146,    75,    81,   227,    84,    96,   260,    97,
      98,    99,   234,   100,   101,    97,    98,   109,    83,   100,
      85,    82,    96,    86,    87,    89,    90,    96,   249,   227,
      97,    98,   172,    96,   100,    97,    98,   174,    95,   100,
     103,    97,    98,   226,    96,   100,   106,   107,   108,    96,
     268,   112,    97,    98,   248,   114,   100,    97,    98,   267,
     113,   100,   120,   124,   125,   134,   126,   135,   152,   149,
     155,   156,   161,   159,   165,   166,   169,   167,   178,   170,
     171,   185,   187,   188,   190,   182,   191,   192,   195,   197,
     199,   200,   201,   204,   205,   202,   207,   216,   217,   206,
     209,   219,   214,   215,   221,   223,   222,     5,   232,   229,
     225,   231,   235,   237,   239,   241,   236,   220,   242,   257,
     244,   247,   259,   261,   186,   251,   264,   160,   266,   224,
     269,   273,   181,   272,   250,   262,   265,   183,   198,   270,
     252,   176,    92,   271,     0,     0,     0,     0,     0,     0,
       0,   263
};

static const yytype_int16 yycheck[] =
{
      80,   110,    17,   194,    11,    62,    11,    17,    43,    44,
      45,    46,    47,    55,    18,    65,    43,    44,    45,    46,
      47,    63,    64,    30,     6,    67,    30,     9,   108,     7,
      65,    19,   151,   113,    91,    92,    93,    94,    65,   158,
      55,    68,    30,   234,    54,    19,    56,     3,    63,    64,
      65,    65,    67,    60,    68,    60,    30,    33,    31,    65,
     169,     0,    68,    65,    41,     4,     5,   147,   148,     3,
       3,    10,    11,    12,    13,    14,    15,    16,     3,    65,
       3,    20,    21,    22,    30,    65,     3,   167,     9,    28,
      29,    23,    24,    25,    26,    27,   153,   154,    65,    65,
      65,    40,    48,    49,    50,    51,    52,    53,    54,     3,
       6,    57,     8,     9,     3,    61,   196,    65,   227,    48,
      49,    50,    51,    52,    53,    54,    38,    42,    57,    33,
      17,    55,    61,    19,    17,   215,     3,    55,   247,    63,
      64,    65,   222,    67,    68,    63,    64,    65,    39,    67,
       3,    65,    55,    32,    34,    65,    67,    55,   238,   239,
      63,    64,    65,    55,    67,    63,    64,    65,    65,    67,
      65,    63,    64,    65,    55,    67,    39,    65,    17,    55,
     260,     3,    63,    64,    65,    31,    67,    63,    64,    65,
      48,    67,    19,    18,    18,    65,    19,    17,     6,    37,
      65,    35,    18,    65,    17,    65,    65,    19,    65,    61,
      54,    18,     3,    63,    55,    36,    65,    19,    18,    30,
       3,     3,    65,    18,    18,    62,    18,    59,    58,    65,
      19,     3,    65,    39,     3,     3,    17,    10,     3,    65,
      30,    59,    18,    30,    37,    30,    65,   206,    19,    19,
      65,    65,    18,    30,   160,    65,    65,   126,   259,   211,
      65,    65,   155,    30,   239,   250,   257,   157,   176,   264,
     242,   149,    75,   265,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   252
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    71,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    28,    29,    40,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    84,
      85,    91,    95,    96,    97,    99,   120,     6,     8,     9,
       6,     9,    65,     7,     3,    31,    33,    65,     3,     3,
       3,     3,     3,    41,    43,    44,    45,    46,    47,    65,
      68,   100,   102,   103,    65,     9,    65,    65,    65,     3,
       3,    65,    65,    38,    42,    19,    30,   101,    33,   101,
      17,    17,    65,    39,     3,     3,    32,    34,   109,    65,
      67,    65,   102,    65,    68,    65,    55,    63,    64,    65,
      67,    68,    94,    65,    87,    90,    39,    65,    17,    65,
      94,   111,     3,    48,    31,    30,   101,   101,   101,   101,
      19,   104,    18,    30,    18,    18,    19,    86,    23,    24,
      25,    26,    27,    89,    65,    17,    94,    30,    48,    49,
      50,    51,    52,    53,    54,    57,    61,   112,   112,    37,
     110,    94,     6,    65,    68,    65,    35,   105,   106,    65,
      87,    18,    17,    54,    56,    17,    65,    19,    92,    65,
      61,    54,    65,    94,    65,    94,   111,   109,    65,   101,
     101,   104,    36,   106,   109,    18,    86,     3,    63,    88,
      55,    65,    19,    83,    94,    18,   112,    30,   110,     3,
       3,    65,    62,   117,    18,    18,    65,    18,    92,    19,
      93,    17,    65,    94,    65,    39,    59,    58,   113,     3,
      83,     3,    17,     3,    99,    30,    65,    94,   108,    65,
     118,    59,     3,    98,    94,    18,    65,    30,   112,    37,
     107,    30,    19,   119,    65,   114,    92,    65,    65,    94,
     108,    65,   118,    11,    30,    60,   115,    19,   116,    18,
     112,    30,   107,   119,    65,   114,    93,    65,    94,    65,
     115,   116,    30,    65
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    70,    71,    71,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    82,    83,    83,    84,    85,    86,    86,    87,    87,
      87,    87,    88,    89,    89,    89,    89,    89,    90,    91,
      92,    92,    93,    93,    94,    94,    94,    94,    95,    96,
      97,    98,    98,    99,   100,   100,   100,   100,   100,   101,
     101,   101,   101,   101,   102,   102,   102,   102,   103,   103,
     103,   103,   103,   104,   104,   105,   106,   106,   107,   107,
     108,   108,   108,   108,   109,   109,   110,   110,   111,   111,
     111,   111,   111,   111,   111,   111,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   113,   113,   114,   114,
     115,   115,   115,   116,   116,   117,   117,   118,   118,   119,
     119,   120
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    10,     0,     3,     4,     8,     0,     3,     5,     2,
       4,     3,     1,     1,     1,     1,     1,     1,     1,    10,
       0,     3,     0,     6,     1,     1,     1,     1,     5,     8,
       1,     0,     1,    10,     1,     2,     4,     4,     2,     0,
       3,     5,     5,     3,     4,     4,     6,     4,     1,     1,
       1,     1,     1,     0,     3,     6,     0,     2,     0,     3,
       5,     5,     7,     3,     0,     3,     0,     3,     3,     3,
       3,     3,     5,     5,     7,     7,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     2,     0,     4,     2,     4,
       0,     1,     1,     0,     3,     0,     4,     1,     3,     0,
       3,     8
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
#line 204 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1470 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 209 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1478 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 214 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1486 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 220 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1494 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 226 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1502 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 232 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1510 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 238 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1519 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 244 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1527 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 250 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1536 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 258 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, 0, (yyvsp[-7].string), (yyvsp[-5].string));
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1546 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 264 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";(unique)
			create_index_init(&CONTEXT->ssql->sstr.create_index, 1, (yyvsp[-6].string), (yyvsp[-4].string));
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-2].string));
		}
#line 1556 "yacc_sql.tab.c"
    break;

  case 33: /* id_list: COMMA ID id_list  */
#line 273 "yacc_sql.y"
                           {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1564 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 280 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1573 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 287 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1585 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 297 "yacc_sql.y"
                                   {    }
#line 1591 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 302 "yacc_sql.y"
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
#line 1606 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type  */
#line 313 "yacc_sql.y"
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
#line 1622 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type NOT_T NULL_T  */
#line 325 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1633 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type NULLABLE_T  */
#line 332 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1644 "yacc_sql.tab.c"
    break;

  case 42: /* number: NUMBER  */
#line 341 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1650 "yacc_sql.tab.c"
    break;

  case 43: /* type: INT_T  */
#line 344 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1656 "yacc_sql.tab.c"
    break;

  case 44: /* type: STRING_T  */
#line 345 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1662 "yacc_sql.tab.c"
    break;

  case 45: /* type: FLOAT_T  */
#line 346 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1668 "yacc_sql.tab.c"
    break;

  case 46: /* type: DATE_T  */
#line 347 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1674 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 348 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1680 "yacc_sql.tab.c"
    break;

  case 48: /* ID_get: ID  */
#line 352 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1689 "yacc_sql.tab.c"
    break;

  case 49: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE insert_pair_list SEMICOLON  */
#line 361 "yacc_sql.y"
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
#line 1709 "yacc_sql.tab.c"
    break;

  case 50: /* value_list: %empty  */
#line 378 "yacc_sql.y"
                {
		// TODO(wq): 插入数据
		// 递增pair_num, 清零value_length
		inserts_append_values(&CONTEXT->ssql->sstr.insertion, CONTEXT->insert_pair_num++, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1720 "yacc_sql.tab.c"
    break;

  case 51: /* value_list: COMMA value value_list  */
#line 384 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	}
#line 1728 "yacc_sql.tab.c"
    break;

  case 53: /* insert_pair_list: COMMA LBRACE value value_list RBRACE insert_pair_list  */
#line 391 "yacc_sql.y"
                                                                {
		}
#line 1735 "yacc_sql.tab.c"
    break;

  case 54: /* value: NUMBER  */
#line 396 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1743 "yacc_sql.tab.c"
    break;

  case 55: /* value: FLOAT  */
#line 399 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1751 "yacc_sql.tab.c"
    break;

  case 56: /* value: SSS  */
#line 402 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1760 "yacc_sql.tab.c"
    break;

  case 57: /* value: NULL_T  */
#line 406 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		}
#line 1768 "yacc_sql.tab.c"
    break;

  case 58: /* delete: DELETE FROM ID where SEMICOLON  */
#line 413 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions[0], CONTEXT->condition_length[0]);
			CONTEXT->condition_length[0] = 0;
    }
#line 1780 "yacc_sql.tab.c"
    break;

  case 59: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 423 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions[0], CONTEXT->condition_length[0]);
			CONTEXT->condition_length[0] = 0;
		}
#line 1792 "yacc_sql.tab.c"
    break;

  case 60: /* select_begin: SELECT  */
#line 433 "yacc_sql.y"
           {
    	CONTEXT->select_length++;
    	show_selects(CONTEXT->selects, CONTEXT->select_length-1);
    }
#line 1801 "yacc_sql.tab.c"
    break;

  case 61: /* select_end: %empty  */
#line 440 "yacc_sql.y"
                {
    }
#line 1808 "yacc_sql.tab.c"
    break;

  case 62: /* select_end: SEMICOLON  */
#line 442 "yacc_sql.y"
                {
    }
#line 1815 "yacc_sql.tab.c"
    break;

  case 63: /* select: select_begin select_attr FROM ID rel_list inner_join_list where group_by order_by select_end  */
#line 448 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->selects[CONTEXT->select_length-1], (yyvsp[-6].string));

			selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length-1], CONTEXT->conditions[CONTEXT->select_length-1], CONTEXT->condition_length[CONTEXT->select_length-1]);

			selects_append_joins(&CONTEXT->selects[CONTEXT->select_length-1], CONTEXT->joins[CONTEXT->select_length-1], CONTEXT->join_length[CONTEXT->select_length-1]);

			//临时变量清零
			CONTEXT->ssql->sstr.selection = CONTEXT->selects[CONTEXT->select_length-1];
			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			CONTEXT->condition_length[CONTEXT->select_length-1]=0;
			CONTEXT->from_length[CONTEXT->select_length-1]=0;
			CONTEXT->value_length = 0;
			CONTEXT->join_length[CONTEXT->select_length-1]=0;
    			CONTEXT->select_length--;
	}
#line 1838 "yacc_sql.tab.c"
    break;

  case 64: /* select_attr: STAR  */
#line 469 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
#line 1848 "yacc_sql.tab.c"
    break;

  case 65: /* select_attr: ID attr_list  */
#line 474 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
#line 1858 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: ID DOT ID attr_list  */
#line 479 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
#line 1868 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: ID DOT STAR attr_list  */
#line 484 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
#line 1878 "yacc_sql.tab.c"
    break;

  case 70: /* attr_list: COMMA ID attr_list  */
#line 494 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1890 "yacc_sql.tab.c"
    break;

  case 71: /* attr_list: COMMA ID DOT ID attr_list  */
#line 501 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1902 "yacc_sql.tab.c"
    break;

  case 72: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 508 "yacc_sql.y"
                                  {
    			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
    	}
#line 1912 "yacc_sql.tab.c"
    break;

  case 74: /* aggre_func: aggre_type LBRACE value RBRACE  */
#line 517 "yacc_sql.y"
                                       {
		Aggregate aggre;
		Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 0, NULL, NULL, value);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	  }
#line 1923 "yacc_sql.tab.c"
    break;

  case 75: /* aggre_func: aggre_type LBRACE ID RBRACE  */
#line 523 "yacc_sql.y"
                                      {
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 1, NULL, (yyvsp[-1].string), NULL);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	  }
#line 1933 "yacc_sql.tab.c"
    break;

  case 76: /* aggre_func: aggre_type LBRACE ID DOT ID RBRACE  */
#line 528 "yacc_sql.y"
                                             {
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 1, (yyvsp[-3].string), (yyvsp[-1].string), NULL);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	  }
#line 1943 "yacc_sql.tab.c"
    break;

  case 77: /* aggre_func: aggre_type LBRACE STAR RBRACE  */
#line 533 "yacc_sql.y"
                                        {
		// TODO(wq):仅需要支持 select COUNT(*)，不需要支持select other_aggre(*) 以及select aggre_func(table_name.*);
		// 由于如果在语法解析里处理该问题的话，代码写的比较冗余丑陋，所以这里不检查sum(*)等这种不合法情况，丢给parse之后的stage去检验
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 1, NULL, "*", NULL);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	}
#line 1955 "yacc_sql.tab.c"
    break;

  case 78: /* aggre_type: MAX_T  */
#line 543 "yacc_sql.y"
                { CONTEXT->aggreType[CONTEXT->select_length-1] = MAXS; }
#line 1961 "yacc_sql.tab.c"
    break;

  case 79: /* aggre_type: MIN_T  */
#line 544 "yacc_sql.y"
                { CONTEXT->aggreType[CONTEXT->select_length-1] = MINS; }
#line 1967 "yacc_sql.tab.c"
    break;

  case 80: /* aggre_type: AVG_T  */
#line 545 "yacc_sql.y"
                { CONTEXT->aggreType[CONTEXT->select_length-1] = AVGS; }
#line 1973 "yacc_sql.tab.c"
    break;

  case 81: /* aggre_type: SUM_T  */
#line 546 "yacc_sql.y"
                { CONTEXT->aggreType[CONTEXT->select_length-1] = SUMS; }
#line 1979 "yacc_sql.tab.c"
    break;

  case 82: /* aggre_type: COUNT_T  */
#line 547 "yacc_sql.y"
                  { CONTEXT->aggreType[CONTEXT->select_length-1] = COUNTS; }
#line 1985 "yacc_sql.tab.c"
    break;

  case 84: /* rel_list: COMMA ID rel_list  */
#line 552 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->selects[CONTEXT->select_length-1], (yyvsp[-1].string));
		  }
#line 1993 "yacc_sql.tab.c"
    break;

  case 85: /* inner_join: INNER JOIN ID ON join_condition join_condition_list  */
#line 558 "yacc_sql.y"
                                                        {
    	Join join;
    	join_init(&join, INNER_JOIN, (yyvsp[-3].string), CONTEXT->join_conditions[CONTEXT->select_length-1], CONTEXT->join_condition_length[CONTEXT->select_length-1]);
    	CONTEXT->joins[CONTEXT->select_length-1][CONTEXT->join_length[CONTEXT->select_length-1]++] = join;
    	// 清空变量
    	CONTEXT->join_condition_length[CONTEXT->select_length-1] = 0;
    }
#line 2005 "yacc_sql.tab.c"
    break;

  case 87: /* inner_join_list: inner_join inner_join_list  */
#line 569 "yacc_sql.y"
                                  {

    }
#line 2013 "yacc_sql.tab.c"
    break;

  case 89: /* join_condition_list: AND join_condition join_condition_list  */
#line 576 "yacc_sql.y"
                                              {

     }
#line 2021 "yacc_sql.tab.c"
    break;

  case 90: /* join_condition: ID DOT ID comOp value  */
#line 582 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value, NULL);
			CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->join_condition_length[CONTEXT->select_length-1]++] = condition;

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
#line 2046 "yacc_sql.tab.c"
    break;

  case 91: /* join_condition: value comOp ID DOT ID  */
#line 603 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL, NULL);
			CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->join_condition_length[CONTEXT->select_length-1]++] = condition;
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
#line 2071 "yacc_sql.tab.c"
    break;

  case 92: /* join_condition: ID DOT ID comOp ID DOT ID  */
#line 624 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL, NULL);
			CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->join_condition_length[CONTEXT->select_length-1]++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2094 "yacc_sql.tab.c"
    break;

  case 93: /* join_condition: value comOp value  */
#line 643 "yacc_sql.y"
                {
    			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
    			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

    			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value, NULL);
			CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->join_condition_length[CONTEXT->select_length-1]++] = condition;

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
#line 2119 "yacc_sql.tab.c"
    break;

  case 95: /* where: WHERE condition condition_list  */
#line 666 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2127 "yacc_sql.tab.c"
    break;

  case 97: /* condition_list: AND condition condition_list  */
#line 673 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2135 "yacc_sql.tab.c"
    break;

  case 98: /* condition: ID comOp value  */
#line 679 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value, NULL);
			CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
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
#line 2160 "yacc_sql.tab.c"
    break;

  case 99: /* condition: value comOp value  */
#line 700 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value, NULL);
			CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
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
#line 2184 "yacc_sql.tab.c"
    break;

  case 100: /* condition: ID comOp ID  */
#line 720 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL, NULL);
			CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2208 "yacc_sql.tab.c"
    break;

  case 101: /* condition: value comOp ID  */
#line 740 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL, NULL);
			CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;

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
#line 2234 "yacc_sql.tab.c"
    break;

  case 102: /* condition: ID DOT ID comOp value  */
#line 762 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value, NULL);
			CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;

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
#line 2259 "yacc_sql.tab.c"
    break;

  case 103: /* condition: value comOp ID DOT ID  */
#line 783 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL, NULL);
			CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
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
#line 2284 "yacc_sql.tab.c"
    break;

  case 104: /* condition: ID DOT ID comOp ID DOT ID  */
#line 804 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL, NULL);
			CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2307 "yacc_sql.tab.c"
    break;

  case 105: /* condition: ID DOT ID comOp LBRACE select RBRACE  */
#line 822 "yacc_sql.y"
                                           {
    	RelAttr left_attr;
	relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
	Condition condition;
	condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, NULL, &CONTEXT->selects[CONTEXT->select_length]);
	CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2319 "yacc_sql.tab.c"
    break;

  case 106: /* comOp: EQ  */
#line 832 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2325 "yacc_sql.tab.c"
    break;

  case 107: /* comOp: LT  */
#line 833 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2331 "yacc_sql.tab.c"
    break;

  case 108: /* comOp: GT  */
#line 834 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2337 "yacc_sql.tab.c"
    break;

  case 109: /* comOp: LE  */
#line 835 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2343 "yacc_sql.tab.c"
    break;

  case 110: /* comOp: GE  */
#line 836 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2349 "yacc_sql.tab.c"
    break;

  case 111: /* comOp: NE  */
#line 837 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2355 "yacc_sql.tab.c"
    break;

  case 112: /* comOp: IS_T  */
#line 838 "yacc_sql.y"
               { CONTEXT->comp = IS; }
#line 2361 "yacc_sql.tab.c"
    break;

  case 113: /* comOp: IS_T NOT_T  */
#line 839 "yacc_sql.y"
                     { CONTEXT->comp = IS_NOT; }
#line 2367 "yacc_sql.tab.c"
    break;

  case 114: /* comOp: IN  */
#line 840 "yacc_sql.y"
        { CONTEXT->comp = IN_OP; }
#line 2373 "yacc_sql.tab.c"
    break;

  case 115: /* comOp: NOT_T IN  */
#line 841 "yacc_sql.y"
              { CONTEXT->comp = NOT_IN_OP; }
#line 2379 "yacc_sql.tab.c"
    break;

  case 118: /* order_item: ID order  */
#line 850 "yacc_sql.y"
                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_order(&CONTEXT->selects[CONTEXT->select_length-1], &attr, CONTEXT->order);
	}
#line 2389 "yacc_sql.tab.c"
    break;

  case 119: /* order_item: ID DOT ID order  */
#line 855 "yacc_sql.y"
                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_order(&CONTEXT->selects[CONTEXT->select_length-1], &attr, CONTEXT->order);
	}
#line 2399 "yacc_sql.tab.c"
    break;

  case 120: /* order: %empty  */
#line 863 "yacc_sql.y"
                    {
		CONTEXT->order = 0;
	}
#line 2407 "yacc_sql.tab.c"
    break;

  case 121: /* order: ASC  */
#line 866 "yacc_sql.y"
              {
		CONTEXT->order = 0;
	}
#line 2415 "yacc_sql.tab.c"
    break;

  case 122: /* order: DESC  */
#line 869 "yacc_sql.y"
               {
		CONTEXT->order = 1;
	}
#line 2423 "yacc_sql.tab.c"
    break;

  case 127: /* group_item: ID  */
#line 885 "yacc_sql.y"
           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		selects_append_group(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 2433 "yacc_sql.tab.c"
    break;

  case 128: /* group_item: ID DOT ID  */
#line 890 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		selects_append_group(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 2443 "yacc_sql.tab.c"
    break;

  case 131: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 905 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2452 "yacc_sql.tab.c"
    break;


#line 2456 "yacc_sql.tab.c"

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

#line 910 "yacc_sql.y"

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
