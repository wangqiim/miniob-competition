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
  YYSYMBOL_ADD = 63,                       /* ADD  */
  YYSYMBOL_SUB = 64,                       /* SUB  */
  YYSYMBOL_DIV = 65,                       /* DIV  */
  YYSYMBOL_STAR = 66,                      /* STAR  */
  YYSYMBOL_NUMBER = 67,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 68,                     /* FLOAT  */
  YYSYMBOL_ID = 69,                        /* ID  */
  YYSYMBOL_PATH = 70,                      /* PATH  */
  YYSYMBOL_SSS = 71,                       /* SSS  */
  YYSYMBOL_STRING_V = 72,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 73,                  /* $accept  */
  YYSYMBOL_commands = 74,                  /* commands  */
  YYSYMBOL_command = 75,                   /* command  */
  YYSYMBOL_exit = 76,                      /* exit  */
  YYSYMBOL_help = 77,                      /* help  */
  YYSYMBOL_sync = 78,                      /* sync  */
  YYSYMBOL_begin = 79,                     /* begin  */
  YYSYMBOL_commit = 80,                    /* commit  */
  YYSYMBOL_rollback = 81,                  /* rollback  */
  YYSYMBOL_drop_table = 82,                /* drop_table  */
  YYSYMBOL_show_tables = 83,               /* show_tables  */
  YYSYMBOL_desc_table = 84,                /* desc_table  */
  YYSYMBOL_create_index = 85,              /* create_index  */
  YYSYMBOL_id_list = 86,                   /* id_list  */
  YYSYMBOL_drop_index = 87,                /* drop_index  */
  YYSYMBOL_create_table = 88,              /* create_table  */
  YYSYMBOL_attr_def_list = 89,             /* attr_def_list  */
  YYSYMBOL_attr_def = 90,                  /* attr_def  */
  YYSYMBOL_number = 91,                    /* number  */
  YYSYMBOL_type = 92,                      /* type  */
  YYSYMBOL_ID_get = 93,                    /* ID_get  */
  YYSYMBOL_insert = 94,                    /* insert  */
  YYSYMBOL_insert_exp = 95,                /* insert_exp  */
  YYSYMBOL_value_list = 96,                /* value_list  */
  YYSYMBOL_insert_pair_list = 97,          /* insert_pair_list  */
  YYSYMBOL_value = 98,                     /* value  */
  YYSYMBOL_exp = 99,                       /* exp  */
  YYSYMBOL_delete_begin = 100,             /* delete_begin  */
  YYSYMBOL_delete = 101,                   /* delete  */
  YYSYMBOL_update_begin = 102,             /* update_begin  */
  YYSYMBOL_update = 103,                   /* update  */
  YYSYMBOL_select_begin = 104,             /* select_begin  */
  YYSYMBOL_select_end = 105,               /* select_end  */
  YYSYMBOL_select_clause = 106,            /* select_clause  */
  YYSYMBOL_select = 107,                   /* select  */
  YYSYMBOL_select_attr = 108,              /* select_attr  */
  YYSYMBOL_attr_list = 109,                /* attr_list  */
  YYSYMBOL_aggre_func = 110,               /* aggre_func  */
  YYSYMBOL_aggre_type = 111,               /* aggre_type  */
  YYSYMBOL_rel_list = 112,                 /* rel_list  */
  YYSYMBOL_inner_join = 113,               /* inner_join  */
  YYSYMBOL_inner_join_list = 114,          /* inner_join_list  */
  YYSYMBOL_join_condition_list = 115,      /* join_condition_list  */
  YYSYMBOL_join_condition = 116,           /* join_condition  */
  YYSYMBOL_where = 117,                    /* where  */
  YYSYMBOL_condition_list = 118,           /* condition_list  */
  YYSYMBOL_condition = 119,                /* condition  */
  YYSYMBOL_left_sub_select = 120,          /* left_sub_select  */
  YYSYMBOL_right_sub_select = 121,         /* right_sub_select  */
  YYSYMBOL_comOp = 122,                    /* comOp  */
  YYSYMBOL_order_by = 123,                 /* order_by  */
  YYSYMBOL_order_item = 124,               /* order_item  */
  YYSYMBOL_order = 125,                    /* order  */
  YYSYMBOL_order_item_list = 126,          /* order_item_list  */
  YYSYMBOL_group_by = 127,                 /* group_by  */
  YYSYMBOL_group_item = 128,               /* group_item  */
  YYSYMBOL_group_item_list = 129,          /* group_item_list  */
  YYSYMBOL_load_data = 130                 /* load_data  */
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
#define YYLAST   297

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  136
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  269

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   189,   189,   191,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   215,   220,   225,   231,   237,   243,   249,   255,   261,
     268,   274,   282,   284,   290,   297,   306,   308,   312,   323,
     335,   342,   352,   355,   356,   357,   358,   359,   362,   371,
     389,   393,   398,   401,   403,   407,   411,   415,   420,   427,
     428,   429,   430,   431,   432,   438,   439,   444,   449,   457,
     463,   474,   480,   492,   498,   503,   509,   532,   537,   540,
     543,   545,   548,   552,   557,   567,   568,   569,   570,   571,
     574,   576,   582,   591,   593,   598,   600,   605,   610,   615,
     620,   627,   629,   634,   636,   642,   647,   652,   657,   665,
     671,   677,   678,   679,   680,   681,   682,   683,   684,   685,
     686,   689,   691,   695,   700,   708,   711,   714,   719,   721,
     724,   726,   730,   735,   742,   744,   749
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
  "BY", "ASC", "IN", "GROUP", "ADD", "SUB", "DIV", "STAR", "NUMBER",
  "FLOAT", "ID", "PATH", "SSS", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index", "id_list",
  "drop_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "ID_get", "insert", "insert_exp", "value_list",
  "insert_pair_list", "value", "exp", "delete_begin", "delete",
  "update_begin", "update", "select_begin", "select_end", "select_clause",
  "select", "select_attr", "attr_list", "aggre_func", "aggre_type",
  "rel_list", "inner_join", "inner_join_list", "join_condition_list",
  "join_condition", "where", "condition_list", "condition",
  "left_sub_select", "right_sub_select", "comOp", "order_by", "order_item",
  "order", "order_item_list", "group_by", "group_item", "group_item_list",
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327
};
#endif

