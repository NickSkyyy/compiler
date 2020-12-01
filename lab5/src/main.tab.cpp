/* A Bison parser, made by GNU Bison 3.5.1.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/main.y"

    #include "common.h"
    TreeNode* root;
    extern int lineNo;
    int yylex();
    int yyerror(char const*);

#line 78 "src/main.tab.cpp"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SRC_MAIN_TAB_H_INCLUDED
# define YY_YY_SRC_MAIN_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_AND = 258,
    T_ASS = 259,
    T_DIV = 260,
    T_DIVE = 261,
    T_EQ = 262,
    T_LA = 263,
    T_LAE = 264,
    T_LE = 265,
    T_LEE = 266,
    T_MINE = 267,
    T_MINS = 268,
    T_MOD = 269,
    T_MODE = 270,
    T_MUL = 271,
    T_MULE = 272,
    T_NOT = 273,
    T_NOTE = 274,
    T_OR = 275,
    T_PLUE = 276,
    T_PLUS = 277,
    ID = 278,
    BOOL = 279,
    CHAR = 280,
    INT = 281,
    STRING = 282,
    BREAK = 283,
    CONST = 284,
    CONTINUE = 285,
    ELSE = 286,
    FOR = 287,
    IF = 288,
    MAIN = 289,
    RETURN = 290,
    TYPE = 291,
    WHILE = 292,
    COMA = 293,
    LBRAC = 294,
    RBRAC = 295,
    LPATH = 296,
    RPATH = 297,
    SEMI = 298,
    CHAR_IN = 299,
    INT_IN = 300,
    STR_IN = 301,
    CHAR_OUT = 302,
    INT_OUT = 303,
    STR_OUT = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_MAIN_TAB_H_INCLUDED  */



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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   269

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  211

