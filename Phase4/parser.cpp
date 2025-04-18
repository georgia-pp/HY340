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
#line 9 "parser.y"

	#include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include <cmath>
    #include "SymbolTable.h"
    #include "quad.h"
    #include "expr.h"
    #include "targetcode.h"

    using namespace std;

    extern int yylex(void);
	extern int yylineno;
	extern char * yytext;
	extern FILE * yyin;
    extern unsigned int functionLocalOffset;
    extern void generate_targetcode(void);
    extern void findConsts(); 
    extern vector<quad> quads;
    extern vector<quad*> quadptrs;


    SymbolTable* symbolTable = new SymbolTable();
    SymbolTableEntry* tmpFunct = NULL;
    int SCOPE = 0, FUNCTNUM = 0;
    unsigned int functCounter = 0;
    int functionCall = 0;
    int tableInstansiation = 0;
    vector<int> offsetStack;
    vector<unsigned int> returnLabel;
    vector <expr*> pairA, pairB;
    vector <expr*> tableitems;
    vector<int> breaklist;
    vector<int> contlist;
    bool loopActive=false;
    bool insideAFunction = 0, RETURNEXPR = 0;
    bool doubleDotEncountered = false; 
    enum Type{FUNCT, BLOCK, ZERO};
    vector<Type> vec;
    extern string error;

    int yyerror (string yaccProvidedMessage);    

#line 116 "parser.cpp"

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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_FLOAT = 5,                      /* FLOAT  */
  YYSYMBOL_STRINGG = 6,                    /* STRINGG  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_ELSE = 8,                       /* ELSE  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_FOR = 10,                       /* FOR  */
  YYSYMBOL_RETURN = 11,                    /* RETURN  */
  YYSYMBOL_BREAK = 12,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 13,                  /* CONTINUE  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_NOT = 15,                       /* NOT  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_LOCAL = 17,                     /* LOCAL  */
  YYSYMBOL_TRUE = 18,                      /* TRUE  */
  YYSYMBOL_FALSE = 19,                     /* FALSE  */
  YYSYMBOL_NILL = 20,                      /* NILL  */
  YYSYMBOL_FUNCTION = 21,                  /* FUNCTION  */
  YYSYMBOL_EQUAL = 22,                     /* EQUAL  */
  YYSYMBOL_ADDITION = 23,                  /* ADDITION  */
  YYSYMBOL_SUBTRACTION = 24,               /* SUBTRACTION  */
  YYSYMBOL_MULTIPLICATION = 25,            /* MULTIPLICATION  */
  YYSYMBOL_DIVISION = 26,                  /* DIVISION  */
  YYSYMBOL_MODE = 27,                      /* MODE  */
  YYSYMBOL_ISEQUAL = 28,                   /* ISEQUAL  */
  YYSYMBOL_NOTEQUAL = 29,                  /* NOTEQUAL  */
  YYSYMBOL_PLUSONE = 30,                   /* PLUSONE  */
  YYSYMBOL_MINUSONE = 31,                  /* MINUSONE  */
  YYSYMBOL_MORETHAN = 32,                  /* MORETHAN  */
  YYSYMBOL_LESSTHAN = 33,                  /* LESSTHAN  */
  YYSYMBOL_MOREOREQUAL = 34,               /* MOREOREQUAL  */
  YYSYMBOL_LESSOREQUAL = 35,               /* LESSOREQUAL  */
  YYSYMBOL_LEFT_CURLY_BRACKET = 36,        /* LEFT_CURLY_BRACKET  */
  YYSYMBOL_RIGHT_CURLY_BRACKET = 37,       /* RIGHT_CURLY_BRACKET  */
  YYSYMBOL_LEFT_BRACKET = 38,              /* LEFT_BRACKET  */
  YYSYMBOL_RIGHT_BRACKET = 39,             /* RIGHT_BRACKET  */
  YYSYMBOL_LEFT_PARENTHESIS = 40,          /* LEFT_PARENTHESIS  */
  YYSYMBOL_RIGHT_PARENTHESIS = 41,         /* RIGHT_PARENTHESIS  */
  YYSYMBOL_SEMICOLON = 42,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 43,                     /* COMMA  */
  YYSYMBOL_COLON = 44,                     /* COLON  */
  YYSYMBOL_DOUBLECOLON = 45,               /* DOUBLECOLON  */
  YYSYMBOL_DOT = 46,                       /* DOT  */
  YYSYMBOL_DOUBLEDOT = 47,                 /* DOUBLEDOT  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_program = 49,                   /* program  */
  YYSYMBOL_stmts = 50,                     /* stmts  */
  YYSYMBOL_stmt = 51,                      /* stmt  */
  YYSYMBOL_expr = 52,                      /* expr  */
  YYSYMBOL_53_1 = 53,                      /* $@1  */
  YYSYMBOL_54_2 = 54,                      /* $@2  */
  YYSYMBOL_55_3 = 55,                      /* $@3  */
  YYSYMBOL_56_4 = 56,                      /* $@4  */
  YYSYMBOL_M = 57,                         /* M  */
  YYSYMBOL_N = 58,                         /* N  */
  YYSYMBOL_term = 59,                      /* term  */
  YYSYMBOL_60_5 = 60,                      /* $@5  */
  YYSYMBOL_61_6 = 61,                      /* $@6  */
  YYSYMBOL_assignexpr = 62,                /* assignexpr  */
  YYSYMBOL_63_7 = 63,                      /* $@7  */
  YYSYMBOL_primary = 64,                   /* primary  */
  YYSYMBOL_lvalue = 65,                    /* lvalue  */
  YYSYMBOL_tableitem = 66,                 /* tableitem  */
  YYSYMBOL_67_8 = 67,                      /* $@8  */
  YYSYMBOL_tablemake = 68,                 /* tablemake  */
  YYSYMBOL_69_9 = 69,                      /* $@9  */
  YYSYMBOL_member = 70,                    /* member  */
  YYSYMBOL_71_10 = 71,                     /* $@10  */
  YYSYMBOL_call = 72,                      /* call  */
  YYSYMBOL_73_11 = 73,                     /* $@11  */
  YYSYMBOL_74_12 = 74,                     /* $@12  */
  YYSYMBOL_75_13 = 75,                     /* $@13  */
  YYSYMBOL_76_14 = 76,                     /* $@14  */
  YYSYMBOL_callsuffix = 77,                /* callsuffix  */
  YYSYMBOL_normcall = 78,                  /* normcall  */
  YYSYMBOL_79_15 = 79,                     /* $@15  */
  YYSYMBOL_methodcall = 80,                /* methodcall  */
  YYSYMBOL_81_16 = 81,                     /* $@16  */
  YYSYMBOL_elist = 82,                     /* elist  */
  YYSYMBOL_83_17 = 83,                     /* $@17  */
  YYSYMBOL_exprs = 84,                     /* exprs  */
  YYSYMBOL_85_18 = 85,                     /* $@18  */
  YYSYMBOL_objectdef = 86,                 /* objectdef  */
  YYSYMBOL_indexed = 87,                   /* indexed  */
  YYSYMBOL_indexedelems = 88,              /* indexedelems  */
  YYSYMBOL_indexedelem = 89,               /* indexedelem  */
  YYSYMBOL_90_19 = 90,                     /* $@19  */
  YYSYMBOL_91_20 = 91,                     /* $@20  */
  YYSYMBOL_block = 92,                     /* block  */
  YYSYMBOL_93_21 = 93,                     /* $@21  */
  YYSYMBOL_funcdef = 94,                   /* funcdef  */
  YYSYMBOL_funcprefix = 95,                /* funcprefix  */
  YYSYMBOL_funcargs = 96,                  /* funcargs  */
  YYSYMBOL_97_22 = 97,                     /* $@22  */
  YYSYMBOL_funcbody = 98,                  /* funcbody  */
  YYSYMBOL_funcname = 99,                  /* funcname  */
  YYSYMBOL_const = 100,                    /* const  */
  YYSYMBOL_idlist = 101,                   /* idlist  */
  YYSYMBOL_102_23 = 102,                   /* $@23  */
  YYSYMBOL_ids = 103,                      /* ids  */
  YYSYMBOL_104_24 = 104,                   /* $@24  */
  YYSYMBOL_ifstmt = 105,                   /* ifstmt  */
  YYSYMBOL_ifprefix = 106,                 /* ifprefix  */
  YYSYMBOL_107_25 = 107,                   /* $@25  */
  YYSYMBOL_elseprefix = 108,               /* elseprefix  */
  YYSYMBOL_whilestmt = 109,                /* whilestmt  */
  YYSYMBOL_whilestart = 110,               /* whilestart  */
  YYSYMBOL_whilecond = 111,                /* whilecond  */
  YYSYMBOL_112_26 = 112,                   /* $@26  */
  YYSYMBOL_forstmt = 113,                  /* forstmt  */
  YYSYMBOL_114_27 = 114,                   /* $@27  */
  YYSYMBOL_forprefix = 115,                /* forprefix  */
  YYSYMBOL_116_28 = 116,                   /* $@28  */
  YYSYMBOL_117_29 = 117,                   /* $@29  */
  YYSYMBOL_returnstmt = 118,               /* returnstmt  */
  YYSYMBOL_119_30 = 119,                   /* $@30  */
  YYSYMBOL_120_31 = 120                    /* $@31  */
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
#define YYFINAL  72
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   302

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  131
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  219

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   302


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
      45,    46,    47
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   153,   153,   156,   157,   160,   168,   169,   170,   171,
     172,   179,   186,   187,   188,   191,   194,   213,   232,   250,
     268,   286,   297,   316,   336,   347,   347,   371,   371,   386,
     386,   408,   408,   428,   431,   433,   435,   439,   454,   467,
     486,   486,   506,   525,   525,   545,   548,   548,   571,   572,
     573,   574,   578,   581,   609,   632,   643,   644,   647,   651,
     651,   660,   660,   683,   696,   699,   699,   707,   707,   707,
     719,   719,   741,   741,   757,   758,   761,   761,   766,   766,
     771,   771,   775,   778,   778,   782,   785,   788,   791,   792,
     795,   795,   795,   801,   801,   823,   841,   857,   857,   870,
     884,   885,   887,   891,   895,   899,   903,   907,   912,   912,
     913,   916,   916,   917,   920,   926,   933,   933,   940,   946,
     965,   971,   971,   980,   980,  1002,  1002,  1002,  1015,  1015,
    1015,  1022
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INTEGER",
  "FLOAT", "STRINGG", "IF", "ELSE", "WHILE", "FOR", "RETURN", "BREAK",
  "CONTINUE", "AND", "NOT", "OR", "LOCAL", "TRUE", "FALSE", "NILL",
  "FUNCTION", "EQUAL", "ADDITION", "SUBTRACTION", "MULTIPLICATION",
  "DIVISION", "MODE", "ISEQUAL", "NOTEQUAL", "PLUSONE", "MINUSONE",
  "MORETHAN", "LESSTHAN", "MOREOREQUAL", "LESSOREQUAL",
  "LEFT_CURLY_BRACKET", "RIGHT_CURLY_BRACKET", "LEFT_BRACKET",
  "RIGHT_BRACKET", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "SEMICOLON",
  "COMMA", "COLON", "DOUBLECOLON", "DOT", "DOUBLEDOT", "$accept",
  "program", "stmts", "stmt", "expr", "$@1", "$@2", "$@3", "$@4", "M", "N",
  "term", "$@5", "$@6", "assignexpr", "$@7", "primary", "lvalue",
  "tableitem", "$@8", "tablemake", "$@9", "member", "$@10", "call", "$@11",
  "$@12", "$@13", "$@14", "callsuffix", "normcall", "$@15", "methodcall",
  "$@16", "elist", "$@17", "exprs", "$@18", "objectdef", "indexed",
  "indexedelems", "indexedelem", "$@19", "$@20", "block", "$@21",
  "funcdef", "funcprefix", "funcargs", "$@22", "funcbody", "funcname",
  "const", "idlist", "$@23", "ids", "$@24", "ifstmt", "ifprefix", "$@25",
  "elseprefix", "whilestmt", "whilestart", "whilecond", "$@26", "forstmt",
  "$@27", "forprefix", "$@28", "$@29", "returnstmt", "$@30", "$@31", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-180)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     186,  -180,  -180,  -180,  -180,   -35,  -180,   -23,   -24,   -22,
     -12,   215,    44,  -180,  -180,  -180,    45,   215,    12,    12,
    -180,    15,     4,  -180,    50,    60,  -180,   186,    74,  -180,
    -180,  -180,   126,  -180,  -180,  -180,    18,  -180,  -180,  -180,
      23,  -180,  -180,   186,  -180,    30,  -180,  -180,  -180,   215,
    -180,  -180,   215,  -180,  -180,  -180,  -180,  -180,  -180,    59,
      55,    -1,   -34,    -1,   186,   215,   215,    32,    36,   101,
      39,  -180,  -180,  -180,  -180,  -180,   215,   215,   215,   215,
     215,  -180,  -180,   215,   215,   215,   215,  -180,   215,    79,
      57,    61,    69,    -4,   215,    92,    56,  -180,    78,    97,
     215,   186,  -180,   238,   215,   238,    77,    73,   238,   238,
      80,  -180,    15,  -180,  -180,    81,  -180,  -180,    59,    59,
    -180,  -180,  -180,   215,   215,   224,   224,   224,   224,   238,
    -180,  -180,  -180,   215,  -180,   117,  -180,  -180,  -180,   238,
    -180,  -180,   120,  -180,  -180,  -180,   186,   238,  -180,   215,
      90,    95,    98,    81,  -180,    88,    96,  -180,    36,  -180,
     215,   215,   152,   152,   102,   238,   215,   103,   105,   215,
    -180,   104,  -180,   106,   110,  -180,  -180,  -180,   215,   215,
    -180,  -180,   215,   267,   254,  -180,   111,  -180,  -180,   112,
     116,  -180,  -180,  -180,   215,   238,   238,   113,  -180,   215,
    -180,   143,  -180,   186,   238,   123,    96,  -180,   121,  -180,
    -180,   127,  -180,  -180,  -180,   116,  -180,  -180,  -180
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    53,   102,   103,   104,     0,   120,     0,   128,     0,
       0,     0,     0,   106,   107,   105,   101,     0,     0,     0,
      93,    61,     0,    14,     0,     0,     2,     4,     0,    33,
      15,    45,    48,    57,    86,    56,    49,    50,    12,    13,
       0,    52,     6,     0,     7,     0,     8,    35,     9,     0,
     125,   131,     0,    10,    11,    38,    54,   100,    96,    37,
       0,    39,    67,    42,     4,     0,    82,     0,    89,     0,
       0,    55,     1,     3,    29,    31,     0,     0,     0,     0,
       0,    25,    27,     0,     0,     0,     0,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97,     0,   114,
       0,     0,   123,   116,    82,   129,     0,     0,    90,    80,
       0,    63,     0,    87,    36,    51,    34,    34,    16,    17,
      18,    19,    20,     0,     0,    21,    23,    22,    24,    59,
      58,    41,    44,     0,    76,     0,    71,    74,    75,    65,
      64,    68,   110,    99,    95,   118,     0,   121,   119,    82,
       0,     0,     0,     0,    94,     0,    85,    62,    89,    72,
       0,     0,    26,    28,     0,    47,    82,     0,     0,    82,
     108,     0,   115,     0,     0,   117,    34,   130,     0,     0,
      81,    88,    82,    30,    32,    60,     0,    78,    66,     0,
     113,    98,   122,    35,     0,    91,    83,     0,    77,    82,
      69,     0,   109,     0,   126,     0,    85,    73,     0,   111,
      35,     0,    92,    84,    79,   113,   124,   127,   112
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -180,  -180,   -14,   -42,   -11,  -180,  -180,  -180,  -180,  -114,
    -179,  -180,  -180,  -180,  -180,  -180,  -180,     8,  -180,  -180,
    -180,  -180,  -180,  -180,    14,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,   -88,  -180,   -43,  -180,  -180,  -180,
       7,    58,  -180,  -180,    76,  -180,   -20,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,   -33,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    25,    26,    27,    28,   123,   124,   116,   117,   160,
     102,    29,    90,    91,    30,    92,    31,    32,    33,   164,
      34,    66,    35,   168,    36,    96,   169,    93,   182,   136,
     137,   166,   138,   199,   110,   156,   180,   206,    37,    67,
     113,    68,   155,   205,    38,    64,    39,    40,    98,   142,
     144,    58,    41,   171,   190,   202,   215,    42,    43,   150,
     146,    44,    45,   101,   173,    46,   149,    47,   104,   211,
      48,    52,   152
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      55,    99,    70,   161,    94,    49,    59,     1,     2,     3,
       4,    69,    95,    73,   203,     1,   151,    50,    51,    11,
      53,    12,    13,    14,    15,    16,    61,    63,    17,    12,
      54,   216,    62,    62,    18,    19,   134,    88,   103,   -70,
     106,   105,    21,   135,    22,    89,   -70,    56,    57,    24,
     107,    65,    60,    71,   108,   109,    94,    24,   -67,   148,
      72,   174,   194,    97,    95,   118,   119,   120,   121,   122,
     100,   111,   125,   126,   127,   128,    16,   129,   186,   112,
     115,   189,   130,   139,    78,    79,    80,   131,    74,   147,
      75,   133,   132,   109,   197,   140,   141,    76,    77,    78,
      79,    80,    81,    82,   172,   145,    83,    84,    85,    86,
     154,   208,   162,   163,    20,    74,    87,    75,   153,   157,
     167,   159,   165,   170,    76,    77,    78,    79,    80,    81,
      82,   175,   178,    83,    84,    85,    86,   176,   109,   179,
     177,   185,   114,   187,   188,   191,   209,   192,   -46,   183,
     184,   193,   198,   200,   207,   109,   -40,   -43,   109,   201,
     212,   210,   214,   213,    88,   181,   -70,   195,   196,   217,
     158,   109,    89,   -70,   143,    76,    77,    78,    79,    80,
     -71,   -71,   218,   204,    83,    84,    85,    86,   109,     1,
       2,     3,     4,     5,     0,     6,     7,     8,     9,    10,
       0,    11,     0,    12,    13,    14,    15,    16,     0,     0,
      17,     0,     0,     0,     0,     0,    18,    19,     1,     2,
       3,     4,    20,     0,    21,     0,    22,     0,    23,     0,
      11,    24,    12,    13,    14,    15,     0,     0,     0,    17,
       0,     0,     0,     0,     0,    18,    19,    76,    77,    78,
      79,    80,    74,    21,    75,    22,   -71,   -71,   -71,   -71,
      24,    76,    77,    78,    79,    80,    81,    82,    74,     0,
      83,    84,    85,    86,     0,     0,     0,    76,    77,    78,
      79,    80,    81,    82,     0,     0,    83,    84,    85,    86,
      76,    77,    78,    79,    80,    81,    82,     0,     0,    83,
      84,    85,    86
};

