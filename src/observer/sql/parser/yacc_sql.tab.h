/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
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
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    UNIQUE = 263,                  /* UNIQUE  */
    INDEX = 264,                   /* INDEX  */
    SELECT = 265,                  /* SELECT  */
    DESC = 266,                    /* DESC  */
    SHOW = 267,                    /* SHOW  */
    SYNC = 268,                    /* SYNC  */
    INSERT = 269,                  /* INSERT  */
    DELETE = 270,                  /* DELETE  */
    UPDATE = 271,                  /* UPDATE  */
    LBRACE = 272,                  /* LBRACE  */
    RBRACE = 273,                  /* RBRACE  */
    COMMA = 274,                   /* COMMA  */
    TRX_BEGIN = 275,               /* TRX_BEGIN  */
    TRX_COMMIT = 276,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 277,            /* TRX_ROLLBACK  */
    INT_T = 278,                   /* INT_T  */
    STRING_T = 279,                /* STRING_T  */
    FLOAT_T = 280,                 /* FLOAT_T  */
    DATE_T = 281,                  /* DATE_T  */
    TEXT_T = 282,                  /* TEXT_T  */
    HELP = 283,                    /* HELP  */
    EXIT = 284,                    /* EXIT  */
    DOT = 285,                     /* DOT  */
    INTO = 286,                    /* INTO  */
    VALUES = 287,                  /* VALUES  */
    FROM = 288,                    /* FROM  */
    WHERE = 289,                   /* WHERE  */
    INNER = 290,                   /* INNER  */
    JOIN = 291,                    /* JOIN  */
    AND = 292,                     /* AND  */
    SET = 293,                     /* SET  */
    ON = 294,                      /* ON  */
    LOAD = 295,                    /* LOAD  */
    DATA = 296,                    /* DATA  */
    INFILE = 297,                  /* INFILE  */
    MAX_T = 298,                   /* MAX_T  */
    MIN_T = 299,                   /* MIN_T  */
    AVG_T = 300,                   /* AVG_T  */
    SUM_T = 301,                   /* SUM_T  */
    COUNT_T = 302,                 /* COUNT_T  */
    EQ = 303,                      /* EQ  */
    LT = 304,                      /* LT  */
    GT = 305,                      /* GT  */
    LE = 306,                      /* LE  */
    GE = 307,                      /* GE  */
    NE = 308,                      /* NE  */
    NOT_T = 309,                   /* NOT_T  */
    NULL_T = 310,                  /* NULL_T  */
    NULLABLE_T = 311,              /* NULLABLE_T  */
    IS_T = 312,                    /* IS_T  */
    ORDER = 313,                   /* ORDER  */
    BY = 314,                      /* BY  */
    ASC = 315,                     /* ASC  */
    GROUP = 316,                   /* GROUP  */
    NUMBER = 317,                  /* NUMBER  */
    FLOAT = 318,                   /* FLOAT  */
    ID = 319,                      /* ID  */
    PATH = 320,                    /* PATH  */
    SSS = 321,                     /* SSS  */
    STAR = 322,                    /* STAR  */
    STRING_V = 323                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 139 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

#line 142 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
