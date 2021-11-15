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

  Selects left_sub_select;
  Selects right_sub_select;

  size_t value_length;
  Value values[MAX_NUM];
  size_t insert_pair_num;
  CompOp comp[MAX_NUM];
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


#line 158 "yacc_sql.tab.c"

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
  YYSYMBOL_delete_begin = 95,              /* delete_begin  */
  YYSYMBOL_delete = 96,                    /* delete  */
  YYSYMBOL_update_begin = 97,              /* update_begin  */
  YYSYMBOL_update = 98,                    /* update  */
  YYSYMBOL_select_begin = 99,              /* select_begin  */
  YYSYMBOL_select_end = 100,               /* select_end  */
  YYSYMBOL_select = 101,                   /* select  */
  YYSYMBOL_select_attr = 102,              /* select_attr  */
  YYSYMBOL_attr_list = 103,                /* attr_list  */
  YYSYMBOL_aggre_func = 104,               /* aggre_func  */
  YYSYMBOL_aggre_type = 105,               /* aggre_type  */
  YYSYMBOL_rel_list = 106,                 /* rel_list  */
  YYSYMBOL_inner_join = 107,               /* inner_join  */
  YYSYMBOL_inner_join_list = 108,          /* inner_join_list  */
  YYSYMBOL_join_condition_list = 109,      /* join_condition_list  */
  YYSYMBOL_join_condition = 110,           /* join_condition  */
  YYSYMBOL_where = 111,                    /* where  */
  YYSYMBOL_condition_list = 112,           /* condition_list  */
  YYSYMBOL_condition = 113,                /* condition  */
  YYSYMBOL_left_sub_select = 114,          /* left_sub_select  */
  YYSYMBOL_right_sub_select = 115,         /* right_sub_select  */
  YYSYMBOL_comOp = 116,                    /* comOp  */
  YYSYMBOL_order_by = 117,                 /* order_by  */
  YYSYMBOL_order_item = 118,               /* order_item  */
  YYSYMBOL_order = 119,                    /* order  */
  YYSYMBOL_order_item_list = 120,          /* order_item_list  */
  YYSYMBOL_group_by = 121,                 /* group_by  */
  YYSYMBOL_group_item = 122,               /* group_item  */
  YYSYMBOL_group_item_list = 123,          /* group_item_list  */
  YYSYMBOL_load_data = 124                 /* load_data  */
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
#define YYLAST   309

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  144
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  296

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
       0,   181,   181,   183,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   207,   212,   217,   223,   229,   235,   241,   247,   253,
     260,   266,   274,   276,   282,   289,   298,   300,   304,   315,
     327,   334,   344,   347,   348,   349,   350,   351,   354,   363,
     381,   387,   392,   394,   399,   402,   405,   409,   415,   421,
     432,   438,   449,   456,   458,   463,   486,   491,   496,   501,
     506,   509,   511,   518,   525,   530,   534,   540,   545,   550,
     560,   561,   562,   563,   564,   567,   569,   575,   584,   586,
     591,   593,   598,   619,   640,   659,   680,   687,   694,   701,
     708,   714,   716,   721,   723,   728,   749,   769,   789,   811,
     832,   853,   872,   879,   886,   893,   900,   908,   914,   920,
     921,   922,   923,   924,   925,   926,   927,   928,   929,   932,
     934,   938,   943,   951,   954,   957,   962,   964,   967,   969,
     973,   978,   985,   987,   992
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
  "value_list", "insert_pair_list", "value", "delete_begin", "delete",
  "update_begin", "update", "select_begin", "select_end", "select",
  "select_attr", "attr_list", "aggre_func", "aggre_type", "rel_list",
  "inner_join", "inner_join_list", "join_condition_list", "join_condition",
  "where", "condition_list", "condition", "left_sub_select",
  "right_sub_select", "comOp", "order_by", "order_item", "order",
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