static const yytype_int16 yycheck[] =
{
      11,    43,    22,   117,    38,    40,    17,     3,     4,     5,
       6,    22,    46,    27,   193,     3,   104,    40,    42,    15,
      42,    17,    18,    19,    20,    21,    18,    19,    24,    17,
      42,   210,    18,    19,    30,    31,    40,    38,    49,    40,
      60,    52,    38,    47,    40,    46,    47,     3,     3,    45,
      64,    36,    40,     3,    65,    66,    38,    45,    40,   101,
       0,   149,   176,    40,    46,    76,    77,    78,    79,    80,
      40,    39,    83,    84,    85,    86,    21,    88,   166,    43,
      41,   169,     3,    94,    25,    26,    27,    30,    14,   100,
      16,    22,    31,   104,   182,     3,    40,    23,    24,    25,
      26,    27,    28,    29,   146,     8,    32,    33,    34,    35,
      37,   199,   123,   124,    36,    14,    42,    16,    41,    39,
       3,    40,   133,     3,    23,    24,    25,    26,    27,    28,
      29,    41,    44,    32,    33,    34,    35,    42,   149,    43,
      42,    39,    41,    40,    39,    41,     3,    41,    22,   160,
     161,    41,    41,    41,    41,   166,    30,    31,   169,    43,
      37,   203,    41,   206,    38,   158,    40,   178,   179,    42,
     112,   182,    46,    47,    98,    23,    24,    25,    26,    27,
      28,    29,   215,   194,    32,    33,    34,    35,   199,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    13,
      -1,    15,    -1,    17,    18,    19,    20,    21,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,     3,     4,
       5,     6,    36,    -1,    38,    -1,    40,    -1,    42,    -1,
      15,    45,    17,    18,    19,    20,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    30,    31,    23,    24,    25,
      26,    27,    14,    38,    16,    40,    32,    33,    34,    35,
      45,    23,    24,    25,    26,    27,    28,    29,    14,    -1,
      32,    33,    34,    35,    -1,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    33,    34,    35,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    12,
      13,    15,    17,    18,    19,    20,    21,    24,    30,    31,
      36,    38,    40,    42,    45,    49,    50,    51,    52,    59,
      62,    64,    65,    66,    68,    70,    72,    86,    92,    94,
      95,   100,   105,   106,   109,   110,   113,   115,   118,    40,
      40,    42,   119,    42,    42,    52,     3,     3,    99,    52,
      40,    65,    72,    65,    93,    36,    69,    87,    89,    52,
      94,     3,     0,    50,    14,    16,    23,    24,    25,    26,
      27,    28,    29,    32,    33,    34,    35,    42,    38,    46,
      60,    61,    63,    75,    38,    46,    73,    40,    96,    51,
      40,   111,    58,    52,   116,    52,    94,    50,    52,    52,
      82,    39,    43,    88,    41,    41,    55,    56,    52,    52,
      52,    52,    52,    53,    54,    52,    52,    52,    52,    52,
       3,    30,    31,    22,    40,    47,    77,    78,    80,    52,
       3,    40,    97,    92,    98,     8,   108,    52,    51,   114,
     107,    82,   120,    41,    37,    90,    83,    39,    89,    40,
      57,    57,    52,    52,    67,    52,    79,     3,    71,    74,
       3,   101,    51,   112,    82,    41,    42,    42,    44,    43,
      84,    88,    76,    52,    52,    39,    82,    40,    39,    82,
     102,    41,    41,    41,    57,    52,    52,    82,    41,    81,
      41,    43,   103,    58,    52,    91,    85,    41,    82,     3,
      51,   117,    37,    84,    41,   104,    58,    42,   103
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    52,    54,    52,    55,
      52,    56,    52,    52,    57,    58,    59,    59,    59,    59,
      60,    59,    59,    61,    59,    59,    63,    62,    64,    64,
      64,    64,    64,    65,    65,    65,    65,    65,    66,    67,
      66,    69,    68,    68,    70,    71,    70,    73,    74,    72,
      75,    72,    76,    72,    77,    77,    79,    78,    81,    80,
      83,    82,    82,    85,    84,    84,    86,    87,    88,    88,
      90,    91,    89,    93,    92,    94,    95,    97,    96,    98,
      99,    99,   100,   100,   100,   100,   100,   100,   102,   101,
     101,   104,   103,   103,   105,   105,   107,   106,   108,   109,
     110,   112,   111,   114,   113,   116,   117,   115,   119,   120,
     118,   118
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     0,     4,     0,
       5,     0,     5,     1,     0,     0,     3,     2,     2,     2,
       0,     3,     2,     0,     3,     1,     0,     4,     1,     1,
       1,     3,     1,     1,     2,     2,     1,     1,     3,     0,
       5,     0,     4,     3,     3,     0,     5,     0,     0,     6,
       0,     3,     0,     7,     1,     1,     0,     4,     0,     6,
       0,     3,     0,     0,     4,     0,     1,     2,     3,     0,
       0,     0,     7,     0,     4,     3,     2,     0,     4,     1,
       1,     0,     1,     1,     1,     1,     1,     1,     0,     3,
       0,     0,     4,     0,     2,     4,     0,     5,     1,     3,
       1,     0,     4,     0,     8,     0,     0,     9,     0,     0,
       5,     2
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
  case 2: /* program: stmts  */
#line 153 "parser.y"
                  {}
#line 1407 "parser.cpp"
    break;

  case 3: /* stmts: stmt stmts  */
#line 156 "parser.y"
                                       {}
#line 1413 "parser.cpp"
    break;

  case 4: /* stmts: %empty  */
#line 157 "parser.y"
                    {}
#line 1419 "parser.cpp"
    break;

  case 5: /* stmt: expr SEMICOLON  */
#line 160 "parser.y"
                             {
            if ((yyvsp[-1].exprNode2)->type == boolexpr_e && !(yyvsp[-1].exprNode2)->evaluated) {
                //$1->sym = newtemp();
                shortCircuitEval((yyvsp[-1].exprNode2));
                   
            }
            resettemp();
        }
#line 1432 "parser.cpp"
    break;

  case 6: /* stmt: ifstmt  */
#line 168 "parser.y"
                             {}
#line 1438 "parser.cpp"
    break;

  case 7: /* stmt: whilestmt  */
#line 169 "parser.y"
                             {}
#line 1444 "parser.cpp"
    break;

  case 8: /* stmt: forstmt  */
#line 170 "parser.y"
                             {}
#line 1450 "parser.cpp"
    break;

  case 9: /* stmt: returnstmt  */
#line 171 "parser.y"
                             {}
#line 1456 "parser.cpp"
    break;

  case 10: /* stmt: BREAK SEMICOLON  */
#line 172 "parser.y"
                             {
            if(!loopActive) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": break statement only allowed inside loops");
            else {  
                breaklist.push_back(nextquad()+1);
                emit(jump,NULL,NULL,NULL,0,yylineno);
            }
        }