#define YYPACT_NINF (-214)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -214,   196,  -214,     3,    44,  -214,   -49,    36,    45,    53,
    -214,  -214,    88,    96,   100,   102,   104,    57,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,    77,  -214,    39,  -214,    49,  -214,   108,  -214,
      50,   105,    52,    55,    56,   119,   126,  -214,    62,  -214,
    -214,  -214,  -214,  -214,    84,    73,   107,     4,  -214,  -214,
    -214,  -214,  -214,  -214,     4,  -214,  -214,  -214,   121,  -214,
    -214,   118,   122,   133,   137,  -214,   148,    98,   129,   166,
     168,  -214,  -214,   140,   109,   142,   110,    23,   -41,   -37,
      89,     4,     4,     4,     4,  -214,   124,  -214,    14,   125,
     139,   128,  -214,  -214,   173,   160,    95,   192,   150,  -214,
    -214,  -214,   118,   133,   -41,   -41,  -214,  -214,   180,   186,
      83,  -214,   194,    -9,   145,   198,     4,   213,    -4,   178,
     183,   -15,  -214,     4,  -214,  -214,   152,   187,  -214,  -214,
     125,   205,  -214,  -214,  -214,  -214,  -214,    -7,   216,   165,
     218,   123,   169,   222,  -214,  -214,  -214,  -214,  -214,  -214,
     184,   193,  -214,   106,    95,  -214,   106,    75,   180,   210,
     187,   142,   194,   245,   182,   195,  -214,   185,   232,     4,
     234,   250,  -214,  -214,  -214,    -4,   123,  -214,   183,   123,
    -214,   252,  -214,   188,  -214,   197,  -214,  -214,  -214,   238,
    -214,   240,   191,   243,   218,   244,  -214,   246,  -214,  -214,
     223,   206,   208,  -214,   264,   232,   265,  -214,   253,   266,
    -214,    95,   202,   214,  -214,  -214,  -214,  -214,     4,  -214,
     178,   235,   -15,   247,   255,   207,  -214,   218,   106,    95,
    -214,   106,   209,   202,  -214,    -8,   256,   261,   123,  -214,
     235,   123,  -214,  -214,   255,  -214,   211,  -214,  -214,   207,
    -214,   244,  -214,  -214,    16,   256,  -214,  -214,  -214
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    73,     0,     0,     0,     0,
      69,    71,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     0,     7,     0,     6,     0,     4,     0,    18,
       0,     0,     0,     0,     0,     0,     0,    23,     0,    24,
      25,    26,    22,    21,     0,     0,     0,     0,    85,    86,
      87,    88,    89,    58,     0,    77,    55,    56,    66,    57,
      65,    80,     0,    80,     0,    75,     0,     0,     0,     0,
       0,    29,    28,     0,     0,   101,     0,     0,    60,     0,
       0,     0,     0,     0,     0,    78,     0,    79,     0,     0,
       0,     0,    27,    34,     0,     0,     0,     0,     0,    64,
      68,    67,    80,    80,    59,    61,    63,    62,    90,     0,
       0,    48,    36,     0,     0,     0,     0,     0,     0,     0,
     103,     0,    70,     0,    81,    82,     0,    93,    84,    83,
       0,     0,    43,    44,    45,    46,    47,    39,     0,     0,
      51,    50,     0,     0,   111,   112,   113,   114,   115,   116,
       0,   117,   119,     0,     0,   102,     0,   101,    90,     0,
      93,   101,    36,     0,     0,     0,    41,     0,    32,     0,
       0,     0,   109,   120,   118,     0,   105,   106,   103,   107,
     108,     0,    91,     0,    94,   130,    37,    35,    42,     0,
      40,     0,     0,     0,    51,    53,   136,     0,   104,    72,
       0,     0,   121,    38,     0,    32,     0,    52,     0,     0,
     110,     0,     0,     0,    74,    31,    33,    30,     0,    49,
       0,    95,     0,   132,   134,     0,    76,    51,     0,     0,
      92,     0,     0,     0,   131,   125,   128,     0,    97,    98,
      95,    99,   100,   133,   134,   127,     0,   126,   123,     0,
     122,    53,    96,   135,   125,   128,    54,   124,   129
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,    66,  -214,  -214,   111,   144,  -214,  -214,
    -214,  -214,  -149,  -197,    21,  -214,   -36,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -124,  -214,   -68,   199,  -214,   117,
    -214,   116,    37,    51,  -148,   103,   130,  -213,  -164,  -130,
    -214,    29,    28,    30,  -214,    54,    42,  -214
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   203,    29,    30,   141,   122,   199,   147,
     123,    31,   150,   180,   219,    70,    87,    32,    33,    34,
      35,    36,   236,    37,    38,    72,    95,    73,    74,   137,
     170,   171,   240,   231,   107,   165,   130,   131,   187,   163,
     224,   246,   258,   260,   212,   234,   244,    39
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,   166,   190,   255,   153,    97,     5,   217,   232,    40,
     174,    41,    42,    57,   142,   143,   144,   145,   146,   191,
      45,    57,   256,   195,    93,    94,   232,   255,    88,   110,
     204,    57,   111,   154,   155,   156,   157,   158,   159,   160,
     247,   109,   161,    46,   134,   135,   162,   175,    47,   176,
      43,    63,   257,    44,   112,   114,   115,   116,   117,    63,
      64,   207,   120,    66,    67,    68,    57,    69,    64,    63,
     129,    66,    67,    68,   249,    69,   257,   252,    64,   237,
     119,    66,    67,    68,    48,    69,    91,    92,    93,    94,
     151,    49,    58,    59,    60,    61,    62,   167,    54,    50,
     238,   139,   241,    51,    63,    52,    57,    53,    56,   106,
      55,    75,   128,    64,    77,    65,    66,    67,    68,    76,
      69,    78,    81,   185,    79,    80,    84,   186,   129,    82,
     189,    83,    58,    59,    60,    61,    62,    90,    91,    92,
      93,    94,    85,   151,    63,    86,    91,    92,    93,    94,
      63,    89,    90,    64,    98,    96,    66,    67,    68,    64,
      69,    63,    66,    67,    68,    99,    69,   100,   101,   102,
      64,   103,   104,    66,    67,    68,   106,    69,   124,   108,
     105,    91,    92,    93,    94,   230,    91,    92,    93,    94,
     126,   127,   151,   118,   121,   132,     2,   125,   133,   136,
       3,     4,   248,   230,   138,   251,     5,     6,     7,     8,
       9,    10,    11,   140,   148,   149,    12,    13,    14,   152,
     164,   168,   169,   173,    15,    16,   154,   155,   156,   157,
     158,   159,   160,   177,   178,   161,    17,   179,   181,   162,
     182,    91,    92,    93,    94,   183,   193,   184,   197,   198,
     200,   202,   205,   206,   201,   209,   213,   210,   214,   211,
     215,   216,   221,   218,   220,   222,   223,   225,   227,   229,
     228,   233,   239,   235,   243,   259,   245,   242,   253,   261,
     264,   226,   266,   196,   172,   192,   194,   262,   265,   113,
     250,   208,   267,     0,   188,   268,   263,   254
};