#define YYPACT_NINF (-221)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -221,   147,  -221,   111,    26,  -221,   -49,    34,    24,     2,
    -221,  -221,    45,    46,    72,    77,    86,    54,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,    43,  -221,    50,  -221,   134,  -221,  -221,    51,
     112,    60,    64,    74,   119,   139,  -221,    78,  -221,  -221,
    -221,  -221,  -221,   103,    81,   115,  -221,  -221,  -221,  -221,
    -221,   -12,  -221,   116,   135,   148,   149,    91,   125,   167,
     170,  -221,  -221,   142,   117,   151,   118,   -21,    20,  -221,
     121,  -221,   127,   123,   150,   128,  -221,  -221,   179,   169,
     -13,   195,   153,    93,   135,   135,   135,   191,  -221,  -221,
    -221,    -1,  -221,   196,   197,  -221,   194,   201,   152,   205,
      19,   212,   219,    57,   155,   193,   155,  -221,    19,    73,
    -221,  -221,  -221,  -221,   166,   198,  -221,   171,  -221,  -221,
     123,   214,  -221,  -221,  -221,  -221,  -221,   -11,   217,   172,
     216,   173,   221,   175,  -221,  -221,  -221,  -221,  -221,  -221,
     180,   188,  -221,    -8,    35,   -13,  -221,    -3,   151,   135,
     135,   191,   207,   198,   151,   226,   194,   242,   183,   192,
    -221,   184,   229,    19,   232,   248,  -221,   155,  -221,  -221,
     219,  -221,  -221,  -221,   222,  -221,   193,   223,  -221,   251,
    -221,  -221,  -221,   190,  -221,   199,  -221,  -221,  -221,  -221,
     238,  -221,   239,   200,   240,   216,   241,  -221,     3,   244,
     202,  -221,   203,  -221,   220,   204,   206,  -221,   263,   229,
     266,  -221,   253,   268,   243,  -221,  -221,  -221,  -221,  -221,
      14,   209,   213,   272,  -221,  -221,  -221,    19,  -221,   211,
      83,   155,   245,   155,   247,   259,   215,  -221,  -221,   216,
    -221,   218,   262,   156,    14,  -221,    -2,   224,   209,  -221,
       0,   265,   267,   155,  -221,   256,  -221,   245,   257,  -221,
    -221,   259,  -221,   225,  -221,  -221,   215,  -221,   241,    29,
     227,  -221,   228,  -221,     1,   265,  -221,   258,  -221,  -221,
    -221,  -221,  -221,  -221,   230,  -221
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    62,     0,     0,     0,     0,
      58,    60,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     0,     7,     0,     6,     0,     4,    18,     0,
       0,     0,     0,     0,     0,     0,    23,     0,    24,    25,
      26,    22,    21,     0,     0,     0,    80,    81,    82,    83,
      84,    71,    66,     0,    71,     0,     0,     0,     0,     0,
       0,    29,    28,     0,     0,   101,     0,     0,     0,    67,
       0,    70,     0,     0,     0,     0,    27,    34,     0,     0,
       0,     0,     0,    71,    71,    71,    71,    85,    57,    54,
      55,     0,    56,     0,     0,    48,    36,     0,     0,     0,
       0,     0,     0,     0,     0,   103,     0,    59,     0,     0,
      72,    75,    68,    69,     0,    88,    77,     0,    79,    76,
       0,     0,    43,    44,    45,    46,    47,    39,     0,     0,
      50,     0,     0,     0,   119,   120,   121,   122,   123,   124,
       0,   125,   127,     0,     0,     0,   102,     0,   101,    71,
      71,    85,     0,    88,   101,     0,    36,     0,     0,     0,
      41,     0,    32,     0,     0,     0,   117,     0,   128,   126,
       0,   107,   105,   112,   108,   106,   103,   113,   116,     0,
      73,    74,    86,     0,    89,   138,    78,    37,    35,    42,
       0,    40,     0,     0,     0,    50,    52,   144,     0,     0,
       0,   104,     0,    61,     0,     0,   129,    38,     0,    32,
       0,    51,     0,     0,     0,   109,   114,   118,   110,   115,
       0,     0,     0,    63,    31,    33,    30,     0,    49,     0,
       0,     0,    90,     0,   140,   142,     0,    64,    65,    50,
     111,     0,     0,     0,     0,    87,     0,     0,     0,   139,
     133,   136,     0,     0,    96,     0,    95,    90,    97,   100,
     141,   142,   135,     0,   134,   131,     0,   130,    52,     0,
       0,    91,     0,   143,   133,   136,    53,     0,    92,    98,
      93,    99,   132,   137,     0,    94
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,    62,  -221,  -221,   130,   161,  -221,  -221,
    -221,  -221,  -184,    16,   -82,  -221,  -221,  -221,  -221,  -221,
    -221,  -107,  -221,   -56,   231,  -221,   136,  -221,   137,    31,
      47,  -145,   113,   154,  -220,  -155,  -113,  -221,    27,    18,
      21,  -221,    49,    33,  -221
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   204,    29,    30,   131,   106,   200,   137,
     107,    31,   174,   223,   114,    32,    33,    34,    35,    36,
     248,    37,    63,    79,    64,    65,   125,   163,   164,   255,
     242,    91,   156,   115,   116,   183,   153,   233,   261,   275,
     277,   216,   245,   259,    38
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     104,   154,   188,   157,   112,   142,   168,    77,    81,   180,
     243,   272,   272,   189,   180,   180,    44,   126,    78,   195,
     180,   221,    56,    57,    58,    59,    60,    46,   140,   127,
     273,   112,    42,    47,   243,    43,   158,   120,   121,   122,
     123,    45,    98,   169,    93,   170,   180,    98,    48,    49,
      99,   100,   113,   226,   102,    99,   100,   181,    98,   102,
     274,   274,   187,   268,   208,   262,    99,   100,   224,    98,
     102,   182,   185,   209,    98,    50,    54,    99,   100,   240,
      51,   102,    99,   100,    98,    95,   102,   143,    96,    52,
      98,   205,    99,   100,   287,    53,   102,   264,    99,   100,
     184,   269,   102,   190,   191,   144,   145,   146,   147,   148,
     149,   150,    77,   251,   151,    55,    66,    39,   152,    40,
      41,    67,    71,   119,   289,    68,   225,   252,   253,    69,
     256,   144,   145,   146,   147,   148,   149,   150,   159,    70,
     151,   160,    72,    73,   152,    74,    75,     2,   241,    80,
     279,     3,     4,    76,    77,   249,    84,     5,     6,     7,
       8,     9,    10,    11,    85,    82,    83,    12,    13,    14,
      86,   266,   241,    87,    88,    15,    16,    56,    57,    58,
      59,    60,    98,    92,    89,    90,    97,    17,   105,   108,
      99,   100,   101,   109,   102,   103,   110,   288,   117,    61,
     111,   118,    62,   144,   145,   146,   147,   148,   149,   150,
     124,    98,   151,   130,   128,   129,   152,   138,   141,    99,
     100,   265,   139,   102,   132,   133,   134,   135,   136,     5,
     155,   161,   167,   162,   171,   173,   165,   172,   175,   176,
     177,   178,   179,   193,   196,   198,   199,   201,   203,   202,
     206,   207,   210,   212,   213,   214,   217,   218,   220,   230,
     222,   215,   227,   231,   232,   219,   234,   228,   229,   236,
     237,   238,   246,   239,   244,   247,   250,   257,   258,   180,
     260,   235,   254,   263,   276,   278,   280,   282,   294,   270,
     284,   166,   290,   291,   286,   295,   197,   192,   281,   211,
     194,   267,   292,   285,   283,     0,   293,   271,    94,   186
};