#line 1468 "parser.cpp"
    break;

  case 11: /* stmt: CONTINUE SEMICOLON  */
#line 179 "parser.y"
                             {
            if(!loopActive) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": continue statement only allowed inside loops");
            else{   
                contlist.push_back(nextquad()+1);
                emit(jump,NULL,NULL,NULL,0,yylineno);
            }
        }
#line 1480 "parser.cpp"
    break;

  case 12: /* stmt: block  */
#line 186 "parser.y"
                             {}
#line 1486 "parser.cpp"
    break;

  case 13: /* stmt: funcdef  */
#line 187 "parser.y"
                             {}
#line 1492 "parser.cpp"
    break;

  case 14: /* stmt: SEMICOLON  */
#line 188 "parser.y"
                             {}
#line 1498 "parser.cpp"
    break;

  case 15: /* expr: assignexpr  */
#line 191 "parser.y"
                   {
            (yyval.exprNode2) = (yyvsp[0].exprNode2);
        }
#line 1506 "parser.cpp"
    break;

  case 16: /* expr: expr ADDITION expr  */
#line 194 "parser.y"
                             {
            
            if( !checkarithmetic_type((yyvsp[-2].exprNode2),(yyvsp[0].exprNode2)) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                if ((yyvsp[-2].exprNode2)->type == constnum_e && (yyvsp[0].exprNode2)->type == constnum_e) {
                    (yyval.exprNode2) = newexpr(constnum_e);
                    (yyval.exprNode2)->numConst = (yyvsp[-2].exprNode2)->numConst + (yyvsp[0].exprNode2)->numConst;
                } else {
                    (yyval.exprNode2) = newexpr(arithexpr_e);
                }
                if (istempexpr((yyvsp[-2].exprNode2))) { /*this if was inside the else above and therefore if $1=constnum && $3==constnum then there wound be an assignement to $$->sym and when print goes to print it segmentation fault happens*/
                    (yyval.exprNode2)->sym = (yyvsp[-2].exprNode2)->sym;
                } else if (istempexpr((yyvsp[0].exprNode2))) {
                    (yyval.exprNode2)->sym = (yyvsp[0].exprNode2)->sym;
                } else {
                    (yyval.exprNode2)->sym = newtemp();
                }

                emit(add, (yyvsp[-2].exprNode2), (yyvsp[0].exprNode2), (yyval.exprNode2), 0, yylineno);
        }
#line 1530 "parser.cpp"
    break;

  case 17: /* expr: expr SUBTRACTION expr  */
#line 213 "parser.y"
                                {
            
            if( !checkarithmetic_type((yyvsp[-2].exprNode2),(yyvsp[0].exprNode2)) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                if ((yyvsp[-2].exprNode2)->type == constnum_e && (yyvsp[0].exprNode2)->type == constnum_e) {
                    (yyval.exprNode2) = newexpr(constnum_e);
                    (yyval.exprNode2)->numConst = (yyvsp[-2].exprNode2)->numConst - (yyvsp[0].exprNode2)->numConst;
                } else {
                    (yyval.exprNode2) = newexpr(arithexpr_e);
                }
                if (istempexpr((yyvsp[-2].exprNode2))) { 
                    (yyval.exprNode2)->sym = (yyvsp[-2].exprNode2)->sym;
                } else if (istempexpr((yyvsp[0].exprNode2))) {
                    (yyval.exprNode2)->sym = (yyvsp[0].exprNode2)->sym;
                } else {
                    (yyval.exprNode2)->sym = newtemp();
                }
                emit(sub, (yyvsp[-2].exprNode2), (yyvsp[0].exprNode2), (yyval.exprNode2), 0, yylineno);
          
        }
#line 1554 "parser.cpp"
    break;

  case 18: /* expr: expr MULTIPLICATION expr  */
#line 232 "parser.y"
                                   {

            if( !checkarithmetic_type((yyvsp[-2].exprNode2),(yyvsp[0].exprNode2)) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                if ((yyvsp[-2].exprNode2)->type == constnum_e && (yyvsp[0].exprNode2)->type == constnum_e) {
                    (yyval.exprNode2) = newexpr(constnum_e);
                    (yyval.exprNode2)->numConst = (yyvsp[-2].exprNode2)->numConst * (yyvsp[0].exprNode2)->numConst;
                } else {
                    (yyval.exprNode2) = newexpr(arithexpr_e);
                }
                if (istempexpr((yyvsp[-2].exprNode2))) {
                    (yyval.exprNode2)->sym = (yyvsp[-2].exprNode2)->sym;
                } else if (istempexpr((yyvsp[0].exprNode2))) {
                    (yyval.exprNode2)->sym = (yyvsp[0].exprNode2)->sym;
                } else {
                    (yyval.exprNode2)->sym = newtemp();
                }
                emit(mul, (yyvsp[-2].exprNode2), (yyvsp[0].exprNode2), (yyval.exprNode2), 0, yylineno);
        }
#line 1577 "parser.cpp"
    break;

  case 19: /* expr: expr DIVISION expr  */
#line 250 "parser.y"
                             {

            if( !checkarithmetic_type((yyvsp[-2].exprNode2),(yyvsp[0].exprNode2)) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                if ((yyvsp[-2].exprNode2)->type == constnum_e && (yyvsp[0].exprNode2)->type == constnum_e) {
                    (yyval.exprNode2) = newexpr(constnum_e);
                    (yyval.exprNode2)->numConst = (yyvsp[-2].exprNode2)->numConst / (yyvsp[0].exprNode2)->numConst;
                } else {
                    (yyval.exprNode2) = newexpr(arithexpr_e);
                }
                if (istempexpr((yyvsp[-2].exprNode2))) {
                    (yyval.exprNode2)->sym = (yyvsp[-2].exprNode2)->sym;
                } else if (istempexpr((yyvsp[0].exprNode2))) {
                    (yyval.exprNode2)->sym = (yyvsp[0].exprNode2)->sym;
                } else {
                    (yyval.exprNode2)->sym = newtemp();
                }
                emit(division, (yyvsp[-2].exprNode2), (yyvsp[0].exprNode2), (yyval.exprNode2), 0, yylineno);  
        }
#line 1600 "parser.cpp"
    break;

  case 20: /* expr: expr MODE expr  */
#line 268 "parser.y"
                         {
            
            if( !checkarithmetic_type((yyvsp[-2].exprNode2),(yyvsp[0].exprNode2)) ) symbolTable->errors.push_back("RUNTIME RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                if ((yyvsp[-2].exprNode2)->type == constnum_e && (yyvsp[0].exprNode2)->type == constnum_e) {
                    (yyval.exprNode2) = newexpr(constnum_e);
                    (yyval.exprNode2)->numConst = fmod((yyvsp[-2].exprNode2)->numConst ,(yyvsp[0].exprNode2)->numConst);
                } else {
                    (yyval.exprNode2) = newexpr(arithexpr_e);
                }
                if (istempexpr((yyvsp[-2].exprNode2))) {
                    (yyval.exprNode2)->sym = (yyvsp[-2].exprNode2)->sym;
                } else if (istempexpr((yyvsp[0].exprNode2))) {
                    (yyval.exprNode2)->sym = (yyvsp[0].exprNode2)->sym;
                } else {
                    (yyval.exprNode2)->sym = newtemp();
                }
                emit(mod, (yyvsp[-2].exprNode2), (yyvsp[0].exprNode2), (yyval.exprNode2), 0, yylineno);
        }
#line 1623 "parser.cpp"
    break;

  case 21: /* expr: expr MORETHAN expr  */
#line 286 "parser.y"
                             {
            
            if( !checkarithmetic_type((yyvsp[-2].exprNode2),(yyvsp[0].exprNode2)) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                (yyval.exprNode2) = newexpr(boolexpr_e);
                //$$->sym = newtemp();
               
                (yyval.exprNode2)->truelist = nextquad()+1;//because nextquad() returns the position in the vector that the nextwuad is going to be in
                (yyval.exprNode2)->falselist = nextquad()+2;
                emit(if_greater, (yyvsp[-2].exprNode2), (yyvsp[0].exprNode2), NULL, 0, yylineno);
                emit(jump, NULL, NULL, NULL, 0, yylineno);
        }
#line 1639 "parser.cpp"
    break;

  case 22: /* expr: expr MOREOREQUAL expr  */
#line 297 "parser.y"
                                {

             if( !checkarithmetic_type((yyvsp[-2].exprNode2),(yyvsp[0].exprNode2)) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                (yyval.exprNode2) = newexpr(boolexpr_e);
                
                /*if (istempexpr($1)) {
                    $$->sym = $1->sym;
                } else if (istempexpr($3)) {
                    $$->sym = $3->sym;
                } else {
                    $$->sym = newtemp();
                    cout <<"LINE 280: "<<$$->sym->name<<endl;
                }*/
                
                (yyval.exprNode2)->truelist = nextquad()+1;//because nextquad() returns the position in the vector that the nextwuad is going to be in
                (yyval.exprNode2)->falselist = nextquad()+2;
                emit(if_greatereq, (yyvsp[-2].exprNode2), (yyvsp[0].exprNode2), NULL, 0, yylineno);
                emit(jump, NULL, NULL, NULL, 0, yylineno);
        }
#line 1663 "parser.cpp"
    break;

  case 23: /* expr: expr LESSTHAN expr  */
#line 316 "parser.y"
                             {
            
            if( !checkarithmetic_type((yyvsp[-2].exprNode2),(yyvsp[0].exprNode2)) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                (yyval.exprNode2) = newexpr(boolexpr_e);
                
                /*if (istempexpr($1)) {
                    $$->sym = $1->sym;
                } else if (istempexpr($3)) {
                    $$->sym = $3->sym;
                } else {
                    $$->sym = newtemp();
                    cout <<"LINE 300: "<<$$->sym->name<<endl;
                }*/
            
                (yyval.exprNode2)->truelist = nextquad()+1;
                (yyval.exprNode2)->falselist = nextquad()+2;
                emit(if_less, (yyvsp[-2].exprNode2), (yyvsp[0].exprNode2), NULL, 0, yylineno);
                emit(jump, NULL, NULL, NULL, 0, yylineno);
                
        }
#line 1688 "parser.cpp"
    break;

  case 24: /* expr: expr LESSOREQUAL expr  */
#line 336 "parser.y"
                                {
            
            if( !checkarithmetic_type((yyvsp[-2].exprNode2),(yyvsp[0].exprNode2)) )symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                (yyval.exprNode2) = newexpr(boolexpr_e);
                //$$->sym = newtemp();

                (yyval.exprNode2)->truelist = nextquad()+1;//because nextquad() returns the position in the vector that the nextwuad is going to be in
                (yyval.exprNode2)->falselist = nextquad()+2;
                emit(if_lesseq, (yyvsp[-2].exprNode2), (yyvsp[0].exprNode2), NULL, 0, yylineno);
                emit(jump, NULL, NULL, NULL, 0, yylineno);
        }
#line 1704 "parser.cpp"
    break;

  case 25: /* $@1: %empty  */
#line 347 "parser.y"
                       {if ((yyvsp[-1].exprNode2)->type == boolexpr_e && !(yyvsp[-1].exprNode2)->evaluated) shortCircuitEval((yyvsp[-1].exprNode2));}
#line 1710 "parser.cpp"
    break;

  case 26: /* expr: expr ISEQUAL $@1 expr  */
#line 347 "parser.y"
                                                                                                  {
            

            if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) {
                shortCircuitEval((yyvsp[0].exprNode2));
            }

            (yyval.exprNode2) = newexpr(boolexpr_e);
           
            /*  if (istempexpr($1)) {
                    $$->sym = $1->sym;
                } else if (istempexpr($4)) {
                    $$->sym = $4->sym;
                } else {
                    $$->sym = newtemp();
                    cout <<"LINE 338: "<<$$->sym->name<<endl;
                }*/
            

            (yyval.exprNode2)->truelist = nextquad()+1;//because nextquad() returns the position in the vector that the nextwuad is going to be in
            (yyval.exprNode2)->falselist = nextquad()+2;
            emit(if_eq, (yyvsp[-3].exprNode2), (yyvsp[0].exprNode2), NULL, 0, yylineno);
            emit(jump, NULL, NULL, NULL, 0, yylineno);
        }
#line 1739 "parser.cpp"
    break;

  case 27: /* $@2: %empty  */
#line 371 "parser.y"
                        {if ((yyvsp[-1].exprNode2)->type == boolexpr_e && !(yyvsp[-1].exprNode2)->evaluated) shortCircuitEval((yyvsp[-1].exprNode2));}
#line 1745 "parser.cpp"
    break;

  case 28: /* expr: expr NOTEQUAL $@2 expr  */
#line 371 "parser.y"
                                                                                                   {
            
        
            if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) {
                shortCircuitEval((yyvsp[0].exprNode2));
            }

            (yyval.exprNode2) = newexpr(boolexpr_e);
            //$$->sym = newtemp();

            (yyval.exprNode2)->truelist = nextquad()+1;//because nextquad() returns the position in the vector that the nextwuad is going to be in
            (yyval.exprNode2)->falselist = nextquad()+2;
            emit(if_noteq, (yyvsp[-3].exprNode2), (yyvsp[0].exprNode2), NULL, 0, yylineno);
            emit(jump, NULL, NULL, NULL, 0, yylineno);  
        }
#line 1765 "parser.cpp"
    break;

  case 29: /* $@3: %empty  */
#line 386 "parser.y"
                   {if ((yyvsp[-1].exprNode2)->type != boolexpr_e) { trueTest((yyvsp[-1].exprNode2)); }}
#line 1771 "parser.cpp"
    break;

  case 30: /* expr: expr AND $@3 M expr  */
#line 386 "parser.y"
                                                                          {
            
           
            if ((yyvsp[0].exprNode2)->type != boolexpr_e ) { 
                trueTest((yyvsp[0].exprNode2)); 
            }

            (yyval.exprNode2) = newexpr(boolexpr_e);
            /*if (istempexpr($1)) {
                $$->sym = $1->sym;
            } else if (istempexpr($5)) {
                $$->sym = $5->sym;
            } else {
                $$->sym = newtemp();
                cout <<"LINE 280: "<<$$->sym->name<<endl;
            }*/
            //$$->sym = newtemp();

            patchlist((yyvsp[-4].exprNode2)->truelist, (yyvsp[-1].intValue));
            (yyval.exprNode2)->truelist = (yyvsp[0].exprNode2)->truelist;
            (yyval.exprNode2)->falselist = mergelist((yyvsp[-4].exprNode2)->falselist, (yyvsp[0].exprNode2)->falselist);
        }
#line 1798 "parser.cpp"
    break;

  case 31: /* $@4: %empty  */
#line 408 "parser.y"
                  {if ((yyvsp[-1].exprNode2)->type != boolexpr_e) { trueTest((yyvsp[-1].exprNode2)); }}
#line 1804 "parser.cpp"
    break;

  case 32: /* expr: expr OR $@4 M expr  */
#line 408 "parser.y"
                                                                         {
            

            if ((yyvsp[0].exprNode2)->type != boolexpr_e) { 
                trueTest((yyvsp[0].exprNode2)); 
            }

            (yyval.exprNode2) = newexpr(boolexpr_e);
            /*if (istempexpr($1)) {
                $$->sym = $1->sym;
            } else if (istempexpr($5)) {
                $$->sym = $5->sym;
            } else {
                $$->sym = newtemp();
            }*/

            patchlist((yyvsp[-4].exprNode2)->falselist,(yyvsp[-1].intValue));
            (yyval.exprNode2)->truelist = mergelist((yyvsp[-4].exprNode2)->truelist, (yyvsp[0].exprNode2)->truelist);
            (yyval.exprNode2)->falselist = (yyvsp[0].exprNode2)->falselist;
        }
#line 1829 "parser.cpp"
    break;

  case 33: /* expr: term  */
#line 428 "parser.y"
               { (yyval.exprNode2) = (yyvsp[0].exprNode2);}
#line 1835 "parser.cpp"
    break;

  case 34: /* M: %empty  */
#line 431 "parser.y"
   { (yyval.intValue) = nextquad() + 1; }
#line 1841 "parser.cpp"
    break;

  case 35: /* N: %empty  */
#line 433 "parser.y"
   {(yyval.intValue) = nextquad()+1; emit(jump, NULL, NULL, NULL, nextquad()+1, yylineno);}
#line 1847 "parser.cpp"
    break;

  case 36: /* term: LEFT_PARENTHESIS expr RIGHT_PARENTHESIS  */
#line 435 "parser.y"
                                                { 
            (yyval.exprNode2) = (yyvsp[-1].exprNode2);
            //if ($2->type == boolexpr_e && !$2->evaluated) shortCircuitEval($2);
        }
#line 1856 "parser.cpp"
    break;

  case 37: /* term: SUBTRACTION expr  */
#line 439 "parser.y"
                           {
            if (!checkarithmetic_type((yyvsp[0].exprNode2),(yyvsp[0].exprNode2))) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                if ((yyvsp[0].exprNode2)->type == constnum_e ) {
                    (yyval.exprNode2) = newexpr(constnum_e);
                    (yyval.exprNode2)->numConst = -1*(yyvsp[0].exprNode2)->numConst;
                } else {
                    (yyval.exprNode2) = newexpr(arithexpr_e);
                }
                if (istempexpr((yyvsp[0].exprNode2))) { /*this if was inside the else above and therefore if $1=constnum && $3==constnum then there wound be an assignement to $$->sym and when print goes to print it segmentation fault happens*/
                    (yyval.exprNode2)->sym = (yyvsp[0].exprNode2)->sym;
                } else {
                    (yyval.exprNode2)->sym = newtemp();
                }
                emit(uminus, (yyvsp[0].exprNode2), NULL, (yyval.exprNode2), 0, yylineno);
        }
#line 1876 "parser.cpp"
    break;

  case 38: /* term: NOT expr  */
#line 454 "parser.y"
                   {
            if ((yyvsp[0].exprNode2)->type != boolexpr_e) {
                trueTest((yyvsp[0].exprNode2));
                //$$ = newexpr(boolexpr_e);
            } /*else {
                $$ = $2;
            }*/

            (yyval.exprNode2) = newexpr(boolexpr_e);

            (yyval.exprNode2)->truelist = (yyvsp[0].exprNode2)->falselist;
            (yyval.exprNode2)->falselist = (yyvsp[0].exprNode2)->truelist;
        }
#line 1894 "parser.cpp"
    break;

  case 39: /* term: PLUSONE lvalue  */
#line 467 "parser.y"
                         { /*if( $2 != NULL) {if($2->sym->type == LIB_FUNCTION || $2->sym->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$2->sym->name+" is declared as a function, forbidden action ++");} */
            if (!checkarithmetic_type((yyvsp[0].exprNode2),(yyvsp[0].exprNode2))) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");

            if ((yyvsp[0].exprNode2)->type == tableitem_e) {
                (yyval.exprNode2) = emit_iftableitem((yyvsp[0].exprNode2));
                emit(add, (yyval.exprNode2), newexpr_constnum(1), (yyval.exprNode2), 0,yylineno);
                emit(tablesetelem, (yyvsp[0].exprNode2)->index, (yyval.exprNode2), (yyvsp[0].exprNode2), 0, yylineno);
            }
            else {
                emit(add, (yyvsp[0].exprNode2), newexpr_constnum(1), (yyvsp[0].exprNode2), 0, yylineno);
                (yyval.exprNode2) = newexpr(arithexpr_e);
                if (istempexpr((yyvsp[0].exprNode2))) { //dont know if i want to reuse temp here
                    (yyval.exprNode2)->sym = (yyvsp[0].exprNode2)->sym;
                } else {
                    (yyval.exprNode2)->sym = newtemp();
                }
                emit(assign, (yyvsp[0].exprNode2), NULL, (yyval.exprNode2),0,yylineno);
            }
        }
#line 1918 "parser.cpp"
    break;

  case 40: /* $@5: %empty  */
#line 486 "parser.y"
                 {if( (yyvsp[0].exprNode2) != NULL) {  /*if($1->sym->type == LIB_FUNCTION || $1->sym->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$1->sym->name+" is declared as a function, forbidden action ++");*/} }
#line 1924 "parser.cpp"
    break;

  case 41: /* term: lvalue $@5 PLUSONE  */
#line 486 "parser.y"
                                                                                                                                                                                                                                                                 {
            if (!checkarithmetic_type((yyvsp[-2].exprNode2),(yyvsp[-2].exprNode2))) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");

            (yyval.exprNode2) = newexpr(var_e);
            if (istempexpr((yyvsp[-2].exprNode2))) { //dont know if i want to reuse temp here
                (yyval.exprNode2)->sym = (yyvsp[-2].exprNode2)->sym;
            } else {
                (yyval.exprNode2)->sym = newtemp();
            }

            if ( (yyvsp[-2].exprNode2)->type == tableitem_e) {
                expr* val = emit_iftableitem((yyvsp[-2].exprNode2));
                emit(assign, val, NULL, (yyval.exprNode2), 0, yylineno);
                emit(add, val, newexpr_constnum(1), val, 0, yylineno);
                emit(tablesetelem, (yyvsp[-2].exprNode2)->index, val, (yyvsp[-2].exprNode2), 0, yylineno);
            } else {
                emit(assign, (yyvsp[-2].exprNode2), NULL, (yyval.exprNode2), 0, yylineno);
                emit(add, (yyvsp[-2].exprNode2), newexpr_constnum(1), (yyvsp[-2].exprNode2), 0, yylineno);
            }
        }
#line 1949 "parser.cpp"
    break;

  case 42: /* term: MINUSONE lvalue  */
#line 506 "parser.y"
                          {if( (yyvsp[0].exprNode2) != NULL) {  /*if($2->sym->type == LIB_FUNCTION || $2->sym->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$2->sym->name+" is declared as a function, forbidden action --");*/} 
            if (!checkarithmetic_type((yyvsp[0].exprNode2),(yyvsp[0].exprNode2))) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");

            if ((yyvsp[0].exprNode2)->type == tableitem_e) {
                (yyval.exprNode2) = emit_iftableitem((yyvsp[0].exprNode2));
                emit(sub, (yyval.exprNode2), newexpr_constnum(1), (yyval.exprNode2), 0,yylineno);
                emit(tablesetelem, (yyvsp[0].exprNode2)->index, (yyval.exprNode2), (yyvsp[0].exprNode2), 0, yylineno);
            }
            else {
                emit(sub, (yyvsp[0].exprNode2), newexpr_constnum(1), (yyvsp[0].exprNode2), 0, yylineno);
                (yyval.exprNode2) = newexpr(arithexpr_e);
                if (istempexpr((yyvsp[0].exprNode2))) { //dont know if i want to reuse temp here
                    (yyval.exprNode2)->sym = (yyvsp[0].exprNode2)->sym;
                } else {
                    (yyval.exprNode2)->sym = newtemp();
                }
                emit(assign, (yyvsp[0].exprNode2), NULL, (yyval.exprNode2),0,yylineno);
            }
        }
#line 1973 "parser.cpp"
    break;

  case 43: /* $@6: %empty  */
#line 525 "parser.y"
                 {if( (yyvsp[0].exprNode2) != NULL) {  /*if($1->sym->type == LIB_FUNCTION || $1->sym->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$1->sym->name+" is declared as a function, forbidden action --");*/} }
#line 1979 "parser.cpp"
    break;

  case 44: /* term: lvalue $@6 MINUSONE  */
#line 525 "parser.y"
                                                                                                                                                                                                                                                                  {
            if (!checkarithmetic_type((yyvsp[-2].exprNode2),(yyvsp[-2].exprNode2))) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");

            (yyval.exprNode2) = newexpr(var_e);
            if (istempexpr((yyvsp[-2].exprNode2))) { //dont know if i want to reuse temp here
                (yyval.exprNode2)->sym = (yyvsp[-2].exprNode2)->sym;
            } else {
                (yyval.exprNode2)->sym = newtemp();
            }

            if ( (yyvsp[-2].exprNode2)->type == tableitem_e) {
                expr* val = emit_iftableitem((yyvsp[-2].exprNode2));
                emit(assign, val, NULL, (yyval.exprNode2), 0, yylineno);
                emit(sub, val, newexpr_constnum(1), val, 0, yylineno);
                emit(tablesetelem, (yyvsp[-2].exprNode2)->index, val, (yyvsp[-2].exprNode2), 0, yylineno);
            } else {
                emit(assign, (yyvsp[-2].exprNode2), NULL, (yyval.exprNode2), 0, yylineno);
                emit(sub, (yyvsp[-2].exprNode2), newexpr_constnum(1), (yyvsp[-2].exprNode2), 0, yylineno);
            }
        }
#line 2004 "parser.cpp"
    break;

  case 45: /* term: primary  */
#line 545 "parser.y"
                  {  (yyval.exprNode2) = (yyvsp[0].exprNode2);}
#line 2010 "parser.cpp"
    break;

  case 46: /* $@7: %empty  */
#line 548 "parser.y"
                   {if( (yyvsp[0].exprNode2) != NULL) {if((yyvsp[0].exprNode2)->sym->type == LIB_FUNCTION || (yyvsp[0].exprNode2)->sym->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+(yyvsp[0].exprNode2)->sym->name+" is declared as a function, forbidden action =");} }
#line 2016 "parser.cpp"
    break;

  case 47: /* assignexpr: lvalue $@7 EQUAL expr  */
#line 548 "parser.y"
                                                                                                                                                                                                                                                               {    
                assert((yyvsp[0].exprNode2));
                if ((yyvsp[-3].exprNode2)->type == tableitem_e) {
                    emit(tablesetelem, (yyvsp[-3].exprNode2)->index, (yyvsp[0].exprNode2), (yyvsp[-3].exprNode2), 0, yylineno);
                    (yyval.exprNode2) = emit_iftableitem((yyvsp[-3].exprNode2));
                    (yyval.exprNode2)->type = assignexpr_e;
                } else {
                    if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) shortCircuitEval((yyvsp[0].exprNode2));
                    emit(assign, (yyvsp[0].exprNode2), NULL, (yyvsp[-3].exprNode2),0,yylineno);
                    
                    (yyval.exprNode2) = newexpr(assignexpr_e);
                    (yyval.exprNode2)->sym = newtemp();
                    /*if (istempexpr($4)) { //dont know if i want to reuse temp here
                        $$->sym = $4->sym;
                    } else {
                        $$->sym = newtemp();
                    }*/
                    
                    emit(assign,(yyvsp[-3].exprNode2),NULL,(yyval.exprNode2),0,yylineno);
                }
            }
#line 2042 "parser.cpp"
    break;

  case 48: /* primary: lvalue  */
#line 571 "parser.y"
                   { (yyval.exprNode2) = emit_iftableitem((yyvsp[0].exprNode2));}
#line 2048 "parser.cpp"
    break;

  case 49: /* primary: call  */
#line 572 "parser.y"
                   { }
#line 2054 "parser.cpp"
    break;

  case 50: /* primary: objectdef  */
#line 573 "parser.y"
                        {}
#line 2060 "parser.cpp"
    break;

  case 51: /* primary: LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS  */
#line 574 "parser.y"
                                                         { 
                (yyval.exprNode2) = newexpr(programfunc_e);
                (yyval.exprNode2)->sym = (yyvsp[-1].exprNode2)->sym;
            }
#line 2069 "parser.cpp"
    break;

  case 52: /* primary: const  */
#line 578 "parser.y"
                    { (yyval.exprNode2) = (yyvsp[0].exprNode2);}
#line 2075 "parser.cpp"
    break;

  case 53: /* lvalue: ID  */
#line 581 "parser.y"
               {   
                   if (symbolTable->lookEverywhere((yyvsp[0].stringValue),SCOPE) == NULL && !RETURNEXPR) {
                        SymbolTableEntry* symbol = new SymbolTableEntry((yyvsp[0].stringValue), SCOPE ? LOCALVAR : GLOBAL, var_s, SCOPE, yylineno, true);
                        symbolTable->insert(symbol); 
                        (yyval.exprNode2) = newexpr(var_e);
                        (yyval.exprNode2)->sym = symbol;
                        //incurrscopeoffset();
                    }   
                    else {
                        SymbolTableEntry* tmp = symbolTable->lookEverywhere((yyvsp[0].stringValue),SCOPE);
                        if (tmp != NULL) {
                            if (tmp->type == USERFUNCTION || tmp->scope == 0) (yyval.exprNode2) = lvalue_expr(tmp);
                            else {
                                int i;
                                for (i=vec.size()-1; vec.at(i)!=FUNCT && i != 0; i--) {
                                    
                                }
                                
                                if (tmp->scope >= i)
                                    (yyval.exprNode2) = lvalue_expr(tmp);
                                else {(yyval.exprNode2) = NULL; symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+(yyvsp[0].stringValue)+" cannot be accessed");}
                            }
                        } else {
                            if (RETURNEXPR) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+(yyvsp[0].stringValue)+" has not been declared");
                            (yyval.exprNode2) = NULL;
                        }
                    }
                }
#line 2108 "parser.cpp"
    break;

  case 54: /* lvalue: LOCAL ID  */
#line 609 "parser.y"
                       {  
                (yyval.exprNode2) = NULL; 
                if( symbolTable->isLibFunct((yyvsp[0].stringValue)) && SCOPE != 0) {
                    symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+(yyvsp[0].stringValue)+": collision with library function");
                }
                else if (SCOPE == 0) {
                    if (symbolTable->isLibFunct((yyvsp[0].stringValue)) ) {
                        (yyval.exprNode2) = lvalue_expr(symbolTable->lookUp((yyvsp[0].stringValue),0));
                    }
                    else {
                        SymbolTableEntry* symbol = new SymbolTableEntry((yyvsp[0].stringValue), GLOBAL, var_s, SCOPE, yylineno, true);
                        symbolTable->insert(symbol);
                        (yyval.exprNode2) = lvalue_expr(symbol);
                        //incurrscopeoffset();
                    }
                }
                else {
                    SymbolTableEntry* symbol = new SymbolTableEntry((yyvsp[0].stringValue), LOCALVAR, var_s, SCOPE, yylineno, true);
                    symbolTable->insert(symbol);
                    (yyval.exprNode2) = lvalue_expr(symbol);
                    //incurrscopeoffset();
                }
            }
#line 2136 "parser.cpp"
    break;

  case 55: /* lvalue: DOUBLECOLON ID  */
#line 632 "parser.y"
                             { 
                if (symbolTable->lookUp((yyvsp[0].stringValue), 0) == NULL) {
                    symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+(yyvsp[0].stringValue)+" undefined variable/function");
                    cout<<"ERROR in line "+to_string(yylineno)+": "+(yyvsp[0].stringValue)+" undefined variable/function"<<endl;
                    exit(EXIT_FAILURE);
                }
                else {
                  (yyval.exprNode2) = lvalue_expr(symbolTable->lookUp((yyvsp[0].stringValue), 0));
                    //symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$2+" undefined variable/function");
                } 
            }
