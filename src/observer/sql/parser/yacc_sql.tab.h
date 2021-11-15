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
    IN = 316,                      /* IN  */
    GROUP = 317,                   /* GROUP  */
    NUMBER = 318,                  /* NUMBER  */
    FLOAT = 319,                   /* FLOAT  */
    ID = 320,                      /* ID  */
    PATH = 321,                    /* PATH  */
    SSS = 322,                     /* SSS  */
    STAR = 323,                    /* STAR  */
    STRING_V = 324                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define SEMICOLON 258
#define CREATE 259
#define DROP 260
#define TABLE 261
#define TABLES 262
#define UNIQUE 263
#define INDEX 264
#define SELECT 265
#define DESC 266
#define SHOW 267
#define SYNC 268
#define INSERT 269
#define DELETE 270
#define UPDATE 271
#define LBRACE 272
#define RBRACE 273
#define COMMA 274
#define TRX_BEGIN 275
#define TRX_COMMIT 276
#define TRX_ROLLBACK 277
#define INT_T 278
#define STRING_T 279
#define FLOAT_T 280
#define DATE_T 281
#define TEXT_T 282
#define HELP 283
#define EXIT 284
#define DOT 285
#define INTO 286
#define VALUES 287
#define FROM 288
#define WHERE 289
#define INNER 290
#define JOIN 291
#define AND 292
#define SET 293
#define ON 294
#define LOAD 295
#define DATA 296
#define INFILE 297
#define MAX_T 298
#define MIN_T 299
#define AVG_T 300
#define SUM_T 301
#define COUNT_T 302
#define EQ 303
#define LT 304
#define GT 305
#define LE 306
#define GE 307
#define NE 308
#define NOT_T 309
#define NULL_T 310
#define NULLABLE_T 311
#define IS_T 312
#define ORDER 313
#define BY 314
#define ASC 315
#define IN 316
#define GROUP 317
#define NUMBER 318
#define FLOAT 319
#define ID 320
#define PATH 321
#define SSS 322
#define STAR 323
#define STRING_V 324

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 152 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

#line 214 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