static const yytype_int16 yycheck[] =
{
      82,   114,   157,   116,    17,   112,    17,    19,    64,    17,
     230,    11,    11,   158,    17,    17,    65,    18,    30,   164,
      17,   205,    43,    44,    45,    46,    47,     3,   110,    30,
      30,    17,     6,    31,   254,     9,   118,    93,    94,    95,
      96,     7,    55,    54,    65,    56,    17,    55,     3,     3,
      63,    64,    65,   208,    67,    63,    64,    65,    55,    67,
      60,    60,    65,    65,   177,   249,    63,    64,    65,    55,
      67,   153,   154,   180,    55,     3,    33,    63,    64,    65,
       3,    67,    63,    64,    55,    65,    67,    30,    68,     3,
      55,   173,    63,    64,    65,    41,    67,   252,    63,    64,
      65,   256,    67,   159,   160,    48,    49,    50,    51,    52,
      53,    54,    19,    30,    57,    65,    65,     6,    61,     8,
       9,     9,     3,    30,   279,    65,   208,   240,   241,    65,
     243,    48,    49,    50,    51,    52,    53,    54,    65,    65,
      57,    68,     3,    65,    61,    42,    65,     0,   230,    33,
     263,     4,     5,    38,    19,   237,    65,    10,    11,    12,
      13,    14,    15,    16,    39,    17,    17,    20,    21,    22,
       3,   253,   254,     3,    32,    28,    29,    43,    44,    45,
      46,    47,    55,    65,    67,    34,    65,    40,    65,    39,
      63,    64,    65,    65,    67,    68,    17,   279,     3,    65,
      31,    48,    68,    48,    49,    50,    51,    52,    53,    54,
      19,    55,    57,    19,    18,    18,    61,    65,     6,    63,
      64,    65,    17,    67,    23,    24,    25,    26,    27,    10,
      37,    65,    18,    35,    17,    19,    65,    65,    65,    18,
      65,    61,    54,    36,    18,     3,    63,    55,    19,    65,
      18,     3,    30,    30,     3,    65,    18,    18,    18,    39,
      19,    62,    18,    59,    58,    65,     3,    65,    65,     3,
      17,     3,    59,    30,    65,     3,    65,    30,    19,    17,
      65,   219,    37,    65,    19,    18,    30,    30,    30,    65,
      65,   130,    65,    65,   278,    65,   166,   161,   267,   186,
     163,   254,   284,   276,   271,    -1,   285,   258,    77,   155
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    71,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    28,    29,    40,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    84,
      85,    91,    95,    96,    97,    98,    99,   101,   124,     6,
       8,     9,     6,     9,    65,     7,     3,    31,     3,     3,
       3,     3,     3,    41,    33,    65,    43,    44,    45,    46,
      47,    65,    68,   102,   104,   105,    65,     9,    65,    65,
      65,     3,     3,    65,    42,    65,    38,    19,    30,   103,
      33,   103,    17,    17,    65,    39,     3,     3,    32,    67,
      34,   111,    65,    65,   104,    65,    68,    65,    55,    63,
      64,    65,    67,    68,    94,    65,    87,    90,    39,    65,
      17,    31,    17,    65,    94,   113,   114,     3,    48,    30,
     103,   103,   103,   103,    19,   106,    18,    30,    18,    18,
      19,    86,    23,    24,    25,    26,    27,    89,    65,    17,
      94,     6,   101,    30,    48,    49,    50,    51,    52,    53,
      54,    57,    61,   116,   116,    37,   112,   116,    94,    65,
      68,    65,    35,   107,   108,    65,    87,    18,    17,    54,
      56,    17,    65,    19,    92,    65,    18,    65,    61,    54,
      17,    65,    94,   115,    65,    94,   113,    65,   115,   111,
     103,   103,   106,    36,   108,   111,    18,    86,     3,    63,
      88,    55,    65,    19,    83,    94,    18,     3,   116,   101,
      30,   112,    30,     3,    65,    62,   121,    18,    18,    65,
      18,    92,    19,    93,    65,    94,   115,    18,    65,    65,
      39,    59,    58,   117,     3,    83,     3,    17,     3,    30,
      65,    94,   110,   114,    65,   122,    59,     3,   100,    94,
      65,    30,   116,   116,    37,   109,   116,    30,    19,   123,
      65,   118,    92,    65,   115,    65,    94,   110,    65,   115,
      65,   122,    11,    30,    60,   119,    19,   120,    18,   116,
      30,   109,    30,   123,    65,   118,    93,    65,    94,   115,
      65,    65,   119,   120,    30,    65
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
      97,    98,    99,   100,   100,   101,   102,   102,   102,   102,
     102,   103,   103,   103,   103,   103,   104,   104,   104,   104,
     105,   105,   105,   105,   105,   106,   106,   107,   108,   108,
     109,   109,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   111,   111,   112,   112,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   114,   115,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   117,
     117,   118,   118,   119,   119,   119,   120,   120,   121,   121,
     122,   122,   123,   123,   124
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    10,     0,     3,     4,     8,     0,     3,     5,     2,
       4,     3,     1,     1,     1,     1,     1,     1,     1,    10,
       0,     3,     0,     6,     1,     1,     1,     1,     1,     5,
       1,     8,     1,     0,     1,    10,     1,     2,     4,     4,
       2,     0,     3,     5,     5,     3,     4,     4,     6,     4,
       1,     1,     1,     1,     1,     0,     3,     6,     0,     2,
       0,     3,     5,     5,     7,     3,     3,     3,     5,     5,
       3,     0,     3,     0,     3,     3,     3,     3,     3,     5,
       5,     7,     3,     3,     5,     5,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     0,
       4,     2,     4,     0,     1,     1,     0,     3,     0,     4,
       1,     3,     0,     3,     8
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
#line 207 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1491 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 212 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1499 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 217 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1507 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 223 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1515 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 229 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1523 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 235 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1531 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 241 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1540 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 247 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1548 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 253 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1557 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 261 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, 0, (yyvsp[-7].string), (yyvsp[-5].string));
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1567 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 267 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";(unique)
			create_index_init(&CONTEXT->ssql->sstr.create_index, 1, (yyvsp[-6].string), (yyvsp[-4].string));
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-2].string));
		}