static const yytype_int16 yycheck[] =
{
      36,   131,   166,    11,   128,    73,    10,   204,   221,     6,
      17,     8,     9,    17,    23,    24,    25,    26,    27,   167,
      69,    17,    30,   171,    65,    66,   239,    11,    64,    66,
     179,    17,    69,    48,    49,    50,    51,    52,    53,    54,
     237,    18,    57,     7,   112,   113,    61,    54,     3,    56,
       6,    55,    60,     9,    90,    91,    92,    93,    94,    55,
      64,   185,    98,    67,    68,    69,    17,    71,    64,    55,
     106,    67,    68,    69,   238,    71,    60,   241,    64,   228,
      66,    67,    68,    69,    31,    71,    63,    64,    65,    66,
     126,     3,    43,    44,    45,    46,    47,   133,    41,     3,
     230,    18,   232,     3,    55,     3,    17,     3,    69,    34,
      33,     3,    17,    64,     9,    66,    67,    68,    69,    69,
      71,    69,     3,    17,    69,    69,    42,   163,   164,     3,
     166,    69,    43,    44,    45,    46,    47,    19,    63,    64,
      65,    66,    69,   179,    55,    38,    63,    64,    65,    66,
      55,    30,    19,    64,    17,    33,    67,    68,    69,    64,
      71,    55,    67,    68,    69,    17,    71,    69,    39,     3,
      64,     3,    32,    67,    68,    69,    34,    71,    39,    69,
      71,    63,    64,    65,    66,   221,    63,    64,    65,    66,
      17,    31,   228,    69,    69,     3,     0,    69,    48,    19,
       4,     5,   238,   239,    18,   241,    10,    11,    12,    13,
      14,    15,    16,    19,    69,    17,    20,    21,    22,     6,
      37,    69,    35,    18,    28,    29,    48,    49,    50,    51,
      52,    53,    54,    17,    69,    57,    40,    19,    69,    61,
      18,    63,    64,    65,    66,    61,    36,    54,     3,    67,
      55,    19,    18,     3,    69,     3,    18,    69,    18,    62,
      69,    18,    39,    19,    18,    59,    58,     3,     3,     3,
      17,    69,    37,    59,    19,    19,    69,    30,    69,    18,
      69,   215,   261,   172,   140,   168,   170,   250,   259,    90,
     239,   188,   264,    -1,   164,   265,   254,   243
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    74,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    28,    29,    40,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    87,
      88,    94,   100,   101,   102,   103,   104,   106,   107,   130,
       6,     8,     9,     6,     9,    69,     7,     3,    31,     3,
       3,     3,     3,     3,    41,    33,    69,    17,    43,    44,
      45,    46,    47,    55,    64,    66,    67,    68,    69,    71,
      98,    99,   108,   110,   111,     3,    69,     9,    69,    69,
      69,     3,     3,    69,    42,    69,    38,    99,    99,    30,
      19,    63,    64,    65,    66,   109,    33,   109,    17,    17,
      69,    39,     3,     3,    32,    71,    34,   117,    69,    18,
      66,    69,    99,   110,    99,    99,    99,    99,    69,    66,
      99,    69,    90,    93,    39,    69,    17,    31,    17,    99,
     119,   120,     3,    48,   109,   109,    19,   112,    18,    18,
      19,    89,    23,    24,    25,    26,    27,    92,    69,    17,
      95,    99,     6,   107,    48,    49,    50,    51,    52,    53,
      54,    57,    61,   122,    37,   118,   122,    99,    69,    35,
     113,   114,    90,    18,    17,    54,    56,    17,    69,    19,
      96,    69,    18,    61,    54,    17,    99,   121,   119,    99,
     121,   117,   112,    36,   114,   117,    89,     3,    67,    91,
      55,    69,    19,    86,    95,    18,     3,   107,   118,     3,
      69,    62,   127,    18,    18,    69,    18,    96,    19,    97,
      18,    39,    59,    58,   123,     3,    86,     3,    17,     3,
      99,   116,   120,    69,   128,    59,   105,    95,   122,    37,
     115,   122,    30,    19,   129,    69,   124,    96,    99,   121,
     116,    99,   121,    69,   128,    11,    30,    60,   125,    19,
     126,    18,   115,   129,    69,   124,    97,   125,   126
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    85,    86,    86,    87,    88,    89,    89,    90,    90,
      90,    90,    91,    92,    92,    92,    92,    92,    93,    94,
      95,    96,    96,    97,    97,    98,    98,    98,    98,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   108,   108,
     109,   109,   109,   110,   110,   111,   111,   111,   111,   111,
     112,   112,   113,   114,   114,   115,   115,   116,   116,   116,
     116,   117,   117,   118,   118,   119,   119,   119,   119,   120,
     121,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   123,   123,   124,   124,   125,   125,   125,   126,   126,
     127,   127,   128,   128,   129,   129,   130
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    10,     0,     3,     4,     8,     0,     3,     5,     2,
       4,     3,     1,     1,     1,     1,     1,     1,     1,    10,
       1,     0,     3,     0,     6,     1,     1,     1,     1,     3,
       2,     3,     3,     3,     3,     1,     1,     3,     3,     1,
       5,     1,     8,     1,     0,     2,    10,     1,     2,     2,
       0,     3,     3,     4,     4,     1,     1,     1,     1,     1,
       0,     3,     6,     0,     2,     0,     3,     3,     3,     3,
       3,     0,     3,     0,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     0,     4,     2,     4,     0,     1,     1,     0,     3,
       0,     4,     1,     3,     0,     3,     8
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
#line 215 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1485 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 220 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1493 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 225 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1501 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 231 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1509 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 237 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1517 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 243 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1525 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 249 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1534 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 255 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1542 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 261 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1551 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID id_list RBRACE SEMICOLON  */
#line 269 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, 0, (yyvsp[-7].string), (yyvsp[-5].string));
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-3].string));
		}