#line 2152 "parser.cpp"
    break;

  case 56: /* lvalue: member  */
#line 643 "parser.y"
                     {  }
#line 2158 "parser.cpp"
    break;

  case 57: /* lvalue: tableitem  */
#line 644 "parser.y"
                        {  (yyval.exprNode2) = (yyvsp[0].exprNode2);}
#line 2164 "parser.cpp"
    break;

  case 58: /* tableitem: lvalue DOT ID  */
#line 647 "parser.y"
                          { 
                
                (yyval.exprNode2) = member_item((yyvsp[-2].exprNode2), (yyvsp[0].stringValue));
            }
#line 2173 "parser.cpp"
    break;

  case 59: /* $@8: %empty  */
#line 651 "parser.y"
                                       {if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) shortCircuitEval((yyvsp[0].exprNode2));}
#line 2179 "parser.cpp"
    break;

  case 60: /* tableitem: lvalue LEFT_BRACKET expr $@8 RIGHT_BRACKET  */
#line 651 "parser.y"
                                                                                                                           { 
                
                (yyvsp[-4].exprNode2) = emit_iftableitem((yyvsp[-4].exprNode2));
                (yyval.exprNode2) = newexpr(tableitem_e);
                (yyval.exprNode2)->sym = (yyvsp[-4].exprNode2)->sym;
                (yyval.exprNode2)->index = (yyvsp[-2].exprNode2);
                }