#line 1577 "yacc_sql.tab.c"
    break;

  case 33: /* id_list: COMMA ID id_list  */
#line 276 "yacc_sql.y"
                           {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1585 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 283 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1594 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 290 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1606 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 300 "yacc_sql.y"
                                   {    }
#line 1612 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 305 "yacc_sql.y"
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
#line 1627 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type  */
#line 316 "yacc_sql.y"
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
#line 1643 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type NOT_T NULL_T  */
#line 328 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1654 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type NULLABLE_T  */
#line 335 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1665 "yacc_sql.tab.c"
    break;

  case 42: /* number: NUMBER  */
#line 344 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1671 "yacc_sql.tab.c"
    break;

  case 43: /* type: INT_T  */
#line 347 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1677 "yacc_sql.tab.c"
    break;

  case 44: /* type: STRING_T  */
#line 348 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1683 "yacc_sql.tab.c"
    break;

  case 45: /* type: FLOAT_T  */
#line 349 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1689 "yacc_sql.tab.c"
    break;

  case 46: /* type: DATE_T  */
#line 350 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1695 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 351 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1701 "yacc_sql.tab.c"
    break;

  case 48: /* ID_get: ID  */
#line 355 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1710 "yacc_sql.tab.c"
    break;

  case 49: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE insert_pair_list SEMICOLON  */
#line 364 "yacc_sql.y"
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
#line 1730 "yacc_sql.tab.c"
    break;

  case 50: /* value_list: %empty  */
#line 381 "yacc_sql.y"
                {
		// TODO(wq): 插入数据
		// 递增pair_num, 清零value_length
		inserts_append_values(&CONTEXT->ssql->sstr.insertion, CONTEXT->insert_pair_num++, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1741 "yacc_sql.tab.c"
    break;

  case 51: /* value_list: COMMA value value_list  */
#line 387 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	}
#line 1749 "yacc_sql.tab.c"
    break;

  case 53: /* insert_pair_list: COMMA LBRACE value value_list RBRACE insert_pair_list  */
#line 394 "yacc_sql.y"
                                                                {
		}
#line 1756 "yacc_sql.tab.c"
    break;

  case 54: /* value: NUMBER  */
#line 399 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1764 "yacc_sql.tab.c"
    break;

  case 55: /* value: FLOAT  */
#line 402 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1772 "yacc_sql.tab.c"
    break;

  case 56: /* value: SSS  */
#line 405 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1781 "yacc_sql.tab.c"
    break;

  case 57: /* value: NULL_T  */
#line 409 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		}
#line 1789 "yacc_sql.tab.c"
    break;

  case 58: /* delete_begin: DELETE  */
#line 415 "yacc_sql.y"
           {
    	CONTEXT->select_length++;
    }
#line 1797 "yacc_sql.tab.c"
    break;

  case 59: /* delete: delete_begin FROM ID where SEMICOLON  */
#line 422 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions[0], CONTEXT->condition_length[0]);
			CONTEXT->condition_length[0] = 0;
    }
#line 1809 "yacc_sql.tab.c"
    break;

  case 60: /* update_begin: UPDATE  */
#line 432 "yacc_sql.y"
          {
   	CONTEXT->select_length++;
   }
#line 1817 "yacc_sql.tab.c"
    break;

  case 61: /* update: update_begin ID SET ID EQ value where SEMICOLON  */
#line 439 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions[0], CONTEXT->condition_length[0]);
			CONTEXT->condition_length[0] = 0;
		}
#line 1829 "yacc_sql.tab.c"
    break;

  case 62: /* select_begin: SELECT  */
#line 449 "yacc_sql.y"
           {
    	CONTEXT->select_length++;
    	clear_selects(&CONTEXT->selects[CONTEXT->select_length-1]);
    }
#line 1838 "yacc_sql.tab.c"
    break;

  case 63: /* select_end: %empty  */
#line 456 "yacc_sql.y"
                {
    }
#line 1845 "yacc_sql.tab.c"
    break;

  case 64: /* select_end: SEMICOLON  */
#line 458 "yacc_sql.y"
                {
    }
#line 1852 "yacc_sql.tab.c"
    break;

  case 65: /* select: select_begin select_attr FROM ID rel_list inner_join_list where group_by order_by select_end  */
#line 464 "yacc_sql.y"
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
    			show_selects(CONTEXT->selects, CONTEXT->select_length-1);
    			CONTEXT->select_length--;
	}