#line 1561 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON  */
#line 275 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";(unique)
			create_index_init(&CONTEXT->ssql->sstr.create_index, 1, (yyvsp[-6].string), (yyvsp[-4].string));
			create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-2].string));
		}
#line 1571 "yacc_sql.tab.c"
    break;

  case 33: /* id_list: COMMA ID id_list  */
#line 284 "yacc_sql.y"
                           {
		create_index_append_attribute(&CONTEXT->ssql->sstr.create_index, (yyvsp[-1].string));
	}
#line 1579 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 291 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1588 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 298 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1600 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 308 "yacc_sql.y"
                                   {    }
#line 1606 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 313 "yacc_sql.y"
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
#line 1621 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type  */
#line 324 "yacc_sql.y"
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
#line 1637 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type NOT_T NULL_T  */
#line 336 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-2].number), 4, 0);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1648 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def: ID_get type NULLABLE_T  */
#line 343 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, 1);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1659 "yacc_sql.tab.c"
    break;

  case 42: /* number: NUMBER  */
#line 352 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1665 "yacc_sql.tab.c"
    break;

  case 43: /* type: INT_T  */
#line 355 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1671 "yacc_sql.tab.c"
    break;

  case 44: /* type: STRING_T  */
#line 356 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1677 "yacc_sql.tab.c"
    break;

  case 45: /* type: FLOAT_T  */