#line 2191 "parser.cpp"
    break;

  case 61: /* $@9: %empty  */
#line 660 "parser.y"
                         {tableInstansiation = 1; tableitems.clear();}
#line 2197 "parser.cpp"
    break;

  case 62: /* tablemake: LEFT_BRACKET $@9 elist RIGHT_BRACKET  */
#line 660 "parser.y"
                                                                                           {
                tableInstansiation = 0;
                
                expr* t = newexpr(newtable_e);
                //t->sym = newtemp();
                //t->next = tableitems.at(0);
                emit(tablecreate, NULL, NULL, t, 0, yylineno);
                
                if (!tableitems.empty()) {
                    t->sym = newtemp();

                    t->next = tableitems.at(0);
                    emit(tablesetelem, newexpr_constnum(0), tableitems[0], t, 0, yylineno);
                    for (int i = 1; i < tableitems.size(); i++) {
                        emit(tablesetelem, newexpr_constnum(i), tableitems.at(i), t, 0, yylineno);
                        tableitems.at(i-1)->next = tableitems.at(i);
                    }
                } else {
                    t->sym = newtemp();
                }
                tableitems.clear();
                (yyval.exprNode2) = t;
            }
#line 2225 "parser.cpp"
    break;

  case 63: /* tablemake: LEFT_BRACKET indexed RIGHT_BRACKET  */