#line 1876 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: STAR  */
#line 486 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
#line 1886 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: ID attr_list  */
#line 491 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
#line 1896 "yacc_sql.tab.c"
    break;

  case 68: /* select_attr: ID DOT ID attr_list  */
#line 496 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
#line 1906 "yacc_sql.tab.c"
    break;

  case 69: /* select_attr: ID DOT STAR attr_list  */
#line 501 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
#line 1916 "yacc_sql.tab.c"
    break;

  case 72: /* attr_list: COMMA ID attr_list  */
#line 511 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1928 "yacc_sql.tab.c"
    break;

  case 73: /* attr_list: COMMA ID DOT ID attr_list  */
#line 518 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1940 "yacc_sql.tab.c"
    break;

  case 74: /* attr_list: COMMA ID DOT STAR attr_list  */
#line 525 "yacc_sql.y"
                                  {
    			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
    	}
#line 1950 "yacc_sql.tab.c"
    break;

  case 76: /* aggre_func: aggre_type LBRACE value RBRACE  */
#line 534 "yacc_sql.y"
                                       {
		Aggregate aggre;
		Value *value = &CONTEXT->values[CONTEXT->value_length - 1];
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 0, NULL, NULL, value);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	  }
#line 1961 "yacc_sql.tab.c"
    break;

  case 77: /* aggre_func: aggre_type LBRACE ID RBRACE  */