#line 357 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1683 "yacc_sql.tab.c"
    break;

  case 46: /* type: DATE_T  */
#line 358 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1689 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 359 "yacc_sql.y"
                    { (yyval.number)=TEXTS; }
#line 1695 "yacc_sql.tab.c"
    break;

  case 48: /* ID_get: ID  */
#line 363 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1704 "yacc_sql.tab.c"
    break;

  case 49: /* insert: INSERT INTO ID VALUES LBRACE insert_exp value_list RBRACE insert_pair_list SEMICOLON  */
#line 372 "yacc_sql.y"
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
#line 1724 "yacc_sql.tab.c"
    break;

  case 50: /* insert_exp: exp  */
#line 389 "yacc_sql.y"
            { context_value_init((yyvsp[0].ast1), &(CONTEXT->values[CONTEXT->value_length - 1])); }
#line 1730 "yacc_sql.tab.c"
    break;

  case 51: /* value_list: %empty  */
#line 393 "yacc_sql.y"
                {
		// 递增pair_num, 清零value_length
		inserts_append_values(&CONTEXT->ssql->sstr.insertion, CONTEXT->insert_pair_num++, CONTEXT->values, CONTEXT->value_length);
		CONTEXT->value_length=0;
	}
#line 1740 "yacc_sql.tab.c"
    break;

  case 55: /* value: NUMBER  */
#line 407 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
  		(yyval.value1) = &CONTEXT->values[CONTEXT->value_length - 1];
		}
#line 1749 "yacc_sql.tab.c"
    break;

  case 56: /* value: FLOAT  */
#line 411 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
  		(yyval.value1) = &CONTEXT->values[CONTEXT->value_length - 1];
		}
#line 1758 "yacc_sql.tab.c"
    break;

  case 57: /* value: SSS  */
#line 415 "yacc_sql.y"
         {
  		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
  		(yyval.value1) = &CONTEXT->values[CONTEXT->value_length - 1];
		}
#line 1768 "yacc_sql.tab.c"
    break;

  case 58: /* value: NULL_T  */
#line 420 "yacc_sql.y"
                {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
  		(yyval.value1) = &CONTEXT->values[CONTEXT->value_length - 1];
		}
#line 1777 "yacc_sql.tab.c"
    break;

  case 59: /* exp: exp ADD exp  */
#line 427 "yacc_sql.y"
                    { (yyval.ast1) = newast(ADDN, (yyvsp[-2].ast1), (yyvsp[0].ast1)); }
#line 1783 "yacc_sql.tab.c"
    break;

  case 60: /* exp: SUB exp  */
#line 428 "yacc_sql.y"
                  { (yyval.ast1) = newast(SUBN, NULL, (yyvsp[0].ast1)); }
#line 1789 "yacc_sql.tab.c"
    break;

  case 61: /* exp: exp SUB exp  */
#line 429 "yacc_sql.y"
                      { (yyval.ast1) = newast(SUBN, (yyvsp[-2].ast1), (yyvsp[0].ast1)); }
#line 1795 "yacc_sql.tab.c"
    break;

  case 62: /* exp: exp STAR exp  */
#line 430 "yacc_sql.y"
                       { (yyval.ast1) = newast(MULN, (yyvsp[-2].ast1), (yyvsp[0].ast1)); }