#define YYUNDEFTOK  2
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    32,    32,    42,    52,    58,    68,    74,    84,    90,
      99,   108,   117,   126,   138,   152,   156,   160,   166,   169,
     173,   176,   183,   189,   201,   213,   216,   219,   222,   228,
     232,   238,   241,   247,   254,   261,   267,   273,   276,   279,
     282,   288,   296,   307,   316,   323,   329,   333,   339,   346,
     353,   360,   366,   373,   377,   383,   389,   395,   401,   407,
     413,   422,   425,   435,   438,   448,   451,   458,   468,   474,
     477,   480,   483,   489,   492,   499,   506,   513,   523,   530,
     533,   536,   539,   542,   545,   554,   562,   565,   568,   575,
     578,   588,   591,   600,   605,   610,   618,   629,   632,   643,
     646,   649,   652,   658,   662
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_AND", "T_ASS", "T_DIV", "T_DIVE",
  "T_EQ", "T_LA", "T_LAE", "T_LE", "T_LEE", "T_MINE", "T_MINS", "T_MOD",
  "T_MODE", "T_MUL", "T_MULE", "T_NOT", "T_NOTE", "T_OR", "T_PLUE",
  "T_PLUS", "ID", "BOOL", "CHAR", "INT", "STRING", "BREAK", "CONST",
  "CONTINUE", "ELSE", "FOR", "IF", "MAIN", "RETURN", "TYPE", "WHILE",
  "COMA", "LBRAC", "RBRAC", "LPATH", "RPATH", "SEMI", "CHAR_IN", "INT_IN",
  "STR_IN", "CHAR_OUT", "INT_OUT", "STR_OUT", "$accept", "Assign", "Block",
  "BlockItem", "CompUnit", "Cond", "ConstDecl", "ConstDef", "ConstInitVal",
  "ConstRest", "Decl", "EqExp", "Exp", "ForHead", "FuncDef", "FuncFParam",
  "FuncFParams", "FuncFRest", "HighExp", "IfRest", "IO", "LAndExp",
  "LOrExp", "LowExp", "Lval", "PrimaryExp", "RelExp", "StartProg", "Stmt",
  "UnaryExp", "UnaryOp", "VarDecl", "VarDef", "VarInitVal", "VarRest", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF (-128)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-37)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      39,   -22,   -10,  -128,  -128,    39,    39,    46,  -128,    33,
       2,    25,    20,  -128,  -128,  -128,    68,    43,    80,    47,
      47,    64,    58,   212,    33,    65,  -128,  -128,  -128,  -128,
    -128,  -128,  -128,  -128,   228,  -128,     4,    17,  -128,  -128,
    -128,   228,  -128,    87,    81,    95,    99,   142,    20,  -128,
    -128,  -128,  -128,  -128,  -128,    43,  -128,   109,     9,   111,
       7,  -128,    13,   123,   228,   228,   228,   228,   228,  -128,
    -128,    47,  -128,   118,   118,  -128,  -128,  -128,   228,   228,
    -128,   228,   228,   228,   228,   228,   228,  -128,  -128,  -128,
       4,     4,    81,    41,  -128,  -128,    17,   123,   123,     9,
    -128,    17,    17,    17,    17,  -128,   116,   120,   126,   128,
      -1,    64,   129,  -128,   130,   133,   134,   136,  -128,   121,
      41,   137,  -128,   243,    41,  -128,  -128,   119,   228,  -128,
     139,   228,    97,   228,   -12,  -128,  -128,  -128,  -128,   187,
     228,   228,   228,   228,   228,  -128,   141,  -128,   143,  -128,
     228,   243,   147,  -128,   149,   151,   153,   157,   159,   164,
     165,  -128,  -128,  -128,   135,   156,   167,  -128,  -128,  -128,
    -128,  -128,  -128,  -128,  -128,   172,   117,   117,   173,   174,
     175,   176,   177,   178,   180,   181,   182,   203,   196,  -128,
    -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,  -128,   198,
     155,  -128,   117,   188,  -128,  -128,   228,   200,   117,   196,
    -128
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,    78,    31,    18,    20,     0,    32,     0,
      97,     0,   104,    19,    21,     1,     0,    30,     0,    45,
      45,     0,     0,     0,     0,     0,    93,    94,    95,    68,
      99,   100,    71,   102,     0,   101,    65,    36,    72,    91,
      51,     0,    98,     0,    47,     0,     0,    97,   104,    96,
      25,    26,    28,    24,    27,    30,    23,     0,    61,     0,
      63,    22,    73,    35,     0,     0,     0,     0,     0,    92,
      43,     0,    44,     0,     0,   103,    29,    69,     0,     0,
      70,     0,     0,     0,     0,     0,     0,    48,    49,    50,
      67,    66,    47,    17,    42,    41,    73,    33,    34,    62,
      64,    74,    75,    76,    77,    46,     0,     0,     0,     0,
       0,     0,     0,    89,     0,     0,     0,     0,    80,     0,
      17,     0,    86,    72,    17,    81,    82,     0,     0,    87,
       0,     0,     0,     0,     0,    79,    14,    15,    83,     0,
       0,     0,     0,     0,     0,    16,    68,    40,     0,    38,
       0,     0,     0,    88,     0,     0,     0,     0,     0,     0,
       0,     2,     3,     7,     0,     0,     0,     5,     9,    10,
      11,    12,    13,    39,    37,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,    90,
      56,    55,    57,    58,    59,    60,     4,     6,     8,     0,
       0,    85,     0,     0,    53,    84,     0,     0,     0,    54,
      52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -128,  -122,   -42,   -67,    86,  -127,  -128,   219,  -128,   189,
     -86,   171,   -15,  -128,  -128,   185,   225,   169,    32,    48,
    -128,  -128,   166,   -34,   -91,  -128,    36,  -128,   -64,    -4,
    -128,  -128,   238,  -128,   214
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   117,   118,   119,     3,    57,     4,    17,    53,    25,
       5,    58,   121,   150,     6,    44,    45,    72,    36,   201,
     122,    60,    61,    37,    38,    39,    63,     7,   124,    40,
      41,     8,    12,    42,    22
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,   152,   123,    35,   154,   148,    18,   120,    54,    64,
      81,   159,    26,    10,     9,   160,    78,    27,    65,    59,
      66,    28,    29,   175,    11,    32,    67,    82,    79,   123,
      67,    94,    95,   123,   120,    68,   151,    69,   120,    68,
      34,   149,   129,    19,    96,    96,    15,    96,    96,   101,
     102,   103,   104,   137,    26,   -36,    16,   145,    21,    27,
      87,    88,    89,    28,    29,   199,    20,    32,     1,   106,
       1,   107,    23,   108,   109,     2,   110,   111,   112,   207,
      93,    24,    34,    43,   113,   123,   123,    47,   114,   115,
     116,    13,    14,    26,    96,   130,   151,    96,    27,    90,
      91,    49,    28,    29,    30,    31,    32,    33,    56,   123,
      70,   123,   188,   189,    97,    98,    96,   123,   158,    71,
     155,    34,   156,   157,   167,   168,   169,   170,   171,   172,
      26,    83,    84,    85,    86,    27,   204,    73,   205,    28,
      29,    74,   146,    32,   209,   106,    18,   107,     1,   108,
     109,    77,   110,    80,   112,   111,    93,    93,    34,   125,
     113,   136,   147,   126,   114,   115,   116,   127,    26,   128,
     131,   132,    96,    27,   133,   134,   184,    28,    29,   135,
     138,    32,   153,   106,   173,   107,   174,   108,   203,   176,
     110,   177,   112,   178,    93,   179,    34,   185,   113,   180,
      26,   181,   114,   115,   116,    27,   182,   183,   186,    28,
      29,   161,   162,    32,   163,   187,   190,   191,   192,   193,
     194,   195,   196,   197,   198,    26,    29,   200,    34,   206,
      27,   164,   165,   166,    28,    29,    50,    51,    32,    52,
     202,    26,   208,    55,    76,    46,    27,   139,   100,   140,
      28,    29,    99,    34,    32,   141,    92,   210,   142,    48,
     143,   105,    75,     0,   144,     0,     0,     0,     0,    34
};