#line 540 "yacc_sql.y"
                                      {
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 1, NULL, (yyvsp[-1].string), NULL);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	  }
#line 1971 "yacc_sql.tab.c"
    break;

  case 78: /* aggre_func: aggre_type LBRACE ID DOT ID RBRACE  */
#line 545 "yacc_sql.y"
                                             {
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 1, (yyvsp[-3].string), (yyvsp[-1].string), NULL);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	  }
#line 1981 "yacc_sql.tab.c"
    break;

  case 79: /* aggre_func: aggre_type LBRACE STAR RBRACE  */
#line 550 "yacc_sql.y"
                                        {
		// TODO(wq):仅需要支持 select COUNT(*)，不需要支持select other_aggre(*) 以及select aggre_func(table_name.*);
		// 由于如果在语法解析里处理该问题的话，代码写的比较冗余丑陋，所以这里不检查sum(*)等这种不合法情况，丢给parse之后的stage去检验
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 1, NULL, "*", NULL);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	}
#line 1993 "yacc_sql.tab.c"
    break;

  case 80: /* aggre_type: MAX_T  */
#line 560 "yacc_sql.y"
                { CONTEXT->aggreType[CONTEXT->select_length-1] = MAXS; }
#line 1999 "yacc_sql.tab.c"
    break;

  case 81: /* aggre_type: MIN_T  */
#line 561 "yacc_sql.y"
                { CONTEXT->aggreType[CONTEXT->select_length-1] = MINS; }
#line 2005 "yacc_sql.tab.c"
    break;

  case 82: /* aggre_type: AVG_T  */
#line 562 "yacc_sql.y"
                { CONTEXT->aggreType[CONTEXT->select_length-1] = AVGS; }
#line 2011 "yacc_sql.tab.c"
    break;

  case 83: /* aggre_type: SUM_T  */
#line 563 "yacc_sql.y"
                { CONTEXT->aggreType[CONTEXT->select_length-1] = SUMS; }
#line 2017 "yacc_sql.tab.c"
    break;

  case 84: /* aggre_type: COUNT_T  */
#line 564 "yacc_sql.y"
                  { CONTEXT->aggreType[CONTEXT->select_length-1] = COUNTS; }
#line 2023 "yacc_sql.tab.c"
    break;

  case 86: /* rel_list: COMMA ID rel_list  */
#line 569 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->selects[CONTEXT->select_length-1], (yyvsp[-1].string));
		  }
#line 2031 "yacc_sql.tab.c"
    break;

  case 87: /* inner_join: INNER JOIN ID ON join_condition join_condition_list  */
#line 575 "yacc_sql.y"
                                                        {
    	Join join;
    	join_init(&join, INNER_JOIN, (yyvsp[-3].string), CONTEXT->join_conditions[CONTEXT->select_length-1], CONTEXT->join_condition_length[CONTEXT->select_length-1]);
    	CONTEXT->joins[CONTEXT->select_length-1][CONTEXT->join_length[CONTEXT->select_length-1]++] = join;
    	// 清空变量
    	CONTEXT->join_condition_length[CONTEXT->select_length-1] = 0;
    }
#line 2043 "yacc_sql.tab.c"
    break;

  case 89: /* inner_join_list: inner_join inner_join_list  */
#line 586 "yacc_sql.y"
                                  {

    }
#line 2051 "yacc_sql.tab.c"
    break;

  case 91: /* join_condition_list: AND join_condition join_condition_list  */
#line 593 "yacc_sql.y"
                                              {

     }
#line 2059 "yacc_sql.tab.c"
    break;

  case 92: /* join_condition: ID DOT ID comOp value  */
#line 599 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, right_value, NULL, NULL);
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
#line 2084 "yacc_sql.tab.c"
    break;

  case 93: /* join_condition: value comOp ID DOT ID  */
#line 620 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 1, &right_attr, NULL, NULL, NULL);
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
#line 2109 "yacc_sql.tab.c"
    break;

  case 94: /* join_condition: ID DOT ID comOp ID DOT ID  */
#line 641 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 1, &right_attr, NULL, NULL, NULL);
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
#line 2132 "yacc_sql.tab.c"
    break;

  case 95: /* join_condition: value comOp value  */