#line 1801 "yacc_sql.tab.c"
    break;

  case 63: /* exp: exp DIV exp  */
#line 431 "yacc_sql.y"
                      { (yyval.ast1) = newast(DIVN, (yyvsp[-2].ast1), (yyvsp[0].ast1)); }
#line 1807 "yacc_sql.tab.c"
    break;

  case 64: /* exp: LBRACE exp RBRACE  */
#line 432 "yacc_sql.y"
                            {
		ast *a = (ast *)(yyvsp[-1].ast1);
		a->l_brace++;
		a->r_brace++;
		(yyval.ast1) = (yyvsp[-1].ast1);
	}
#line 1818 "yacc_sql.tab.c"
    break;

  case 65: /* exp: value  */
#line 438 "yacc_sql.y"
                { (yyval.ast1) = newvalNode((yyvsp[0].value1)); }
#line 1824 "yacc_sql.tab.c"
    break;

  case 66: /* exp: ID  */
#line 439 "yacc_sql.y"
             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		(yyval.ast1) = newattrNode(&attr);
	}
#line 1834 "yacc_sql.tab.c"
    break;

  case 67: /* exp: ID DOT ID  */
#line 444 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		(yyval.ast1) = newattrNode(&attr);
	}
#line 1844 "yacc_sql.tab.c"
    break;

  case 68: /* exp: ID DOT STAR  */
#line 449 "yacc_sql.y"
                      {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), "*");
		(yyval.ast1) = newattrNode(&attr);
	}
#line 1854 "yacc_sql.tab.c"
    break;

  case 69: /* delete_begin: DELETE  */
#line 457 "yacc_sql.y"
           {
    	CONTEXT->select_length++;
    }
#line 1862 "yacc_sql.tab.c"
    break;

  case 70: /* delete: delete_begin FROM ID where SEMICOLON  */
#line 464 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions[0], CONTEXT->condition_length[0]);
			CONTEXT->condition_length[0] = 0;
    }
#line 1874 "yacc_sql.tab.c"
    break;

  case 71: /* update_begin: UPDATE  */
#line 474 "yacc_sql.y"
          {
   	CONTEXT->select_length++;
   }
#line 1882 "yacc_sql.tab.c"
    break;

  case 72: /* update: update_begin ID SET ID EQ exp where SEMICOLON  */
#line 481 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			context_value_init((yyvsp[-2].ast1), &CONTEXT->values[0]);
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions[0], CONTEXT->condition_length[0]);
			CONTEXT->condition_length[0] = 0;
		}
#line 1895 "yacc_sql.tab.c"
    break;

  case 73: /* select_begin: SELECT  */
#line 492 "yacc_sql.y"
           {
    	CONTEXT->select_length++;
    	clear_selects(&CONTEXT->selects[CONTEXT->select_length-1]);
    }
#line 1904 "yacc_sql.tab.c"
    break;

  case 75: /* select_clause: select SEMICOLON  */
#line 503 "yacc_sql.y"
                         {
		// 解决 shift/reduce冲突
	}
#line 1912 "yacc_sql.tab.c"
    break;

  case 76: /* select: select_begin select_attr FROM ID rel_list inner_join_list where group_by order_by select_end  */
#line 510 "yacc_sql.y"
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
#line 1936 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr: STAR  */
#line 532 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
		}
#line 1946 "yacc_sql.tab.c"
    break;

  case 78: /* select_attr: exp attr_list  */
#line 537 "yacc_sql.y"
                        {
		selects_append_attribute_expression(&CONTEXT->selects[CONTEXT->select_length-1], (yyvsp[-1].ast1));
	}
#line 1954 "yacc_sql.tab.c"
    break;

  case 81: /* attr_list: COMMA exp attr_list  */
#line 545 "yacc_sql.y"
                          {
		selects_append_attribute_expression(&CONTEXT->selects[CONTEXT->select_length-1], (yyvsp[-1].ast1));
    }
#line 1962 "yacc_sql.tab.c"
    break;

  case 83: /* aggre_func: aggre_type LBRACE exp RBRACE  */
#line 552 "yacc_sql.y"
                                     {
		Aggregate aggre;
		relation_aggre_init_with_exp(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], (yyvsp[-1].ast1));
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	  }
#line 1972 "yacc_sql.tab.c"
    break;

  case 84: /* aggre_func: aggre_type LBRACE STAR RBRACE  */
#line 557 "yacc_sql.y"
                                        {
		// TODO(wq):仅需要支持 select COUNT(*)，不需要支持select other_aggre(*) 以及select aggre_func(table_name.*);
		// 由于如果在语法解析里处理该问题的话，代码写的比较冗余丑陋，所以这里不检查sum(*)等这种不合法情况，丢给parse之后的stage去检验
		Aggregate aggre;
		relation_aggre_init(&aggre, CONTEXT->aggreType[CONTEXT->select_length-1], 1, NULL, "*", NULL);
		selects_append_aggregate(&CONTEXT->selects[CONTEXT->select_length-1], &aggre);
	}