static const yytype_int16 yycheck[] =
{
      34,   128,    93,    18,   131,   127,     4,    93,    23,     5,
       3,    23,    13,    23,    36,    27,     7,    18,    14,    34,
      16,    22,    23,   150,    34,    26,    13,    20,    19,   120,
      13,    73,    74,   124,   120,    22,   127,    41,   124,    22,
      41,   127,    43,    41,    78,    79,     0,    81,    82,    83,
      84,    85,    86,   120,    13,    42,    23,   124,    38,    18,
      64,    65,    66,    22,    23,   187,    41,    26,    29,    28,
      29,    30,     4,    32,    33,    36,    35,    36,    37,   206,
      39,    38,    41,    36,    43,   176,   177,    23,    47,    48,
      49,     5,     6,    13,   128,   110,   187,   131,    18,    67,
      68,    43,    22,    23,    24,    25,    26,    27,    43,   200,
      23,   202,   176,   177,    78,    79,   150,   208,   133,    38,
      23,    41,    25,    26,   139,   140,   141,   142,   143,   144,
      13,     8,     9,    10,    11,    18,   200,    42,   202,    22,
      23,    42,    23,    26,   208,    28,     4,    30,    29,    32,
      33,    42,    35,    42,    37,    36,    39,    39,    41,    43,
      43,    40,    43,    43,    47,    48,    49,    41,    13,    41,
      41,    41,   206,    18,    41,    41,    41,    22,    23,    43,
      43,    26,    43,    28,    43,    30,    43,    32,    33,    42,
      35,    42,    37,    42,    39,    42,    41,    41,    43,    42,
      13,    42,    47,    48,    49,    18,    42,    42,    41,    22,
      23,    24,    25,    26,    27,    43,    43,    43,    43,    43,
      43,    43,    42,    42,    42,    13,    23,    31,    41,    41,
      18,    44,    45,    46,    22,    23,    24,    25,    26,    27,
      42,    13,    42,    24,    55,    20,    18,     4,    82,     6,
      22,    23,    81,    41,    26,    12,    71,   209,    15,    21,
      17,    92,    48,    -1,    21,    -1,    -1,    -1,    -1,    41
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    29,    36,    54,    56,    60,    64,    77,    81,    36,
      23,    34,    82,    54,    54,     0,    23,    57,     4,    41,
      41,    38,    84,     4,    38,    59,    13,    18,    22,    23,
      24,    25,    26,    27,    41,    62,    68,    73,    74,    75,
      79,    80,    83,    36,    65,    66,    66,    23,    82,    43,
      24,    25,    27,    58,    62,    57,    43,    55,    61,    62,
      71,    72,    73,    76,     5,    14,    16,    13,    22,    79,
      23,    38,    67,    42,    42,    84,    59,    42,     7,    19,
      42,     3,    20,     8,     9,    10,    11,    79,    79,    79,
      68,    68,    65,    39,    52,    52,    73,    76,    76,    61,
      72,    73,    73,    73,    73,    67,    28,    30,    32,    33,
      35,    36,    37,    43,    47,    48,    49,    51,    52,    53,
      60,    62,    70,    74,    78,    43,    43,    41,    41,    43,
      62,    41,    41,    41,    41,    43,    40,    53,    43,     4,
       6,    12,    15,    17,    21,    53,    23,    43,    51,    60,
      63,    74,    55,    43,    55,    23,    25,    26,    62,    23,
      27,    24,    25,    27,    44,    45,    46,    62,    62,    62,
      62,    62,    62,    43,    43,    55,    42,    42,    42,    42,
      42,    42,    42,    42,    41,    41,    41,    43,    78,    78,
      43,    43,    43,    43,    43,    43,    42,    42,    42,    51,
      31,    69,    42,    33,    78,    78,    41,    55,    42,    78,
      69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    53,    53,    53,    54,    54,
      54,    54,    55,    56,    57,    58,    58,    58,    58,    59,
      59,    60,    60,    61,    61,    61,    62,    63,    63,    63,
      63,    64,    64,    65,    66,    66,    67,    67,    68,    68,
      68,    68,    69,    69,    69,    70,    70,    70,    70,    70,
      70,    71,    71,    72,    72,    73,    73,    73,    74,    75,
      75,    75,    75,    76,    76,    76,    76,    76,    77,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    79,    79,    80,    80,    80,    81,    82,    82,    83,
      83,    83,    83,    84,    84
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     3,     5,     3,     5,     3,     5,     3,
       3,     3,     3,     3,     3,     2,     2,     0,     1,     2,
       1,     2,     1,     5,     3,     1,     1,     1,     1,     3,
       0,     1,     1,     3,     3,     1,     1,     2,     1,     2,
       1,     6,     6,     2,     2,     0,     3,     0,     3,     3,
       3,     1,     7,     2,     0,     5,     5,     5,     5,     5,
       5,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     1,     1,     1,     3,     3,     3,     3,     1,     2,
       1,     2,     2,     2,     8,     6,     1,     2,     3,     1,
       5,     1,     2,     1,     1,     1,     4,     1,     3,     1,
       1,     1,     1,     3,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 32 "src/main.y"
                  {
    yyvsp[-2]->bval = yyvsp[0]->bval;
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_ASS;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    node->bval = true;
    yyval = node;
}
#line 1516 "src/main.tab.cpp"
    break;

  case 3:
#line 42 "src/main.y"
                  {
    yyvsp[-2]->cval = yyvsp[0]->cval;
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_ASS;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    node->bval = true;
    yyval = node;
}
#line 1531 "src/main.tab.cpp"
    break;

  case 4:
#line 52 "src/main.y"
                                 {
    TreeNode* node = new TreeNode(yyvsp[-4]->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->addChild(yyvsp[-4]);    
    yyval = node;
}
#line 1542 "src/main.tab.cpp"
    break;

  case 5:
#line 58 "src/main.y"
                 {
    yyvsp[-2]->ival = yyvsp[0]->ival;
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_ASS;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    node->bval = true;
    yyval = node;
}
#line 1557 "src/main.tab.cpp"
    break;

  case 6:
#line 68 "src/main.y"
                                {
    TreeNode* node = new TreeNode(yyvsp[-4]->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->addChild(yyvsp[-4]);
    yyval = node;
}
#line 1568 "src/main.tab.cpp"
    break;

  case 7:
#line 74 "src/main.y"
                    {
    yyvsp[-2]->sval = yyvsp[0]->sval;
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_ASS;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    node->bval = true;
    yyval = node;
}
#line 1583 "src/main.tab.cpp"
    break;

  case 8:
#line 84 "src/main.y"
                                {
    TreeNode* node = new TreeNode(yyvsp[-4]->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->addChild(yyvsp[-4]);
    yyval = node;
}
#line 1594 "src/main.tab.cpp"
    break;

  case 9:
#line 90 "src/main.y"
                  {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_DIVE;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    node->bval = true;
    yyval = node;
}
#line 1608 "src/main.tab.cpp"
    break;

  case 10:
#line 99 "src/main.y"
                  {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_MINE;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    node->bval = true;
    yyval = node;
}
#line 1622 "src/main.tab.cpp"
    break;

  case 11:
#line 108 "src/main.y"
                  {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_MODE;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    node->bval = true;
    yyval = node;
}
#line 1636 "src/main.tab.cpp"
    break;

  case 12:
#line 117 "src/main.y"
                  {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_MULE;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    node->bval = true;
    yyval = node;
}
#line 1650 "src/main.tab.cpp"
    break;

  case 13:
#line 126 "src/main.y"
                  {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_PLUE;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    node->bval = true;
    yyval = node;
}
#line 1664 "src/main.tab.cpp"
    break;

  case 14:
#line 138 "src/main.y"
                         {
    if (yyvsp[-1] == nullptr)
        yyval = nullptr;
    else
    {
        TreeNode* node = new TreeNode(yyvsp[-1]->lineNo, NODE_STMT);
        node->stmtType = STMT_BLCK;
        node->addChild(yyvsp[-1]);
        yyval = node;
    }  
}
#line 1680 "src/main.tab.cpp"
    break;

  case 15:
#line 152 "src/main.y"
                 {
    yyvsp[-1]->addSibling(yyvsp[0]);
    yyval = yyvsp[-1];
}
#line 1689 "src/main.tab.cpp"
    break;

  case 16:
#line 156 "src/main.y"
                 {
    yyvsp[-1]->addSibling(yyvsp[0]);
    yyval = yyvsp[-1];
}
#line 1698 "src/main.tab.cpp"
    break;

  case 17:
#line 160 "src/main.y"
  {
    yyval = nullptr;
}
#line 1706 "src/main.tab.cpp"
    break;

  case 18:
#line 166 "src/main.y"
       {
    yyval = yyvsp[0];
}
#line 1714 "src/main.tab.cpp"
    break;

  case 19:
#line 169 "src/main.y"
                {
    yyvsp[-1]->addSibling(yyvsp[0]);
    yyval = yyvsp[-1];
}
#line 1723 "src/main.tab.cpp"
    break;

  case 20:
#line 173 "src/main.y"
          {
    yyval = yyvsp[0];
}
#line 1731 "src/main.tab.cpp"
    break;

  case 21:
#line 176 "src/main.y"
                   {
    yyvsp[-1]->addSibling(yyvsp[0]);
    yyval = yyvsp[-1];
}
#line 1740 "src/main.tab.cpp"
    break;

  case 22:
#line 183 "src/main.y"
         {
    yyval = yyvsp[0];
}
#line 1748 "src/main.tab.cpp"
    break;

  case 23:
#line 189 "src/main.y"
                                     {
    TreeNode* node = new TreeNode(yyvsp[-4]->lineNo, NODE_STMT);
    node->stmtType = STMT_DECL;
    node->addChild(yyvsp[-4]);
    node->addChild(yyvsp[-3]);
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[-1]);
    yyval = node;
}
#line 1762 "src/main.tab.cpp"
    break;

  case 24:
#line 201 "src/main.y"
                        {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_ASS;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    node->bval = true;
    yyval = node;
}
#line 1776 "src/main.tab.cpp"
    break;

  case 25:
#line 213 "src/main.y"
       {
    yyval = yyvsp[0];
}
#line 1784 "src/main.tab.cpp"
    break;

  case 26:
#line 216 "src/main.y"
       {
    yyval = yyvsp[0];
}
#line 1792 "src/main.tab.cpp"
    break;

  case 27:
#line 219 "src/main.y"
      {
    yyval = yyvsp[0];
}
#line 1800 "src/main.tab.cpp"
    break;

  case 28:
#line 222 "src/main.y"
         {
    yyval = yyvsp[0];
}
#line 1808 "src/main.tab.cpp"
    break;

  case 29:
#line 228 "src/main.y"
                          {
    yyvsp[-1]->addSibling(yyvsp[0]);
    yyval = yyvsp[-1];
}
#line 1817 "src/main.tab.cpp"
    break;

  case 30:
#line 232 "src/main.y"
  {
    yyval = nullptr;
}
#line 1825 "src/main.tab.cpp"
    break;

  case 31:
#line 238 "src/main.y"
            {
    yyval = yyvsp[0];
}
#line 1833 "src/main.tab.cpp"
    break;

  case 32:
#line 241 "src/main.y"
          {
    yyval = yyvsp[0];
}
#line 1841 "src/main.tab.cpp"
    break;

  case 33:
#line 247 "src/main.y"
                    {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_EQ;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 1853 "src/main.tab.cpp"
    break;

  case 34:
#line 254 "src/main.y"
                      {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_NOTE;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 1865 "src/main.tab.cpp"
    break;

  case 35:
#line 261 "src/main.y"
         {
    yyval = yyvsp[0];
}
#line 1873 "src/main.tab.cpp"
    break;

  case 36:
#line 267 "src/main.y"
         {
    yyval = yyvsp[0];
}
#line 1881 "src/main.tab.cpp"
    break;

  case 37:
#line 273 "src/main.y"
              {
    yyval = yyvsp[-1];
}
#line 1889 "src/main.tab.cpp"
    break;

  case 38:
#line 276 "src/main.y"
       {
    yyval = yyvsp[0];
}
#line 1897 "src/main.tab.cpp"
    break;

  case 39:
#line 279 "src/main.y"
          {
    yyval = yyvsp[-1];
}
#line 1905 "src/main.tab.cpp"
    break;

  case 40:
#line 282 "src/main.y"
       {
    yyval = nullptr;
}
#line 1913 "src/main.tab.cpp"
    break;

  case 41:
#line 288 "src/main.y"
                                          {
    TreeNode* node = new TreeNode(yyvsp[-5]->lineNo, NODE_PROG);
    node->addChild(yyvsp[-5]);
    node->addChild(yyvsp[-4]);
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 1926 "src/main.tab.cpp"
    break;

  case 42:
#line 296 "src/main.y"
                                        {
    TreeNode* node = new TreeNode(yyvsp[-5]->lineNo, NODE_PROG);
    node->addChild(yyvsp[-5]);
    node->addChild(yyvsp[-4]);
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 1939 "src/main.tab.cpp"
    break;

  case 43:
#line 307 "src/main.y"
          {
    TreeNode* node = new TreeNode(yyvsp[-1]->lineNo, NODE_PARM);
    node->addChild(yyvsp[-1]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 1950 "src/main.tab.cpp"
    break;

  case 44:
#line 316 "src/main.y"
                       {
    TreeNode* node = new TreeNode(yyvsp[-1]->lineNo, NODE_STMT);
    node->stmtType = STMT_PARM;
    node->addChild(yyvsp[-1]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 1962 "src/main.tab.cpp"
    break;

  case 45:
#line 323 "src/main.y"
  {
    yyval = nullptr;
}
#line 1970 "src/main.tab.cpp"
    break;

  case 46:
#line 329 "src/main.y"
                            {
    yyvsp[-1]->addSibling(yyvsp[0]);
    yyval = yyvsp[-1];
}
#line 1979 "src/main.tab.cpp"
    break;

  case 47:
#line 333 "src/main.y"
  {
    yyval = nullptr;
}
#line 1987 "src/main.tab.cpp"
    break;

  case 48:
#line 339 "src/main.y"
                         {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_DIV;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 1999 "src/main.tab.cpp"
    break;

  case 49:
#line 346 "src/main.y"
                         {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_MOD;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2011 "src/main.tab.cpp"
    break;

  case 50:
#line 353 "src/main.y"
                         {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_MUL;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2023 "src/main.tab.cpp"
    break;

  case 51:
#line 360 "src/main.y"
           {
    yyval = yyvsp[0];
}
#line 2031 "src/main.tab.cpp"
    break;

  case 52:
#line 366 "src/main.y"
                                       {
    yyvsp[-6]->addSibling(yyvsp[-5]);
    yyvsp[-6]->addSibling(yyvsp[-3]);
    yyvsp[-6]->addSibling(yyvsp[-1]);
    yyvsp[-6]->addSibling(yyvsp[0]);
    yyval = yyvsp[-6];
}
#line 2043 "src/main.tab.cpp"
    break;

  case 53:
#line 373 "src/main.y"
            {
    yyvsp[-1]->addSibling(yyvsp[0]);
    yyval = yyvsp[-1];
}
#line 2052 "src/main.tab.cpp"
    break;

  case 54:
#line 377 "src/main.y"
  {
    yyval = nullptr;
}
#line 2060 "src/main.tab.cpp"
    break;

  case 55:
#line 383 "src/main.y"
                                 {
    TreeNode* node = new TreeNode(yyvsp[-4]->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->addChild(yyvsp[-2]);
    yyval = node;
}
#line 2071 "src/main.tab.cpp"
    break;

  case 56:
#line 389 "src/main.y"
                               {
    TreeNode* node = new TreeNode(yyvsp[-4]->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->addChild(yyvsp[-2]);
    yyval = node;    
}
#line 2082 "src/main.tab.cpp"
    break;

  case 57:
#line 395 "src/main.y"
                                {
    TreeNode* node = new TreeNode(yyvsp[-4]->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->addChild(yyvsp[-2]);
    yyval = node;    
}
#line 2093 "src/main.tab.cpp"
    break;

  case 58:
#line 401 "src/main.y"
                               {
    TreeNode* node = new TreeNode(yyvsp[-4]->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->addChild(yyvsp[-2]);
    yyval = node;
}
#line 2104 "src/main.tab.cpp"
    break;

  case 59:
#line 407 "src/main.y"
                              {
    TreeNode* node = new TreeNode(yyvsp[-4]->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->addChild(yyvsp[-2]);
    yyval = node;
}
#line 2115 "src/main.tab.cpp"
    break;

  case 60:
#line 413 "src/main.y"
                                  {
    TreeNode* node = new TreeNode(yyvsp[-4]->lineNo, NODE_STMT);
    node->stmtType = STMT_IO;
    node->addChild(yyvsp[-2]);
    yyval = node;
}
#line 2126 "src/main.tab.cpp"
    break;

  case 61:
#line 422 "src/main.y"
        {
    yyval = yyvsp[0];
}
#line 2134 "src/main.tab.cpp"
    break;

  case 62:
#line 425 "src/main.y"
                      {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_AND;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2146 "src/main.tab.cpp"
    break;

  case 63:
#line 435 "src/main.y"
          {
    yyval = yyvsp[0];
}
#line 2154 "src/main.tab.cpp"
    break;

  case 64:
#line 438 "src/main.y"
                      {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_OR;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2166 "src/main.tab.cpp"
    break;

  case 65:
#line 448 "src/main.y"
          {
    yyval = yyvsp[0];
}
#line 2174 "src/main.tab.cpp"
    break;

  case 66:
#line 451 "src/main.y"
                        {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_PLUS;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2186 "src/main.tab.cpp"
    break;

  case 67:
#line 458 "src/main.y"
                        {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_MINS;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2198 "src/main.tab.cpp"
    break;

  case 68:
#line 468 "src/main.y"
     {
    yyval = yyvsp[0];
}
#line 2206 "src/main.tab.cpp"
    break;

  case 69:
#line 474 "src/main.y"
                   {
    yyval = yyvsp[-1];
}
#line 2214 "src/main.tab.cpp"
    break;

  case 70:
#line 477 "src/main.y"
                  {
    yyval = yyvsp[-1];
}
#line 2222 "src/main.tab.cpp"
    break;

  case 71:
#line 480 "src/main.y"
      {
    yyval = yyvsp[0];
}
#line 2230 "src/main.tab.cpp"
    break;

  case 72:
#line 483 "src/main.y"
       {
    yyval = yyvsp[0];
}
#line 2238 "src/main.tab.cpp"
    break;

  case 73:
#line 489 "src/main.y"
         {
    yyval = yyvsp[0];
}
#line 2246 "src/main.tab.cpp"
    break;

  case 74:
#line 492 "src/main.y"
                     {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_LA;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2258 "src/main.tab.cpp"
    break;

  case 75:
#line 499 "src/main.y"
                      {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_LAE;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2270 "src/main.tab.cpp"
    break;

  case 76:
#line 506 "src/main.y"
                     {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_LE;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2282 "src/main.tab.cpp"
    break;

  case 77:
#line 513 "src/main.y"
                      {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_EXPR);
    node->opType = OP_LEE;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2294 "src/main.tab.cpp"
    break;

  case 78:
#line 523 "src/main.y"
           {
    root = new TreeNode(0, NODE_PROG);
    root->addChild(yyvsp[0]);
}
#line 2303 "src/main.tab.cpp"
    break;

  case 79:
#line 530 "src/main.y"
              {
    yyval = yyvsp[-1];
}
#line 2311 "src/main.tab.cpp"
    break;

  case 80:
#line 533 "src/main.y"
        {
    yyval = yyvsp[0];
}
#line 2319 "src/main.tab.cpp"
    break;

  case 81:
#line 536 "src/main.y"
             {
    yyval = yyvsp[-1];
}
#line 2327 "src/main.tab.cpp"
    break;

  case 82:
#line 539 "src/main.y"
                {
    yyval = yyvsp[-1];
}
#line 2335 "src/main.tab.cpp"
    break;

  case 83:
#line 542 "src/main.y"
           {
    yyval = yyvsp[-1];
}
#line 2343 "src/main.tab.cpp"
    break;

  case 84:
#line 545 "src/main.y"
                                                {
    TreeNode* node = new TreeNode(yyvsp[-7]->lineNo, NODE_STMT);
    node->addChild(yyvsp[-7]);
    node->addChild(yyvsp[-5]);
    node->addChild(yyvsp[-4]);
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2357 "src/main.tab.cpp"
    break;

  case 85:
#line 554 "src/main.y"
                                  {
    TreeNode* node = new TreeNode(yyvsp[-5]->lineNo, NODE_STMT);
    node->addChild(yyvsp[-5]);
    node->addChild(yyvsp[-3]);
    node->addChild(yyvsp[-1]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2370 "src/main.tab.cpp"
    break;

  case 86:
#line 562 "src/main.y"
     {
    yyval = yyvsp[0];
}
#line 2378 "src/main.tab.cpp"
    break;

  case 87:
#line 565 "src/main.y"
              {
    yyval = yyvsp[-1];
}
#line 2386 "src/main.tab.cpp"
    break;

  case 88:
#line 568 "src/main.y"
                  {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_STMT);
    node->stmtType = STMT_RET;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[-1]);
    yyval = node;
}
#line 2398 "src/main.tab.cpp"
    break;

  case 89:
#line 575 "src/main.y"
       {
    yyval = nullptr;
}
#line 2406 "src/main.tab.cpp"
    break;

  case 90:
#line 578 "src/main.y"
                              {
    TreeNode* node = new TreeNode(yyvsp[-4]->lineNo, NODE_STMT);
    node->addChild(yyvsp[-4]);
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2418 "src/main.tab.cpp"
    break;

  case 91:
#line 588 "src/main.y"
             {
    yyval = yyvsp[0];
}
#line 2426 "src/main.tab.cpp"
    break;

  case 92:
#line 591 "src/main.y"
                   {
    TreeNode* node = new TreeNode(yyvsp[-1]->lineNo, NODE_EXPR);
    node->opType = yyvsp[-1]->opType;
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2437 "src/main.tab.cpp"
    break;

  case 93:
#line 600 "src/main.y"
         {
    TreeNode* node = new TreeNode(lineNo, NODE_OP);
    node->opType = OP_MINS;
    yyval = node;
}
#line 2447 "src/main.tab.cpp"
    break;

  case 94:
#line 605 "src/main.y"
        {
    TreeNode* node = new TreeNode(lineNo, NODE_OP);
    node->opType = OP_NOT;
    yyval = node;
}
#line 2457 "src/main.tab.cpp"
    break;

  case 95:
#line 610 "src/main.y"
         {
    TreeNode* node = new TreeNode(lineNo, NODE_OP);
    node->opType = OP_PLUS;
    yyval = node;  
}
#line 2467 "src/main.tab.cpp"
    break;

  case 96:
#line 618 "src/main.y"
                           {
    TreeNode* node = new TreeNode(yyvsp[-3]->lineNo, NODE_STMT);
    node->stmtType = STMT_DECL;
    node->addChild(yyvsp[-3]);
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[-1]);
    yyval = node;
}
#line 2480 "src/main.tab.cpp"
    break;

  case 97:
#line 629 "src/main.y"
     {
    yyval = yyvsp[0];
}
#line 2488 "src/main.tab.cpp"
    break;

  case 98:
#line 632 "src/main.y"
                      {
    TreeNode* node = new TreeNode(yyvsp[-2]->lineNo, NODE_STMT);
    node->stmtType = STMT_ASS;
    node->opType = OP_ASS;
    node->addChild(yyvsp[-2]);
    node->addChild(yyvsp[0]);
    yyval = node;
}
#line 2501 "src/main.tab.cpp"
    break;

  case 99:
#line 643 "src/main.y"
       {
    yyval = yyvsp[0];
}
#line 2509 "src/main.tab.cpp"
    break;

  case 100:
#line 646 "src/main.y"
       {
    yyval = yyvsp[0];
}
#line 2517 "src/main.tab.cpp"
    break;

  case 101:
#line 649 "src/main.y"
      {
    yyval = yyvsp[0];
}
#line 2525 "src/main.tab.cpp"
    break;

  case 102:
#line 652 "src/main.y"
         {
    yyval = yyvsp[0];
}
#line 2533 "src/main.tab.cpp"
    break;

  case 103:
#line 658 "src/main.y"
                      {
    yyvsp[-1]->addChild(yyvsp[0]);
    yyval = yyvsp[-1];
}
#line 2542 "src/main.tab.cpp"
    break;

  case 104:
#line 662 "src/main.y"
  {
    yyval = nullptr;
}
#line 2550 "src/main.tab.cpp"
    break;


#line 2554 "src/main.tab.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 667 "src/main.y"


int yyerror(char const* message)
{
    cout << message << " at line " << lineNo << endl;
    return -1;
}