#line 660 "yacc_sql.y"
                {
    			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
    			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

    			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 0, NULL, right_value, NULL, NULL);
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
#line 2157 "yacc_sql.tab.c"
    break;

  case 96: /* join_condition: ID comOp right_sub_select  */
#line 680 "yacc_sql.y"
                                {
    	RelAttr left_attr;
    	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
    	Condition condition;
    	condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, NULL, NULL, &CONTEXT->right_sub_select);
    	CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    	}
#line 2169 "yacc_sql.tab.c"
    break;

  case 97: /* join_condition: left_sub_select comOp ID  */
#line 687 "yacc_sql.y"
                               {
    	RelAttr right_attr;
    	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
    	Condition condition;
    	condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, NULL, 1, &right_attr, NULL, &CONTEXT->left_sub_select, NULL);
    	CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
        }
#line 2181 "yacc_sql.tab.c"
    break;

  case 98: /* join_condition: ID DOT ID comOp right_sub_select  */
#line 694 "yacc_sql.y"
                                       {
        RelAttr left_attr;
        relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
        Condition condition;
        condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, NULL, NULL, &CONTEXT->right_sub_select);
        CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2193 "yacc_sql.tab.c"
    break;

  case 99: /* join_condition: left_sub_select comOp ID DOT ID  */
#line 701 "yacc_sql.y"
                                      {
        RelAttr right_attr;
        relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
        Condition condition;
        condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, NULL, 1, &right_attr, NULL, &CONTEXT->left_sub_select, NULL);
        CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2205 "yacc_sql.tab.c"
    break;

  case 100: /* join_condition: left_sub_select comOp right_sub_select  */
#line 708 "yacc_sql.y"
                                               {
        Condition condition;
        condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, NULL, 0, NULL, NULL, &CONTEXT->left_sub_select, &CONTEXT->right_sub_select);
        CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2215 "yacc_sql.tab.c"
    break;

  case 102: /* where: WHERE condition condition_list  */
#line 716 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2223 "yacc_sql.tab.c"
    break;

  case 104: /* condition_list: AND condition condition_list  */
#line 723 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2231 "yacc_sql.tab.c"
    break;

  case 105: /* condition: ID comOp value  */
#line 729 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, right_value, NULL, NULL);
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
#line 2256 "yacc_sql.tab.c"
    break;

  case 106: /* condition: value comOp value  */
#line 750 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 0, NULL, right_value, NULL, NULL);
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
#line 2280 "yacc_sql.tab.c"
    break;

  case 107: /* condition: ID comOp ID  */
#line 770 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 1, &right_attr, NULL, NULL, NULL);
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
#line 2304 "yacc_sql.tab.c"
    break;

  case 108: /* condition: value comOp ID  */
#line 790 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 1, &right_attr, NULL, NULL, NULL);
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
#line 2330 "yacc_sql.tab.c"
    break;

  case 109: /* condition: ID DOT ID comOp value  */
#line 812 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, right_value, NULL, NULL);
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
#line 2355 "yacc_sql.tab.c"
    break;

  case 110: /* condition: value comOp ID DOT ID  */
#line 833 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, left_value, 1, &right_attr, NULL, NULL, NULL);
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
#line 2380 "yacc_sql.tab.c"
    break;

  case 111: /* condition: ID DOT ID comOp ID DOT ID  */
#line 854 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 1, &right_attr, NULL, NULL, NULL);
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
#line 2403 "yacc_sql.tab.c"
    break;

  case 112: /* condition: ID comOp right_sub_select  */
#line 872 "yacc_sql.y"
                                {
	RelAttr left_attr;
	relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
	Condition condition;
	condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, NULL, NULL, &CONTEXT->right_sub_select);
	CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2415 "yacc_sql.tab.c"
    break;

  case 113: /* condition: left_sub_select comOp ID  */
#line 879 "yacc_sql.y"
                               {
	RelAttr right_attr;
	relation_attr_init(&right_attr, NULL, (yyvsp[0].string));
	Condition condition;
	condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, NULL, 1, &right_attr, NULL, &CONTEXT->left_sub_select, NULL);
	CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2427 "yacc_sql.tab.c"
    break;

  case 114: /* condition: ID DOT ID comOp right_sub_select  */
#line 886 "yacc_sql.y"
                                       {
        RelAttr left_attr;
    	relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
    	Condition condition;
    	condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 1, &left_attr, NULL, 0, NULL, NULL, NULL, &CONTEXT->right_sub_select);
    	CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2439 "yacc_sql.tab.c"
    break;

  case 115: /* condition: left_sub_select comOp ID DOT ID  */