#line 683 "parser.y"
                                                 {
                
                expr* t = newexpr(newtable_e);
                t->sym = newtemp();
                emit(tablecreate, NULL, NULL, t, 0, yylineno);
                for(int i=0; i<pairA.size(); i++)
                    emit(tablesetelem, pairA.at(i), pairB.at(i), t, 0, yylineno);
                pairA.clear();
                pairB.clear();
                (yyval.exprNode2) = t;
            }
#line 2241 "parser.cpp"
    break;

  case 64: /* member: call DOT ID  */
#line 696 "parser.y"
                        { 
                (yyval.exprNode2) = member_item((yyvsp[-2].exprNode2), (yyvsp[0].stringValue));
            }
#line 2249 "parser.cpp"
    break;

  case 65: /* $@10: %empty  */
#line 699 "parser.y"
                                    {if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) shortCircuitEval((yyvsp[0].exprNode2));}
#line 2255 "parser.cpp"
    break;

  case 66: /* member: call LEFT_BRACKET expr $@10 RIGHT_BRACKET  */
#line 699 "parser.y"
                                                                                                                        { 
                (yyvsp[-4].exprNode2) = emit_iftableitem((yyvsp[-4].exprNode2));
                (yyval.exprNode2) = newexpr(tableitem_e);
                (yyval.exprNode2)->sym = (yyvsp[-4].exprNode2)->sym;
                (yyval.exprNode2)->index = (yyvsp[-2].exprNode2);
            }
#line 2266 "parser.cpp"
    break;

  case 67: /* $@11: %empty  */
#line 707 "parser.y"
                 {functionCall = 1;}
#line 2272 "parser.cpp"
    break;

  case 68: /* $@12: %empty  */
#line 707 "parser.y"
                                                      {tableitems.clear();}
#line 2278 "parser.cpp"
    break;

  case 69: /* call: call $@11 LEFT_PARENTHESIS $@12 elist RIGHT_PARENTHESIS  */
#line 707 "parser.y"
                                                                                                    { functionCall = 0;
                (yyvsp[-5].exprNode2) = emit_iftableitem((yyvsp[-5].exprNode2));
                for (int i = tableitems.size()-1; i>=0; i--) {
                    emit(param,tableitems.at(i),NULL,NULL,0,yylineno);
                }
                tableitems.clear();
                expr* e = newexpr(var_e);
                e->sym = newtemp();
                (yyval.exprNode2) = e;
                emit(call,(yyvsp[-5].exprNode2),NULL,NULL,0,yylineno);
                emit(getretval,NULL,NULL,e,0,yylineno);
            }
#line 2295 "parser.cpp"
    break;

  case 70: /* $@13: %empty  */
#line 719 "parser.y"
                     {functionCall = 1;}
#line 2301 "parser.cpp"
    break;

  case 71: /* call: lvalue $@13 callsuffix  */
#line 719 "parser.y"
                                                    {
              expr* lvalueName  = (yyvsp[-2].exprNode2); 
              if (doubleDotEncountered) (yyvsp[-2].exprNode2) = member_item((yyvsp[-2].exprNode2), (yyvsp[0].stringValue));
              (yyvsp[-2].exprNode2) = emit_iftableitem((yyvsp[-2].exprNode2));
        
              for (int i = tableitems.size()-1; i>=0; i--) {
                emit(param,tableitems.at(i),NULL,NULL,0,yylineno);
              }
              tableitems.clear(); 

              if (doubleDotEncountered) {
                emit(param, lvalueName, NULL, NULL, 0, yylineno);  
                doubleDotEncountered = false;
              }

              expr* e = newexpr(var_e); //expr* e  = newexpr($1->type);i changed it because in the const arrays temporary veriables would appear
              e->sym = newtemp();
              (yyval.exprNode2) = e;
              emit(call,(yyvsp[-2].exprNode2),NULL,NULL,0,yylineno);
              emit(getretval,NULL,NULL,e,0,yylineno);
              functionCall = 0;
            }
