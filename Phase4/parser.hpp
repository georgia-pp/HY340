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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
    ID = 258,                      /* ID  */
    INTEGER = 259,                 /* INTEGER  */
    FLOAT = 260,                   /* FLOAT  */
    STRINGG = 261,                 /* STRINGG  */
    IF = 262,                      /* IF  */
    ELSE = 263,                    /* ELSE  */
    WHILE = 264,                   /* WHILE  */
    FOR = 265,                     /* FOR  */
    RETURN = 266,                  /* RETURN  */
    BREAK = 267,                   /* BREAK  */
    CONTINUE = 268,                /* CONTINUE  */
    AND = 269,                     /* AND  */
    NOT = 270,                     /* NOT  */
    OR = 271,                      /* OR  */
    LOCAL = 272,                   /* LOCAL  */
    TRUE = 273,                    /* TRUE  */
    FALSE = 274,                   /* FALSE  */
    NILL = 275,                    /* NILL  */
    FUNCTION = 276,                /* FUNCTION  */
    EQUAL = 277,                   /* EQUAL  */
    ADDITION = 278,                /* ADDITION  */
    SUBTRACTION = 279,             /* SUBTRACTION  */
    MULTIPLICATION = 280,          /* MULTIPLICATION  */
    DIVISION = 281,                /* DIVISION  */
    MODE = 282,                    /* MODE  */
    ISEQUAL = 283,                 /* ISEQUAL  */
    NOTEQUAL = 284,                /* NOTEQUAL  */
    PLUSONE = 285,                 /* PLUSONE  */
    MINUSONE = 286,                /* MINUSONE  */
    MORETHAN = 287,                /* MORETHAN  */
    LESSTHAN = 288,                /* LESSTHAN  */
    MOREOREQUAL = 289,             /* MOREOREQUAL  */
    LESSOREQUAL = 290,             /* LESSOREQUAL  */
    LEFT_CURLY_BRACKET = 291,      /* LEFT_CURLY_BRACKET  */
    RIGHT_CURLY_BRACKET = 292,     /* RIGHT_CURLY_BRACKET  */
    LEFT_BRACKET = 293,            /* LEFT_BRACKET  */
    RIGHT_BRACKET = 294,           /* RIGHT_BRACKET  */
    LEFT_PARENTHESIS = 295,        /* LEFT_PARENTHESIS  */
    RIGHT_PARENTHESIS = 296,       /* RIGHT_PARENTHESIS  */
    SEMICOLON = 297,               /* SEMICOLON  */
    COMMA = 298,                   /* COMMA  */
    COLON = 299,                   /* COLON  */
    DOUBLECOLON = 300,             /* DOUBLECOLON  */
    DOT = 301,                     /* DOT  */
    DOUBLEDOT = 302                /* DOUBLEDOT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define INTEGER 259
#define FLOAT 260
#define STRINGG 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define FOR 265
#define RETURN 266
#define BREAK 267
#define CONTINUE 268
#define AND 269
#define NOT 270
#define OR 271
#define LOCAL 272
#define TRUE 273
#define FALSE 274
#define NILL 275
#define FUNCTION 276
#define EQUAL 277
#define ADDITION 278
#define SUBTRACTION 279
#define MULTIPLICATION 280
#define DIVISION 281
#define MODE 282
#define ISEQUAL 283
#define NOTEQUAL 284
#define PLUSONE 285
#define MINUSONE 286
#define MORETHAN 287
#define LESSTHAN 288
#define MOREOREQUAL 289
#define LESSOREQUAL 290
#define LEFT_CURLY_BRACKET 291
#define RIGHT_CURLY_BRACKET 292
#define LEFT_BRACKET 293
#define RIGHT_BRACKET 294
#define LEFT_PARENTHESIS 295
#define RIGHT_PARENTHESIS 296
#define SEMICOLON 297
#define COMMA 298
#define COLON 299
#define DOUBLECOLON 300
#define DOT 301
#define DOUBLEDOT 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 56 "parser.y"

    char*   stringValue;
    int     intValue;
    double  realValue;
    class   SymbolTableEntry* exprNode;
    class   expr* exprNode2;
    class   forprefix* forNode;

#line 170 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