#line 893 "yacc_sql.y"
                                      {
        RelAttr right_attr;
    	relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));
    	Condition condition;
    	condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, NULL, 1, &right_attr, NULL, &CONTEXT->left_sub_select, NULL);
    	CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2451 "yacc_sql.tab.c"
    break;

  case 116: /* condition: left_sub_select comOp right_sub_select  */
#line 900 "yacc_sql.y"
                                               {
    	Condition condition;
    	condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], 0, NULL, NULL, 0, NULL, NULL, &CONTEXT->left_sub_select, &CONTEXT->right_sub_select);
    	CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2461 "yacc_sql.tab.c"
    break;

  case 117: /* left_sub_select: LBRACE select RBRACE  */
#line 908 "yacc_sql.y"
                         {
    	CONTEXT->left_sub_select = CONTEXT->selects[CONTEXT->select_length];
    }
#line 2469 "yacc_sql.tab.c"
    break;

  case 118: /* right_sub_select: LBRACE select RBRACE  */
#line 914 "yacc_sql.y"
                         {
    	CONTEXT->right_sub_select = CONTEXT->selects[CONTEXT->select_length];
    }
#line 2477 "yacc_sql.tab.c"
    break;

  case 119: /* comOp: EQ  */
#line 920 "yacc_sql.y"
             { CONTEXT->comp[CONTEXT->select_length-1] = EQUAL_TO; }
#line 2483 "yacc_sql.tab.c"
    break;

  case 120: /* comOp: LT  */
#line 921 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = LESS_THAN; }
#line 2489 "yacc_sql.tab.c"
    break;

  case 121: /* comOp: GT  */
#line 922 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = GREAT_THAN; }
#line 2495 "yacc_sql.tab.c"
    break;

  case 122: /* comOp: LE  */
#line 923 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = LESS_EQUAL; }
#line 2501 "yacc_sql.tab.c"
    break;

  case 123: /* comOp: GE  */
#line 924 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = GREAT_EQUAL; }
#line 2507 "yacc_sql.tab.c"
    break;

  case 124: /* comOp: NE  */
#line 925 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = NOT_EQUAL; }
#line 2513 "yacc_sql.tab.c"
    break;

  case 125: /* comOp: IS_T  */
#line 926 "yacc_sql.y"
               { CONTEXT->comp[CONTEXT->select_length-1] = IS; }
#line 2519 "yacc_sql.tab.c"
    break;

  case 126: /* comOp: IS_T NOT_T  */
#line 927 "yacc_sql.y"
                     { CONTEXT->comp[CONTEXT->select_length-1] = IS_NOT; }
#line 2525 "yacc_sql.tab.c"
    break;

  case 127: /* comOp: IN  */
#line 928 "yacc_sql.y"
        { CONTEXT->comp[CONTEXT->select_length-1] = IN_OP; }
#line 2531 "yacc_sql.tab.c"
    break;

  case 128: /* comOp: NOT_T IN  */
#line 929 "yacc_sql.y"
              { CONTEXT->comp[CONTEXT->select_length-1] = NOT_IN_OP; }
#line 2537 "yacc_sql.tab.c"
    break;

  case 131: /* order_item: ID order  */
#line 938 "yacc_sql.y"
                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_order(&CONTEXT->selects[CONTEXT->select_length-1], &attr, CONTEXT->order);
	}
#line 2547 "yacc_sql.tab.c"
    break;

  case 132: /* order_item: ID DOT ID order  */
#line 943 "yacc_sql.y"
                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_order(&CONTEXT->selects[CONTEXT->select_length-1], &attr, CONTEXT->order);
	}
#line 2557 "yacc_sql.tab.c"
    break;

  case 133: /* order: %empty  */
#line 951 "yacc_sql.y"
                    {
		CONTEXT->order = 0;
	}
#line 2565 "yacc_sql.tab.c"
    break;

  case 134: /* order: ASC  */
#line 954 "yacc_sql.y"
              {
		CONTEXT->order = 0;
	}
#line 2573 "yacc_sql.tab.c"
    break;

  case 135: /* order: DESC  */
#line 957 "yacc_sql.y"
               {
		CONTEXT->order = 1;
	}
#line 2581 "yacc_sql.tab.c"
    break;

  case 140: /* group_item: ID  */
#line 973 "yacc_sql.y"
           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		selects_append_group(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 2591 "yacc_sql.tab.c"
    break;

  case 141: /* group_item: ID DOT ID  */
#line 978 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		selects_append_group(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 2601 "yacc_sql.tab.c"
    break;

  case 144: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 993 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2610 "yacc_sql.tab.c"
    break;


#line 2614 "yacc_sql.tab.c"

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

#line 998 "yacc_sql.y"

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