#line 2328 "parser.cpp"
    break;

  case 72: /* $@14: %empty  */
#line 741 "parser.y"
                                                                          {functionCall = 1; tableitems.clear();}
#line 2334 "parser.cpp"
    break;

  case 73: /* call: LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS $@14 elist RIGHT_PARENTHESIS  */
#line 741 "parser.y"
                                                                                                                                          {
               

                expr* func = emit_iftableitem((yyvsp[-5].exprNode2));
                for (int i = tableitems.size()-1; i>=0; i--) {
                    emit(param,tableitems.at(i),NULL,NULL,0,yylineno);
                }
                emit(call,(yyvsp[-5].exprNode2),NULL,NULL,0,yylineno);
                expr* result = newexpr(var_e);
                result->sym = newtemp();
                emit(getretval,NULL,NULL,result,0,yylineno);
                (yyval.exprNode2) = result;
                functionCall = 0;
            }
#line 2353 "parser.cpp"
    break;

  case 74: /* callsuffix: normcall  */
#line 757 "parser.y"
                     { }
#line 2359 "parser.cpp"
    break;

  case 75: /* callsuffix: methodcall  */
#line 758 "parser.y"
                         { doubleDotEncountered = true; (yyval.stringValue)  = (yyvsp[0].stringValue); }
#line 2365 "parser.cpp"
    break;

  case 76: /* $@15: %empty  */
#line 761 "parser.y"
                            {tableitems.clear();}
#line 2371 "parser.cpp"
    break;

  case 77: /* normcall: LEFT_PARENTHESIS $@15 elist RIGHT_PARENTHESIS  */
#line 761 "parser.y"
                                                                          {
    
            }
#line 2379 "parser.cpp"
    break;

  case 78: /* $@16: %empty  */
#line 766 "parser.y"
                                          {tableitems.clear();}
#line 2385 "parser.cpp"
    break;

  case 79: /* methodcall: DOUBLEDOT ID LEFT_PARENTHESIS $@16 elist RIGHT_PARENTHESIS  */
#line 766 "parser.y"
                                                                                        {
               (yyval.stringValue) = (yyvsp[-4].stringValue);
            }
#line 2393 "parser.cpp"
    break;

  case 80: /* $@17: %empty  */
#line 771 "parser.y"
                 {if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) shortCircuitEval((yyvsp[0].exprNode2));}
#line 2399 "parser.cpp"
    break;

  case 81: /* elist: expr $@17 exprs  */
#line 771 "parser.y"
                                                                                             { 
                tableitems.insert(tableitems.begin(), (yyvsp[-2].exprNode2));
                //if (functionCall) emit(param,$1,NULL,NULL,0,yylineno);
            }
#line 2408 "parser.cpp"
    break;

  case 82: /* elist: %empty  */
#line 775 "parser.y"
                        { (yyval.exprNode2) = NULL; }
#line 2414 "parser.cpp"
    break;

  case 83: /* $@18: %empty  */
#line 778 "parser.y"
                       {if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) shortCircuitEval((yyvsp[0].exprNode2));}
#line 2420 "parser.cpp"
    break;

  case 84: /* exprs: COMMA expr $@18 exprs  */
#line 778 "parser.y"
                                                                                                   { 
                tableitems.insert(tableitems.begin(), (yyvsp[-2].exprNode2));
                //if (functionCall) emit(param,$2,NULL,NULL,0,yylineno);
            }
#line 2429 "parser.cpp"
    break;

  case 85: /* exprs: %empty  */
#line 782 "parser.y"
                        {}
#line 2435 "parser.cpp"
    break;

  case 87: /* indexed: indexedelem indexedelems  */
#line 788 "parser.y"
                                     {}
#line 2441 "parser.cpp"
    break;

  case 88: /* indexedelems: COMMA indexedelem indexedelems  */
#line 791 "parser.y"
                                               {}
#line 2447 "parser.cpp"
    break;

  case 89: /* indexedelems: %empty  */
#line 792 "parser.y"
                            {}
#line 2453 "parser.cpp"
    break;

  case 90: /* $@19: %empty  */
#line 795 "parser.y"
                                        {if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) shortCircuitEval((yyvsp[0].exprNode2));}
#line 2459 "parser.cpp"
    break;

  case 91: /* $@20: %empty  */
#line 795 "parser.y"
                                                                                                                         {if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) shortCircuitEval((yyvsp[0].exprNode2));}
#line 2465 "parser.cpp"
    break;

  case 92: /* indexedelem: LEFT_CURLY_BRACKET expr $@19 COLON expr $@20 RIGHT_CURLY_BRACKET  */
#line 795 "parser.y"
                                                                                                                                                                                                                   {                    
                    pairA.push_back((yyvsp[-5].exprNode2));
                    pairB.push_back((yyvsp[-2].exprNode2));
                }
#line 2474 "parser.cpp"
    break;

  case 93: /* $@21: %empty  */
#line 801 "parser.y"
                                   { //enterscopespace(); resetscopespace(); 
                    if (!insideAFunction) { 
                        SCOPE++; 
                        vec.push_back(BLOCK); 
                    } else {
                        insideAFunction = false;
                    } 
                }
#line 2487 "parser.cpp"
    break;

  case 94: /* block: LEFT_CURLY_BRACKET $@21 stmts RIGHT_CURLY_BRACKET  */
#line 809 "parser.y"
                                          { 
                    if (vec.back() == BLOCK) { 
                        //exitscopespace();
                        symbolTable->hide(SCOPE);
                        SCOPE--;
                        vec.pop_back();
                    } /*else if (vec.back() == FUNCT ) {
                        exitscopespace(); 
                        exitscopespace();
                    } */
                    
                }
#line 2504 "parser.cpp"
    break;

  case 95: /* funcdef: funcprefix funcargs funcbody  */
#line 823 "parser.y"
                                                 {
                                                    (yyval.exprNode2)=(yyvsp[-2].exprNode2); 
                                                    (yyval.exprNode2)->sym->localstotal = (yyvsp[0].intValue);
                                                    if(returnLabel.back()){patchlabel(returnLabel.back()+1,nextquad()+1);}
                                                    emit(funcend, NULL, NULL, (yyvsp[-2].exprNode2),0,yylineno);
                                                    patchlabel((yyval.exprNode2)->sym->funcAddr-1,nextquad()+1); //patchlabel($$->sym->funcAddr,nextquad()+1);
                                                    returnLabel.pop_back();
                                                    functCounter--;
                                                    if(!contlist.empty() && !breaklist.empty()){
                                                        if(contlist.back()!=-10 || breaklist.back()!=-10)  symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": breaklist or contlist failed");
                                                        else{
                                                            loopActive=true;
                                                            contlist.pop_back();
                                                            breaklist.pop_back();
                                                        }
                                                    }
                    }
#line 2526 "parser.cpp"
    break;

  case 96: /* funcprefix: FUNCTION funcname  */
#line 841 "parser.y"
                                      {
                            if((yyvsp[0].stringValue)) symbolTable->insert(tmpFunct = new SymbolTableEntry((yyvsp[0].stringValue), USERFUNCTION, programfunc_s, SCOPE, yylineno, true));
                            else symbolTable->insert(tmpFunct= new SymbolTableEntry("_f"+to_string(FUNCTNUM++), USERFUNCTION, programfunc_s,SCOPE, yylineno, true));
                            (yyval.exprNode2)= lvalue_expr(tmpFunct);
                            emit(jump, NULL, NULL, NULL,0,yylineno);
                            tmpFunct->funcAddr = nextquad()+1; //tmpFunct->funcAddr = nextquad()
                            emit(funcstart, NULL, NULL, (yyval.exprNode2),0,yylineno);
                            enterscopespace(); 
                            resetformalargspace(); 
                            if(loopActive) {
                                breaklist.push_back(-10);
                                contlist.push_back(-10);
                                loopActive=false;
                            }
                    }
#line 2546 "parser.cpp"
    break;

  case 97: /* $@22: %empty  */
#line 857 "parser.y"
                                    {insideAFunction = true;  
                                    SCOPE++; 
                                    vec.push_back(FUNCT);
                                    }
#line 2555 "parser.cpp"
    break;

  case 98: /* funcargs: LEFT_PARENTHESIS $@22 idlist RIGHT_PARENTHESIS  */
#line 861 "parser.y"
                                             {  
                                        functCounter++;
                                        returnLabel.push_back(0);
                                        if(functCounter>1){ offsetStack.push_back(functionLocalOffset); }
                                        enterscopespace(); 
                                        resetfunclocalspace();
                                        }
#line 2567 "parser.cpp"
    break;

  case 99: /* funcbody: block  */
#line 870 "parser.y"
                         {  vec.pop_back(); 
                            symbolTable->hide(SCOPE); 
                            SCOPE--; 
                            tmpFunct = NULL;
                            (yyval.intValue) = currscopeoffset(); 
                            exitscopespace();
                            exitscopespace();
                            if(functCounter>1) {
                                    functionLocalOffset= offsetStack.back();
                                    offsetStack.pop_back();
                             }
                        }
#line 2584 "parser.cpp"
    break;

  case 100: /* funcname: ID  */
#line 884 "parser.y"
                       {(yyval.stringValue)=(yyvsp[0].stringValue); }
#line 2590 "parser.cpp"
    break;

  case 101: /* funcname: %empty  */
#line 885 "parser.y"
                                {(yyval.stringValue) = NULL;}
#line 2596 "parser.cpp"
    break;

  case 102: /* const: INTEGER  */
#line 887 "parser.y"
                        {
                    (yyval.exprNode2) = newexpr(constnum_e);
                    (yyval.exprNode2)->numConst= (yyvsp[0].intValue);
                }
#line 2605 "parser.cpp"
    break;

  case 103: /* const: FLOAT  */
#line 891 "parser.y"
                       {
                    (yyval.exprNode2) = newexpr(constnum_e);
                    (yyval.exprNode2)->numConst= (yyvsp[0].realValue);
                }
#line 2614 "parser.cpp"
    break;

  case 104: /* const: STRINGG  */