#line 1984 "yacc_sql.tab.c"
    break;

  case 85: /* aggre_type: MAX_T  */
#line 567 "yacc_sql.y"
                { CONTEXT->aggreType[CONTEXT->select_length-1] = MAXS; }
#line 1990 "yacc_sql.tab.c"
    break;

  case 86: /* aggre_type: MIN_T  */
#line 568 "yacc_sql.y"
                { CONTEXT->aggreType[CONTEXT->select_length-1] = MINS; }
#line 1996 "yacc_sql.tab.c"
    break;

  case 87: /* aggre_type: AVG_T  */
#line 569 "yacc_sql.y"
                { CONTEXT->aggreType[CONTEXT->select_length-1] = AVGS; }
#line 2002 "yacc_sql.tab.c"
    break;

  case 88: /* aggre_type: SUM_T  */
#line 570 "yacc_sql.y"
                { CONTEXT->aggreType[CONTEXT->select_length-1] = SUMS; }
#line 2008 "yacc_sql.tab.c"
    break;

  case 89: /* aggre_type: COUNT_T  */
#line 571 "yacc_sql.y"
                  { CONTEXT->aggreType[CONTEXT->select_length-1] = COUNTS; }
#line 2014 "yacc_sql.tab.c"
    break;

  case 91: /* rel_list: COMMA ID rel_list  */
#line 576 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->selects[CONTEXT->select_length-1], (yyvsp[-1].string));
		  }
#line 2022 "yacc_sql.tab.c"
    break;

  case 92: /* inner_join: INNER JOIN ID ON join_condition join_condition_list  */
#line 582 "yacc_sql.y"
                                                        {
    	Join join;
    	join_init(&join, INNER_JOIN, (yyvsp[-3].string), CONTEXT->join_conditions[CONTEXT->select_length-1], CONTEXT->join_condition_length[CONTEXT->select_length-1]);
    	CONTEXT->joins[CONTEXT->select_length-1][CONTEXT->join_length[CONTEXT->select_length-1]++] = join;
    	// 清空变量
    	CONTEXT->join_condition_length[CONTEXT->select_length-1] = 0;
    }
#line 2034 "yacc_sql.tab.c"
    break;

  case 94: /* inner_join_list: inner_join inner_join_list  */
#line 593 "yacc_sql.y"
                                  {

    }
#line 2042 "yacc_sql.tab.c"
    break;

  case 96: /* join_condition_list: AND join_condition join_condition_list  */
#line 600 "yacc_sql.y"
                                              {

     }
#line 2050 "yacc_sql.tab.c"
    break;

  case 97: /* join_condition: exp comOp exp  */
#line 605 "yacc_sql.y"
                  {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], (yyvsp[-2].ast1), (yyvsp[0].ast1), NULL, NULL);
		CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->join_condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2060 "yacc_sql.tab.c"
    break;

  case 98: /* join_condition: exp comOp right_sub_select  */
#line 610 "yacc_sql.y"
                                 {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], (yyvsp[-2].ast1), NULL, NULL, &CONTEXT->right_sub_select);
    	CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    	}
#line 2070 "yacc_sql.tab.c"
    break;

  case 99: /* join_condition: left_sub_select comOp exp  */
#line 615 "yacc_sql.y"
                                {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], NULL, (yyvsp[0].ast1), &CONTEXT->left_sub_select, NULL);
    	CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
        }
#line 2080 "yacc_sql.tab.c"
    break;

  case 100: /* join_condition: left_sub_select comOp right_sub_select  */
#line 620 "yacc_sql.y"
                                              {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], NULL, NULL,  &CONTEXT->left_sub_select, &CONTEXT->right_sub_select);
    	CONTEXT->join_conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2090 "yacc_sql.tab.c"
    break;

  case 102: /* where: WHERE condition condition_list  */
#line 629 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2098 "yacc_sql.tab.c"
    break;

  case 104: /* condition_list: AND condition condition_list  */
#line 636 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2106 "yacc_sql.tab.c"
    break;

  case 105: /* condition: exp comOp exp  */
#line 642 "yacc_sql.y"
                  {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], (yyvsp[-2].ast1), (yyvsp[0].ast1), NULL, NULL);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
	}
#line 2116 "yacc_sql.tab.c"
    break;

  case 106: /* condition: exp comOp right_sub_select  */
#line 647 "yacc_sql.y"
                                 {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], (yyvsp[-2].ast1), NULL, NULL, &CONTEXT->right_sub_select);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2126 "yacc_sql.tab.c"
    break;

  case 107: /* condition: left_sub_select comOp exp  */