#line 895 "parser.y"
                         {
                    (yyval.exprNode2) = newexpr(conststring_e);
                    (yyval.exprNode2)->strConst= (yyvsp[0].stringValue);
                }
#line 2623 "parser.cpp"
    break;

  case 105: /* const: NILL  */
#line 899 "parser.y"
                      {
                    (yyval.exprNode2) = newexpr(nil_e);
                    
                }
#line 2632 "parser.cpp"
    break;

  case 106: /* const: TRUE  */
#line 903 "parser.y"
                      {
                    (yyval.exprNode2) = newexpr(constbool_e);
                    (yyval.exprNode2)->boolConst= true;
                }
#line 2641 "parser.cpp"
    break;

  case 107: /* const: FALSE  */
#line 907 "parser.y"
                        {
                    (yyval.exprNode2) = newexpr(constbool_e);
                    (yyval.exprNode2)->boolConst= false;
                }
#line 2650 "parser.cpp"
    break;

  case 108: /* $@23: %empty  */
#line 912 "parser.y"
                   { SymbolTableEntry* tmparg; symbolTable->insert(tmparg = new SymbolTableEntry((yyvsp[0].stringValue), FORMAL, var_s, SCOPE, yylineno, true)); if (tmpFunct != NULL){ tmpFunct->insertArg(tmparg); } /*incurrscopeoffset();*/}
#line 2656 "parser.cpp"
    break;

  case 109: /* idlist: ID $@23 ids  */
#line 912 "parser.y"
                                                                                                                                                                                                                                 {}
#line 2662 "parser.cpp"
    break;

  case 110: /* idlist: %empty  */
#line 913 "parser.y"
                            {}
#line 2668 "parser.cpp"
    break;

  case 111: /* $@24: %empty  */
#line 916 "parser.y"
                         { SymbolTableEntry* tmparg; symbolTable->insert(tmparg = new SymbolTableEntry((yyvsp[0].stringValue), FORMAL, var_s, SCOPE, yylineno, true)); if (tmpFunct != NULL){ tmpFunct->insertArg(tmparg); } /*incurrscopeoffset();*/}
#line 2674 "parser.cpp"
    break;

  case 112: /* ids: COMMA ID $@24 ids  */
#line 916 "parser.y"
                                                                                                                                                                                                                                      {}
#line 2680 "parser.cpp"
    break;

  case 113: /* ids: %empty  */
#line 917 "parser.y"
                            {}
#line 2686 "parser.cpp"
    break;

  case 114: /* ifstmt: ifprefix stmt  */
#line 920 "parser.y"
                              {
                     
                    patchlabel((yyvsp[-1].intValue), nextquad()+1);
                   // patchlist($2->breaklist, nextquad()+1);
                    //patchlist($2->contlist, $1);
                }
#line 2697 "parser.cpp"
    break;

  case 115: /* ifstmt: ifprefix stmt elseprefix stmt  */
#line 926 "parser.y"
                                               {
                    
                    patchlabel((yyvsp[-3].intValue), (yyvsp[-1].intValue) + 1);
                    patchlabel((yyvsp[-1].intValue), nextquad()+1);
                }
#line 2707 "parser.cpp"
    break;

  case 116: /* $@25: %empty  */
#line 933 "parser.y"
                                         {if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) shortCircuitEval((yyvsp[0].exprNode2)); }
#line 2713 "parser.cpp"
    break;

  case 117: /* ifprefix: IF LEFT_PARENTHESIS expr $@25 RIGHT_PARENTHESIS  */
#line 933 "parser.y"
                                                                                                                                  {
                    emit(if_eq, (yyvsp[-2].exprNode2), newexpr_constbool(1), NULL, nextquad()+3, yylineno); 
                    (yyval.intValue) = nextquad() +1; 
                    emit(jump, NULL, NULL, NULL, nextquad()+1, yylineno);
                }
#line 2723 "parser.cpp"
    break;

  case 118: /* elseprefix: ELSE  */
#line 940 "parser.y"
                    {
                    (yyval.intValue) = nextquad() + 1;
                    emit(jump, NULL, NULL, NULL, nextquad()+1, yylineno);
                }
#line 2732 "parser.cpp"
    break;

  case 119: /* whilestmt: whilestart whilecond stmt  */
#line 946 "parser.y"
                                          {
                    
                    emit(jump, NULL, NULL, NULL, (yyvsp[-2].intValue), yylineno);
                    patchlabel((yyvsp[-1].intValue), nextquad()+1);
                    loopActive = false;
                    while(breaklist.back()!=-1){
                        patchlabel(breaklist.back(), nextquad()+1);
                        breaklist.pop_back();
                    }
                    breaklist.pop_back();
                    while(contlist.back()!=-1){
                        patchlabel(contlist.back(), (yyvsp[-2].intValue));
                        contlist.pop_back();
                    }
                    contlist.pop_back();
                    if(!breaklist.empty()){ loopActive = true;}
                }
#line 2754 "parser.cpp"
    break;

  case 120: /* whilestart: WHILE  */
#line 965 "parser.y"
                     { (yyval.intValue) = nextquad()+1; 
                    loopActive= true; 
                    breaklist.push_back(-1); 
                    contlist.push_back(-1);
                }
#line 2764 "parser.cpp"
    break;

  case 121: /* $@26: %empty  */
#line 971 "parser.y"
                                      {if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) shortCircuitEval((yyvsp[0].exprNode2)); }
#line 2770 "parser.cpp"
    break;

  case 122: /* whilecond: LEFT_PARENTHESIS expr $@26 RIGHT_PARENTHESIS  */
#line 971 "parser.y"
                                                                                                                              {
                    if ((yyvsp[-2].exprNode2)->type == boolexpr_e && !(yyvsp[-2].exprNode2)->evaluated) shortCircuitEval((yyvsp[-2].exprNode2));
    
                    emit(if_eq, (yyvsp[-2].exprNode2), newexpr_constbool(1), NULL, nextquad()+3, yylineno);
                    (yyval.intValue) = nextquad()+1;
                    emit(jump, NULL, NULL, NULL, nextquad()+1, yylineno);
                }
#line 2782 "parser.cpp"
    break;

  case 123: /* $@27: %empty  */
#line 980 "parser.y"
                            {tableitems.clear();}
#line 2788 "parser.cpp"
    break;

  case 124: /* forstmt: forprefix N $@27 elist RIGHT_PARENTHESIS N stmt N  */
#line 980 "parser.y"
                                                                                   {
                    
                    patchlabel((yyvsp[-7].forNode)->enter, (yyvsp[-2].intValue) + 1); 
                    patchlabel((yyvsp[-6].intValue), nextquad()+1);
                    
                    patchlabel((yyvsp[-2].intValue), (yyvsp[-7].forNode)->test); 
                    patchlabel((yyvsp[0].intValue), (yyvsp[-6].intValue) +1);
                    loopActive= false;
                    while(breaklist.back()!=-1){
                        patchlabel(breaklist.back(), nextquad()+1);
                        breaklist.pop_back();
                    }
                    breaklist.pop_back();
                    while(contlist.back()!=-1){
                        patchlabel(contlist.back(), (yyvsp[-6].intValue)+1);
                        contlist.pop_back();
                    }
                    contlist.pop_back();
                    if(!breaklist.empty()){ loopActive = true;}
                }
#line 2813 "parser.cpp"
    break;

  case 125: /* $@28: %empty  */
#line 1002 "parser.y"
                                     {tableitems.clear();}
#line 2819 "parser.cpp"
    break;

  case 126: /* $@29: %empty  */
#line 1002 "parser.y"
                                                                                  {if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) shortCircuitEval((yyvsp[0].exprNode2)); }
#line 2825 "parser.cpp"
    break;

  case 127: /* forprefix: FOR LEFT_PARENTHESIS $@28 elist SEMICOLON M expr $@29 SEMICOLON  */
#line 1002 "parser.y"
                                                                                                                                                                   {
                    (yyval.forNode) = new forprefix();
                    (yyval.forNode)->test = (yyvsp[-3].intValue);
                    (yyval.forNode)->enter = nextquad()+1;
                    
                    emit(if_eq, (yyvsp[-2].exprNode2), newexpr_constbool(1), NULL, nextquad()+4, yylineno);
                    breaklist.push_back(-1); 
                    contlist.push_back(-1);
                    loopActive=true; 
                }
#line 2840 "parser.cpp"
    break;

  case 128: /* $@30: %empty  */
#line 1015 "parser.y"
                       { RETURNEXPR = true; }
#line 2846 "parser.cpp"
    break;

  case 129: /* $@31: %empty  */
#line 1015 "parser.y"
                                                   {if ((yyvsp[0].exprNode2)->type == boolexpr_e && !(yyvsp[0].exprNode2)->evaluated) shortCircuitEval((yyvsp[0].exprNode2)); }
#line 2852 "parser.cpp"
    break;

  case 130: /* returnstmt: RETURN $@30 expr $@31 SEMICOLON  */
#line 1015 "parser.y"
                                                                                                                                    {  RETURNEXPR = false; 
                                                                if(functCounter){
                                                                    emit(ret,NULL,NULL,(yyvsp[-2].exprNode2),0,yylineno);
                                                                    returnLabel.at(functCounter-1)= nextquad();
                                                                    emit(jump,NULL,NULL,NULL,0,yylineno);
                                                                } else  symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+"RETURN statement allowed inside functions only");
                                                                }
#line 2864 "parser.cpp"
    break;

  case 131: /* returnstmt: RETURN SEMICOLON  */
#line 1022 "parser.y"
                                   {if(functCounter){
                                        emit(ret,NULL,NULL,NULL,0,yylineno); 
                                        returnLabel.at(functCounter-1)= nextquad();
                                        emit(jump,NULL,NULL,NULL,0,yylineno);
                                    } else symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+"RETURN statement allowed inside functions only");
                                    }
#line 2875 "parser.cpp"
    break;


#line 2879 "parser.cpp"

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

#line 1030 "parser.y"


int yyerror (string yaccProvideMessage){
	symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": token \""+ yytext +"\" "+yaccProvideMessage.c_str());
    return 0;
}

int main(int argc, char **argv) {
    if(argc > 1) {
        vec.push_back(ZERO);
        if(!(yyin = fopen(argv[1],"r"))) {
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    }
    else {
        yyin = stdin;
    }

    yyparse();
    assert(quads.size() == quadptrs.size());
    symbolTable->displayHash();
    if (symbolTable->errors.empty()) printQuads();
    findConsts(); //find cosnts and add them to the const tables
    generate_targetcode(); //create instructions
    printInstructions();
    generateBinaryFile();
    return 0;
}