#line 652 "yacc_sql.y"
                                {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], NULL, (yyvsp[0].ast1), &CONTEXT->left_sub_select, NULL);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2136 "yacc_sql.tab.c"
    break;

  case 108: /* condition: left_sub_select comOp right_sub_select  */
#line 657 "yacc_sql.y"
                                             {
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->select_length-1], NULL, NULL, &CONTEXT->left_sub_select, &CONTEXT->right_sub_select);
		CONTEXT->conditions[CONTEXT->select_length-1][CONTEXT->condition_length[CONTEXT->select_length-1]++] = condition;
    }
#line 2146 "yacc_sql.tab.c"
    break;

  case 109: /* left_sub_select: LBRACE select RBRACE  */
#line 665 "yacc_sql.y"
                         {
    	CONTEXT->left_sub_select = CONTEXT->selects[CONTEXT->select_length];
    }
#line 2154 "yacc_sql.tab.c"
    break;

  case 110: /* right_sub_select: LBRACE select RBRACE  */
#line 671 "yacc_sql.y"
                         {
    	CONTEXT->right_sub_select = CONTEXT->selects[CONTEXT->select_length];
    }
#line 2162 "yacc_sql.tab.c"
    break;

  case 111: /* comOp: EQ  */
#line 677 "yacc_sql.y"
             { CONTEXT->comp[CONTEXT->select_length-1] = EQUAL_TO; }
#line 2168 "yacc_sql.tab.c"
    break;

  case 112: /* comOp: LT  */
#line 678 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = LESS_THAN; }
#line 2174 "yacc_sql.tab.c"
    break;

  case 113: /* comOp: GT  */
#line 679 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = GREAT_THAN; }
#line 2180 "yacc_sql.tab.c"
    break;

  case 114: /* comOp: LE  */
#line 680 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = LESS_EQUAL; }
#line 2186 "yacc_sql.tab.c"
    break;

  case 115: /* comOp: GE  */
#line 681 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = GREAT_EQUAL; }
#line 2192 "yacc_sql.tab.c"
    break;

  case 116: /* comOp: NE  */
#line 682 "yacc_sql.y"
         { CONTEXT->comp[CONTEXT->select_length-1] = NOT_EQUAL; }
#line 2198 "yacc_sql.tab.c"
    break;

  case 117: /* comOp: IS_T  */
#line 683 "yacc_sql.y"
               { CONTEXT->comp[CONTEXT->select_length-1] = IS; }
#line 2204 "yacc_sql.tab.c"
    break;

  case 118: /* comOp: IS_T NOT_T  */
#line 684 "yacc_sql.y"
                     { CONTEXT->comp[CONTEXT->select_length-1] = IS_NOT; }
#line 2210 "yacc_sql.tab.c"
    break;

  case 119: /* comOp: IN  */
#line 685 "yacc_sql.y"
        { CONTEXT->comp[CONTEXT->select_length-1] = IN_OP; }
#line 2216 "yacc_sql.tab.c"
    break;

  case 120: /* comOp: NOT_T IN  */
#line 686 "yacc_sql.y"
              { CONTEXT->comp[CONTEXT->select_length-1] = NOT_IN_OP; }
#line 2222 "yacc_sql.tab.c"
    break;

  case 123: /* order_item: ID order  */
#line 695 "yacc_sql.y"
                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_order(&CONTEXT->selects[CONTEXT->select_length-1], &attr, CONTEXT->order);
	}
#line 2232 "yacc_sql.tab.c"
    break;

  case 124: /* order_item: ID DOT ID order  */
#line 700 "yacc_sql.y"
                          {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_order(&CONTEXT->selects[CONTEXT->select_length-1], &attr, CONTEXT->order);
	}
#line 2242 "yacc_sql.tab.c"
    break;

  case 125: /* order: %empty  */
#line 708 "yacc_sql.y"
                    {
		CONTEXT->order = 0;
	}
#line 2250 "yacc_sql.tab.c"
    break;

  case 126: /* order: ASC  */
#line 711 "yacc_sql.y"
              {
		CONTEXT->order = 0;
	}
#line 2258 "yacc_sql.tab.c"
    break;

  case 127: /* order: DESC  */
#line 714 "yacc_sql.y"
               {
		CONTEXT->order = 1;
	}
#line 2266 "yacc_sql.tab.c"
    break;

  case 132: /* group_item: ID  */
#line 730 "yacc_sql.y"
           {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		selects_append_group(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 2276 "yacc_sql.tab.c"
    break;

  case 133: /* group_item: ID DOT ID  */
#line 735 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-2].string), (yyvsp[0].string));
		selects_append_group(&CONTEXT->selects[CONTEXT->select_length-1], &attr);
	}
#line 2286 "yacc_sql.tab.c"
    break;

  case 136: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 750 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2295 "yacc_sql.tab.c"
    break;


#line 2299 "yacc_sql.tab.c"

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

#line 755 "yacc_sql.y"

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
