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
#line 1 "parser.y"

    #define YYSTYPE char*
    #include "sym_tab.c"
    #include "parser.tab.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    int temp;
    int scope=0;
    int func=0; // function 0 represents main
    int type=-1;
    char* vval="~";
    int vtype = -1;  
    int condition_result = 0;  
    double expr1_val = 0.0;    
    double expr2_val = 0.0;
    int skip_execution = 0;
    int indent_level = 0;
    int error_count = 0;
    void yyerror(char* s);
    int yylex();
    int yydebug=1;
    extern int yylineno;
    symbol *global_p = NULL; 
    FILE *fp;
    
    // Print node in AST with proper indentation
    void print_ast(const char* node_type, const char* value) {
        for (int i = 0; i < indent_level; i++) {
            fprintf(fp, "  ");
        }
        fprintf(fp, "└─ %s", node_type);
        if (value != NULL) {
            fprintf(fp, ": %s", value);
        }
        fprintf(fp, "\n");
    }

    // Increase tree depth
    void increase_indent() {
        indent_level++;
    }

    // Decrease tree depth
    void decrease_indent() {
        if (indent_level > 0) {
            indent_level--;
        }
    }

#line 123 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_INT = 3,                      /* T_INT  */
  YYSYMBOL_T_CHAR = 4,                     /* T_CHAR  */
  YYSYMBOL_T_DOUBLE = 5,                   /* T_DOUBLE  */
  YYSYMBOL_T_WHILE = 6,                    /* T_WHILE  */
  YYSYMBOL_T_INC = 7,                      /* T_INC  */
  YYSYMBOL_T_DEC = 8,                      /* T_DEC  */
  YYSYMBOL_T_OROR = 9,                     /* T_OROR  */
  YYSYMBOL_T_ANDAND = 10,                  /* T_ANDAND  */
  YYSYMBOL_T_EQCOMP = 11,                  /* T_EQCOMP  */
  YYSYMBOL_T_NOTEQUAL = 12,                /* T_NOTEQUAL  */
  YYSYMBOL_T_GREATEREQ = 13,               /* T_GREATEREQ  */
  YYSYMBOL_T_LESSEREQ = 14,                /* T_LESSEREQ  */
  YYSYMBOL_T_LEFTSHIFT = 15,               /* T_LEFTSHIFT  */
  YYSYMBOL_T_RIGHTSHIFT = 16,              /* T_RIGHTSHIFT  */
  YYSYMBOL_T_PRINTLN = 17,                 /* T_PRINTLN  */
  YYSYMBOL_T_STRING = 18,                  /* T_STRING  */
  YYSYMBOL_T_FLOAT = 19,                   /* T_FLOAT  */
  YYSYMBOL_T_BOOLEAN = 20,                 /* T_BOOLEAN  */
  YYSYMBOL_T_IF = 21,                      /* T_IF  */
  YYSYMBOL_T_ELSE = 22,                    /* T_ELSE  */
  YYSYMBOL_T_STRLITERAL = 23,              /* T_STRLITERAL  */
  YYSYMBOL_T_DO = 24,                      /* T_DO  */
  YYSYMBOL_T_INCLUDE = 25,                 /* T_INCLUDE  */
  YYSYMBOL_T_HEADER = 26,                  /* T_HEADER  */
  YYSYMBOL_T_MAIN = 27,                    /* T_MAIN  */
  YYSYMBOL_T_ID = 28,                      /* T_ID  */
  YYSYMBOL_T_NUM = 29,                     /* T_NUM  */
  YYSYMBOL_T_FOR = 30,                     /* T_FOR  */
  YYSYMBOL_31_ = 31,                       /* ';'  */
  YYSYMBOL_32_ = 32,                       /* ','  */
  YYSYMBOL_33_ = 33,                       /* '='  */
  YYSYMBOL_34_ = 34,                       /* '['  */
  YYSYMBOL_35_ = 35,                       /* ']'  */
  YYSYMBOL_36_ = 36,                       /* '{'  */
  YYSYMBOL_37_ = 37,                       /* '}'  */
  YYSYMBOL_38_ = 38,                       /* '+'  */
  YYSYMBOL_39_ = 39,                       /* '-'  */
  YYSYMBOL_40_ = 40,                       /* '*'  */
  YYSYMBOL_41_ = 41,                       /* '/'  */
  YYSYMBOL_42_ = 42,                       /* '('  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_44_ = 44,                       /* '<'  */
  YYSYMBOL_45_ = 45,                       /* '>'  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_START = 47,                     /* START  */
  YYSYMBOL_FUNC_DEF = 48,                  /* FUNC_DEF  */
  YYSYMBOL_PROG = 49,                      /* PROG  */
  YYSYMBOL_DECLR = 50,                     /* DECLR  */
  YYSYMBOL_LISTVAR = 51,                   /* LISTVAR  */
  YYSYMBOL_VAR = 52,                       /* VAR  */
  YYSYMBOL_ARRAY_DECL = 53,                /* ARRAY_DECL  */
  YYSYMBOL_ARRAY_DIM = 54,                 /* ARRAY_DIM  */
  YYSYMBOL_ARRAY_INIT = 55,                /* ARRAY_INIT  */
  YYSYMBOL_ARRAY_LIST = 56,                /* ARRAY_LIST  */
  YYSYMBOL_TYPE = 57,                      /* TYPE  */
  YYSYMBOL_ASSGN = 58,                     /* ASSGN  */
  YYSYMBOL_59_1 = 59,                      /* $@1  */
  YYSYMBOL_EXPR = 60,                      /* EXPR  */
  YYSYMBOL_E = 61,                         /* E  */
  YYSYMBOL_T = 62,                         /* T  */
  YYSYMBOL_F = 63,                         /* F  */
  YYSYMBOL_INCREMENT = 64,                 /* INCREMENT  */
  YYSYMBOL_REL_OP = 65,                    /* REL_OP  */
  YYSYMBOL_MAIN = 66,                      /* MAIN  */
  YYSYMBOL_67_2 = 67,                      /* $@2  */
  YYSYMBOL_68_3 = 68,                      /* $@3  */
  YYSYMBOL_FUNC = 69,                      /* FUNC  */
  YYSYMBOL_70_4 = 70,                      /* $@4  */
  YYSYMBOL_71_5 = 71,                      /* $@5  */
  YYSYMBOL_EMPTY_LISTVAR = 72,             /* EMPTY_LISTVAR  */
  YYSYMBOL_STMT = 73,                      /* STMT  */
  YYSYMBOL_STMT_NO_BLOCK = 74,             /* STMT_NO_BLOCK  */
  YYSYMBOL_IF_STMT = 75,                   /* IF_STMT  */
  YYSYMBOL_76_6 = 76,                      /* $@6  */
  YYSYMBOL_77_7 = 77,                      /* $@7  */
  YYSYMBOL_ELSE_PART = 78,                 /* ELSE_PART  */
  YYSYMBOL_79_8 = 79,                      /* $@8  */
  YYSYMBOL_LOOP_STMT = 80,                 /* LOOP_STMT  */
  YYSYMBOL_WHILE_LOOP = 81,                /* WHILE_LOOP  */
  YYSYMBOL_82_9 = 82,                      /* $@9  */
  YYSYMBOL_DO_WHILE_LOOP = 83,             /* DO_WHILE_LOOP  */
  YYSYMBOL_84_10 = 84,                     /* $@10  */
  YYSYMBOL_FOR_LOOP = 85,                  /* FOR_LOOP  */
  YYSYMBOL_86_11 = 86,                     /* $@11  */
  YYSYMBOL_FOR_INIT = 87,                  /* FOR_INIT  */
  YYSYMBOL_FOR_UPDATE = 88,                /* FOR_UPDATE  */
  YYSYMBOL_BLOCK = 89,                     /* BLOCK  */
  YYSYMBOL_90_12 = 90,                     /* $@12  */
  YYSYMBOL_COND = 91                       /* COND  */
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
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   211

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  172

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


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
      42,    43,    40,    38,    32,    39,     2,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
      44,    33,    45,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    59,    59,    67,    73,    81,    86,    91,    96,   100,
     103,   110,   115,   122,   137,   147,   167,   172,   177,   184,
     189,   199,   206,   211,   218,   224,   230,   236,   244,   244,
     268,   291,   317,   326,   341,   356,   359,   374,   389,   392,
     398,   418,   434,   445,   452,   477,   502,   527,   554,   558,
     562,   566,   570,   574,   580,   584,   580,   591,   595,   591,
     601,   606,   611,   612,   613,   614,   617,   622,   627,   632,
     638,   646,   638,   651,   651,   661,   666,   671,   676,   683,
     683,   696,   696,   705,   705,   718,   723,   728,   733,   738,
     743,   748,   748,   758,   763
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
  "\"end of file\"", "error", "\"invalid token\"", "T_INT", "T_CHAR",
  "T_DOUBLE", "T_WHILE", "T_INC", "T_DEC", "T_OROR", "T_ANDAND",
  "T_EQCOMP", "T_NOTEQUAL", "T_GREATEREQ", "T_LESSEREQ", "T_LEFTSHIFT",
  "T_RIGHTSHIFT", "T_PRINTLN", "T_STRING", "T_FLOAT", "T_BOOLEAN", "T_IF",
  "T_ELSE", "T_STRLITERAL", "T_DO", "T_INCLUDE", "T_HEADER", "T_MAIN",
  "T_ID", "T_NUM", "T_FOR", "';'", "','", "'='", "'['", "']'", "'{'",
  "'}'", "'+'", "'-'", "'*'", "'/'", "'('", "')'", "'<'", "'>'", "$accept",
  "START", "FUNC_DEF", "PROG", "DECLR", "LISTVAR", "VAR", "ARRAY_DECL",
  "ARRAY_DIM", "ARRAY_INIT", "ARRAY_LIST", "TYPE", "ASSGN", "$@1", "EXPR",
  "E", "T", "F", "INCREMENT", "REL_OP", "MAIN", "$@2", "$@3", "FUNC",
  "$@4", "$@5", "EMPTY_LISTVAR", "STMT", "STMT_NO_BLOCK", "IF_STMT", "$@6",
  "$@7", "ELSE_PART", "$@8", "LOOP_STMT", "WHILE_LOOP", "$@9",
  "DO_WHILE_LOOP", "$@10", "FOR_LOOP", "$@11", "FOR_INIT", "FOR_UPDATE",
  "BLOCK", "$@12", "COND", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-119)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-66)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     110,   -27,  -119,  -119,  -119,  -119,   -20,    22,   110,  -119,
     -24,    13,    16,  -119,  -119,   110,    41,    20,  -119,  -119,
     110,    14,     9,    43,  -119,   110,  -119,    58,    84,  -119,
      77,  -119,    41,    83,    50,    68,  -119,  -119,    41,  -119,
    -119,    37,    53,  -119,  -119,    88,  -119,   105,  -119,  -119,
    -119,  -119,  -119,    87,  -119,  -119,  -119,  -119,   106,  -119,
    -119,    41,    41,    41,    41,    41,    91,   105,    41,    91,
     112,   105,   114,  -119,    57,  -119,  -119,    41,    50,    68,
      68,  -119,  -119,    43,   111,    25,    91,   122,   115,    91,
     119,    41,  -119,  -119,   123,  -119,    91,  -119,    31,    31,
     129,   124,   125,  -119,   127,  -119,   130,   105,   132,   128,
      31,  -119,    31,  -119,  -119,  -119,    31,   131,  -119,    64,
      64,   134,   121,    31,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,     5,  -119,    91,   133,   135,   158,  -119,  -119,   140,
     136,  -119,  -119,   138,    64,  -119,   134,   139,    64,   141,
    -119,    31,   142,     3,   144,   143,    73,  -119,  -119,   145,
    -119,  -119,  -119,   155,   134,  -119,  -119,  -119,   146,    31,
     147,  -119
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    24,    27,    26,    25,    28,     0,     0,     2,
       0,     0,     0,     3,     4,     0,     0,     0,     1,     5,
       0,     0,    14,    10,    12,     0,     8,     0,     0,    42,
      40,    41,     0,     0,    32,    35,    38,    43,     0,     6,
      54,     0,     0,    57,    15,    17,    18,     0,     7,    44,
      45,    46,    47,     0,    52,    53,    49,    48,     0,    50,
      51,     0,     0,     0,     0,     0,    29,    61,     0,    13,
       0,    61,     0,    16,    14,    11,    39,     0,    31,    33,
      34,    36,    37,    60,     0,     0,    23,    20,     0,    30,
       0,     0,    21,    19,     0,    55,    22,    58,     0,     0,
       0,     0,     0,    81,     0,    91,     0,     0,     0,     0,
       0,    68,     0,    76,    77,    78,     0,     0,    69,     0,
       0,     0,    87,     0,    66,    67,    56,    62,    64,    63,
      59,    40,    94,    93,     0,     0,     0,    85,    86,     0,
       0,    79,    70,     0,     0,    92,     0,     0,     0,     0,
      80,     0,     0,    90,     0,     0,    28,    89,    88,     0,
      71,    82,    83,    75,     0,    73,    72,    84,     0,     0,
       0,    74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -119,  -119,  -119,   126,     1,     7,   148,  -119,    92,   149,
    -119,   137,     0,  -119,   -14,   150,    54,    78,    30,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,   116,   -93,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,  -119,  -119,  -118,  -119,  -115
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     7,     8,     9,   106,    23,    24,    44,    45,    46,
      85,   107,   108,    17,   133,    34,    35,    36,    37,    61,
      13,    67,    98,    14,    71,    99,    84,   109,   110,   111,
     147,   163,   166,   168,   112,   113,   146,   114,   121,   115,
     164,   139,   159,   116,   123,   134
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      12,    10,    33,   136,    15,   135,   117,    20,    12,    10,
      27,    28,    51,    52,    16,    12,    10,   127,    53,   128,
      12,    10,    18,   129,    66,    12,    10,    69,   150,   149,
     140,   156,   100,   152,     2,     3,     4,   101,   -28,    16,
      21,    22,    41,    42,    27,    28,   167,    25,    27,    28,
       5,    43,   102,    38,    86,   103,    40,    91,   154,     6,
      29,   104,    92,    89,    29,    30,    31,   105,   -65,    30,
      31,    27,    28,    68,    83,    47,   170,    96,    83,    32,
      51,    52,    70,    32,    51,    52,    49,    29,    62,    63,
      41,    42,   131,    31,    54,    55,    56,    57,    54,    55,
      56,    57,    54,    55,    56,    57,    32,    16,    64,    65,
      -9,     1,    50,     2,     3,     4,    79,    80,    58,   132,
     132,    72,   138,   137,     2,     3,     4,    59,    60,     5,
      76,    59,    60,    74,    19,    59,    60,    11,     6,    77,
       5,    26,    81,    82,   132,    11,    39,    87,   132,     6,
      68,    48,    11,   157,    90,    95,    42,    11,    94,    97,
     118,   124,    11,   125,   143,   126,   119,   120,   130,   122,
     105,   144,   153,   145,   161,   151,   141,   165,   142,    93,
     148,   160,   169,   158,   171,   155,     0,    88,   162,     0,
       0,     0,     0,     0,    73,    75,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78
};

static const yytype_int16 yycheck[] =
{
       0,     0,    16,   121,    31,   120,    99,    31,     8,     8,
       7,     8,     7,     8,    34,    15,    15,   110,    32,   112,
      20,    20,     0,   116,    38,    25,    25,    41,   146,   144,
     123,    28,     1,   148,     3,     4,     5,     6,    33,    34,
      27,    28,    33,    34,     7,     8,   164,    31,     7,     8,
      19,    42,    21,    33,    68,    24,    42,    32,   151,    28,
      23,    30,    37,    77,    23,    28,    29,    36,    37,    28,
      29,     7,     8,    36,    67,    32,   169,    91,    71,    42,
       7,     8,    29,    42,     7,     8,    28,    23,    38,    39,
      33,    34,    28,    29,    11,    12,    13,    14,    11,    12,
      13,    14,    11,    12,    13,    14,    42,    34,    40,    41,
       0,     1,    28,     3,     4,     5,    62,    63,    35,   119,
     120,    33,   122,   122,     3,     4,     5,    44,    45,    19,
      43,    44,    45,    28,     8,    44,    45,     0,    28,    33,
      19,    15,    64,    65,   144,     8,    20,    35,   148,    28,
      36,    25,    15,   153,    43,    36,    34,    20,    43,    36,
      31,    31,    25,    31,     6,    37,    42,    42,    37,    42,
      36,    31,    31,    37,    31,    36,    43,    22,    43,    87,
      42,    37,    36,   153,    37,    43,    -1,    71,    43,    -1,
      -1,    -1,    -1,    -1,    45,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,     4,     5,    19,    28,    47,    48,    49,
      50,    57,    58,    66,    69,    31,    34,    59,     0,    49,
      31,    27,    28,    51,    52,    31,    49,     7,     8,    23,
      28,    29,    42,    60,    61,    62,    63,    64,    33,    49,
      42,    33,    34,    42,    53,    54,    55,    32,    49,    28,
      28,     7,     8,    60,    11,    12,    13,    14,    35,    44,
      45,    65,    38,    39,    40,    41,    60,    67,    36,    60,
      29,    70,    33,    55,    28,    52,    43,    33,    61,    62,
      62,    63,    63,    51,    72,    56,    60,    35,    72,    60,
      43,    32,    37,    54,    43,    36,    60,    36,    68,    71,
       1,     6,    21,    24,    30,    36,    50,    57,    58,    73,
      74,    75,    80,    81,    83,    85,    89,    73,    31,    42,
      42,    84,    42,    90,    31,    31,    37,    73,    73,    73,
      37,    28,    58,    60,    91,    91,    89,    50,    58,    87,
      73,    43,    43,     6,    31,    37,    82,    76,    42,    91,
      89,    36,    91,    31,    73,    43,    28,    58,    64,    88,
      37,    31,    43,    77,    86,    22,    78,    89,    79,    36,
      73,    37
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    49,    49,
      50,    51,    51,    52,    52,    52,    53,    53,    53,    54,
      54,    55,    56,    56,    57,    57,    57,    57,    59,    58,
      58,    60,    60,    61,    61,    61,    62,    62,    62,    63,
      63,    63,    63,    63,    64,    64,    64,    64,    65,    65,
      65,    65,    65,    65,    67,    68,    66,    70,    71,    69,
      72,    72,    73,    73,    73,    73,    74,    74,    74,    74,
      76,    77,    75,    79,    78,    78,    80,    80,    80,    82,
      81,    84,    83,    86,    85,    87,    87,    87,    88,    88,
      88,    90,    89,    91,    91
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     3,     3,     3,     0,
       2,     3,     1,     3,     1,     2,     2,     1,     1,     4,
       3,     4,     3,     1,     1,     1,     1,     1,     0,     4,
       6,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       1,     1,     1,     1,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     0,     0,    10,     0,     0,    10,
       1,     0,     2,     2,     2,     0,     2,     2,     1,     2,
       0,     0,    10,     0,     5,     0,     1,     1,     1,     0,
       6,     0,     8,     0,    10,     1,     1,     0,     1,     1,
       0,     0,     4,     1,     1
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
  case 2: /* START: PROG  */
#line 59 "parser.y"
             { 
          print_ast("PROGRAM", NULL); 
          printf("Valid syntax\n"); 
          YYACCEPT; 
      }
#line 1334 "parser.tab.c"
    break;

  case 3: /* FUNC_DEF: MAIN  */
#line 67 "parser.y"
               {
           print_ast("FUNCTION_DEFINITION", "main");
           fprintf(fp,"\n");
           increase_indent();
           decrease_indent();
         }
#line 1345 "parser.tab.c"
    break;

  case 4: /* FUNC_DEF: FUNC  */
#line 73 "parser.y"
               {
           print_ast("FUNCTION_DEFINITION", "user_defined");
           fprintf(fp,"\n");
           increase_indent();
           decrease_indent();
         }
#line 1356 "parser.tab.c"
    break;

  case 5: /* PROG: FUNC_DEF PROG  */
#line 81 "parser.y"
                     {
         print_ast("PROGRAM_ELEMENT", "function");
         increase_indent();
         decrease_indent();
       }
#line 1366 "parser.tab.c"
    break;

  case 6: /* PROG: DECLR ';' PROG  */
#line 86 "parser.y"
                      {
         print_ast("PROGRAM_ELEMENT", "declaration");
         increase_indent();
         decrease_indent();
       }
#line 1376 "parser.tab.c"
    break;

  case 7: /* PROG: ASSGN ';' PROG  */
#line 91 "parser.y"
                      {
         print_ast("PROGRAM_ELEMENT", "assignment");
         increase_indent();
         decrease_indent();
       }
#line 1386 "parser.tab.c"
    break;

  case 8: /* PROG: error ';' PROG  */
#line 96 "parser.y"
                      {
         print_ast("ERROR", "invalid_statement");
         error_count++;
       }
#line 1395 "parser.tab.c"
    break;

  case 10: /* DECLR: TYPE LISTVAR  */
#line 103 "parser.y"
                     {
          print_ast("DECLARATION", NULL);
          increase_indent();
          decrease_indent();
        }
#line 1405 "parser.tab.c"
    break;

  case 11: /* LISTVAR: LISTVAR ',' VAR  */
#line 110 "parser.y"
                          {
            print_ast("VARIABLE_LIST", "multiple_vars");
            increase_indent();
            decrease_indent();
          }
#line 1415 "parser.tab.c"
    break;

  case 12: /* LISTVAR: VAR  */
#line 115 "parser.y"
              {
            print_ast("VARIABLE_LIST", "single_var");
            increase_indent();
            decrease_indent();
          }
#line 1425 "parser.tab.c"
    break;

  case 13: /* VAR: T_ID '=' EXPR  */
#line 122 "parser.y"
                    {
        print_ast("VARIABLE_INIT", yyvsp[-2]);
        increase_indent();
        decrease_indent();
        if(!skip_execution) {
            if(check_symbol_table(yyvsp[-2],scope,func))  
                yyerror(yyvsp[-2]);
            else {
                insert_into_table(yyvsp[-2],type,yylineno,scope,func);
                insert_value_to_name(yyvsp[-2],vval,scope,func);
                type=-1;
                vval="~";
            }
        }
    }
#line 1445 "parser.tab.c"
    break;

  case 14: /* VAR: T_ID  */
#line 137 "parser.y"
           {
        print_ast("VARIABLE_DECL", yyvsp[0]);
        increase_indent();
        decrease_indent();
        if(!skip_execution) {
            if(check_symbol_table(yyvsp[0],scope,func))
                yyerror(yyvsp[0]);
            insert_into_table(yyvsp[0],type,yylineno,scope,func);
        }
    }
#line 1460 "parser.tab.c"
    break;

  case 15: /* VAR: T_ID ARRAY_DECL  */
#line 147 "parser.y"
                      {
        print_ast("ARRAY_DECL", yyvsp[-1]);
        increase_indent();
        decrease_indent();
        if(!skip_execution) {
            if(check_symbol_table(yyvsp[-1],scope,func))  
                yyerror(yyvsp[-1]);
            else {
                insert_into_table(yyvsp[-1], type, yylineno, scope,func);
                symbol *s = get_symbol(yyvsp[-1], scope,func);
                if (strcmp(vval, "~") != 0) {
                    insert_value_to_name(yyvsp[-1], vval, scope,func);
                }
                type = -1;
                vval = "~";
            }
        }
    }
#line 1483 "parser.tab.c"
    break;

  case 16: /* ARRAY_DECL: ARRAY_DIM ARRAY_INIT  */
#line 167 "parser.y"
                                  {
               print_ast("ARRAY_DECLARATION", "with_init");
               increase_indent();
               decrease_indent();
             }
#line 1493 "parser.tab.c"
    break;

  case 17: /* ARRAY_DECL: ARRAY_DIM  */
#line 172 "parser.y"
                       {
               print_ast("ARRAY_DECLARATION", "dimensions_only");
               increase_indent();
               decrease_indent();
             }
#line 1503 "parser.tab.c"
    break;

  case 18: /* ARRAY_DECL: ARRAY_INIT  */
#line 177 "parser.y"
                        {
               print_ast("ARRAY_DECLARATION", "init_only");
               increase_indent();
               decrease_indent();
             }
#line 1513 "parser.tab.c"
    break;

  case 19: /* ARRAY_DIM: '[' T_NUM ']' ARRAY_DIM  */
#line 184 "parser.y"
                                    {
              print_ast("ARRAY_DIMENSION", yyvsp[-2]);
              increase_indent();
              decrease_indent();
            }
#line 1523 "parser.tab.c"
    break;

  case 20: /* ARRAY_DIM: '[' T_NUM ']'  */
#line 189 "parser.y"
                          { 
              print_ast("ARRAY_DIMENSION", yyvsp[-1]);
              increase_indent();
              decrease_indent();
              char str[32];
              sprintf(str, "%d", atoi(yyvsp[-1]));
              yyval = strdup(str);
            }
#line 1536 "parser.tab.c"
    break;

  case 21: /* ARRAY_INIT: '=' '{' ARRAY_LIST '}'  */
#line 199 "parser.y"
                                    {
               print_ast("ARRAY_INITIALIZER", NULL);
               increase_indent();
               decrease_indent();
             }
#line 1546 "parser.tab.c"
    break;

  case 22: /* ARRAY_LIST: ARRAY_LIST ',' EXPR  */
#line 206 "parser.y"
                                 {
               print_ast("ARRAY_ELEMENT", NULL);
               increase_indent();
               decrease_indent();
             }
#line 1556 "parser.tab.c"
    break;

  case 23: /* ARRAY_LIST: EXPR  */
#line 211 "parser.y"
                  {
               print_ast("ARRAY_ELEMENT", NULL);
               increase_indent();
               decrease_indent();
             }
#line 1566 "parser.tab.c"
    break;

  case 24: /* TYPE: T_INT  */
#line 218 "parser.y"
             {
         type=INT;
         print_ast("TYPE", "int");
         increase_indent();
         decrease_indent();
       }
#line 1577 "parser.tab.c"
    break;

  case 25: /* TYPE: T_FLOAT  */
#line 224 "parser.y"
               {
         type=FLOAT;
         print_ast("TYPE", "float");
         increase_indent();
         decrease_indent();
       }
#line 1588 "parser.tab.c"
    break;

  case 26: /* TYPE: T_DOUBLE  */
#line 230 "parser.y"
                {
         type=DOUBLE;
         print_ast("TYPE", "double");
         increase_indent();
         decrease_indent();
       }
#line 1599 "parser.tab.c"
    break;

  case 27: /* TYPE: T_CHAR  */
#line 236 "parser.y"
              {
         type=CHAR;
         print_ast("TYPE", "char");
         increase_indent();
         decrease_indent();
       }
#line 1610 "parser.tab.c"
    break;

  case 28: /* $@1: %empty  */
#line 244 "parser.y"
             { 
            print_ast("ASSIGNMENT", yyvsp[0]);
            increase_indent();
            if(!skip_execution) {  
                global_p = get_symbol(yyvsp[0], scope,func);
                type = global_p == NULL ? -1 : global_p->type;
            }
        }
#line 1623 "parser.tab.c"
    break;

  case 29: /* ASSGN: T_ID $@1 '=' EXPR  */
#line 251 "parser.y"
                   {
            if(!skip_execution) {  
                if(global_p == NULL) 
                    yyerror(yyvsp[-3]);
                else if(vtype != type && !(vtype == DOUBLE && type == FLOAT) && !(vtype == FLOAT && type == DOUBLE)) {
                    fprintf(stderr, "Type mismatch: Cannot assign type %d to type %d\n", vtype, type);
                    yyerror(yyvsp[-3]);
                }
                else {
                    insert_value_to_symbol(global_p, vval);
                }
                vval = "~";
                type = -1;
                global_p = NULL;
            }
            decrease_indent();
        }
#line 1645 "parser.tab.c"
    break;

  case 30: /* ASSGN: T_ID '[' EXPR ']' '=' EXPR  */
#line 268 "parser.y"
                                 {
            print_ast("ARRAY_ASSIGNMENT", yyvsp[-5]);
            increase_indent();
            if(!skip_execution) {
                symbol *s = get_symbol(yyvsp[-5], scope,func);
                if(s == NULL) {
                    fprintf(stderr, "%s is not declared\n", yyvsp[-5]);
                    yyerror(yyvsp[-5]);
                }
                else {
                    // Handle array assignment
                    char index_str[32];
                    sprintf(index_str, "[%s]", yyvsp[-3]);
                    char *new_val = malloc(strlen(s->val) + strlen(index_str) + strlen(yyvsp[0]) + 1);
                    sprintf(new_val, "%s%s=%s", s->val, index_str, yyvsp[0]);
                    insert_value_to_symbol(s, new_val);
                    free(new_val);
                }
            }
            decrease_indent();
        }
#line 1671 "parser.tab.c"
    break;

  case 31: /* EXPR: EXPR REL_OP E  */
#line 291 "parser.y"
                     {
        print_ast("RELATIONAL_EXPRESSION", yyvsp[-1]);
        increase_indent();
        expr2_val = atof(yyvsp[0]);
        switch(yyvsp[-1][0]) {
            case '<':
                if (strlen(yyvsp[-1]) == 2)
                    condition_result = (expr1_val <= expr2_val);
                else
                    condition_result = (expr1_val < expr2_val);
                break;
            case '>':
                if (strlen(yyvsp[-1]) == 2)
                    condition_result = (expr1_val >= expr2_val);
                else
                    condition_result = (expr1_val > expr2_val);
                break;
            case '=':
                condition_result = (expr1_val == expr2_val);
                break;
            case '!':
                condition_result = (expr1_val != expr2_val);
                break;
        }
        decrease_indent();
    }
#line 1702 "parser.tab.c"
    break;

  case 32: /* EXPR: E  */
#line 317 "parser.y"
        {
        print_ast("EXPRESSION", yyvsp[0]);
        increase_indent();
        decrease_indent();
        vval = yyvsp[0];
        expr1_val = atof(yyvsp[0]);
    }
#line 1714 "parser.tab.c"
    break;

  case 33: /* E: E '+' T  */
#line 326 "parser.y"
            { 
         print_ast("ADD_EXPRESSION", "+");
         increase_indent();
         if ( vtype == INT ) {
                sprintf( yyval, "%d", ( atoi( yyvsp[-2] ) + atoi( yyvsp[0] ) ) );
            } else if ( vtype == FLOAT || vtype == DOUBLE ) {
                sprintf( yyval, "%lf", ( atof( yyvsp[-2] ) + atof( yyvsp[0] ) ) );
            } else {
                fprintf( stderr, "Operation %s not supported for type %d",
                         yyvsp[-1], vtype );
                yyerror( yyval );
                yyval = "~";
            }
         decrease_indent();
        }
#line 1734 "parser.tab.c"
    break;

  case 34: /* E: E '-' T  */
#line 341 "parser.y"
            {  
            print_ast("SUB_EXPRESSION", "-");
            increase_indent();
            if ( vtype == INT ) {
                sprintf( yyval, "%d", ( atoi( yyvsp[-2] ) - atoi( yyvsp[0] ) ) );
            } else if ( vtype == FLOAT || vtype == DOUBLE ) {
                sprintf( yyval, "%lf", ( atof( yyvsp[-2] ) - atof( yyvsp[0] ) ) );
            } else {
                fprintf( stderr, "Operation %s not supported for type %d",
                         yyvsp[-1], vtype );
                yyerror( yyval );
                yyval = "~";
            }
            decrease_indent();
        }
#line 1754 "parser.tab.c"
    break;

  case 35: /* E: T  */
#line 356 "parser.y"
      {yyval=yyvsp[0];}
#line 1760 "parser.tab.c"
    break;

  case 36: /* T: T '*' F  */
#line 359 "parser.y"
            { 
                 print_ast("MUL_EXPRESSION", "*");
                 increase_indent();
                 if ( vtype == INT ) {
                    sprintf( yyval, "%d", ( atoi( yyvsp[-2] ) * atoi( yyvsp[0] ) ) );
                } else if ( vtype == FLOAT || vtype == DOUBLE ) {
                    sprintf( yyval, "%lf", ( atof( yyvsp[-2] ) * atof( yyvsp[0] ) ) );
                } else {
                    fprintf( stderr, "Operation %s not supported for type %d",
                             yyvsp[-1], vtype );
                    yyerror( yyval );
                    yyval = "~";
                }
                 decrease_indent();
            }
#line 1780 "parser.tab.c"
    break;

  case 37: /* T: T '/' F  */
#line 374 "parser.y"
            {  
                print_ast("DIV_EXPRESSION", "/");
                increase_indent();
                if ( vtype == INT ) {
                    sprintf( yyval, "%d", ( atoi( yyvsp[-2] ) / atoi( yyvsp[0] ) ) );
                } else if ( vtype == FLOAT || vtype == DOUBLE ) {
                    sprintf( yyval, "%lf", ( atof( yyvsp[-2] ) / atof( yyvsp[0] ) ) );
                } else {
                    fprintf( stderr, "Operation %s not supported for type %d",
                             yyvsp[-1], vtype );
                    yyerror( yyval );
                    yyval = "~";
                }
                decrease_indent();
            }
#line 1800 "parser.tab.c"
    break;

  case 38: /* T: F  */
#line 389 "parser.y"
      {yyval=yyvsp[0];}
#line 1806 "parser.tab.c"
    break;

  case 39: /* F: '(' EXPR ')'  */
#line 392 "parser.y"
                 {
      print_ast("PARENTHESIZED_EXPR", NULL);
      increase_indent();
      yyval = yyvsp[-1];
      decrease_indent();
    }
#line 1817 "parser.tab.c"
    break;

  case 40: /* F: T_ID  */
#line 398 "parser.y"
         {
            print_ast("IDENTIFIER", yyvsp[0]);
            increase_indent();
            symbol *s=get_symbol(yyvsp[0],scope,func);
            if(s==NULL) {
                fprintf(stderr,"%s is not declared\n",yyvsp[0]);
                yyerror(yyvsp[0]);
            }
            if(!strcmp(s->val,"~")) {
                fprintf(stderr,"%s is not initialized\n",yyvsp[0]);
                yyerror(yyvsp[0]);
            }
            yyval=strdup(s->val);
            vtype=s->type;
            if(vtype!=type&&type!=-1) {
                fprintf(stderr,"Cannot assign type %d to type %d\n",vtype,type);
                yyerror(yyvsp[0]);
            }
            decrease_indent();
         }
#line 1842 "parser.tab.c"
    break;

  case 41: /* F: T_NUM  */
#line 418 "parser.y"
          {
        print_ast("LITERAL", yyvsp[0]);
        increase_indent();
        if(!skip_execution) {
            yyval=strdup(yyvsp[0]);
            vtype=get_type(yyvsp[0]);
            if(vtype!=type && type!=-1 && !(vtype==DOUBLE && type==FLOAT) && !(vtype==FLOAT && type==DOUBLE)) {
                fprintf(stderr,"Cannot assign type %d to type %d\n", vtype, type );
                yyerror( yyvsp[0] );
            }
	   if(type == -1) {
                condition_result = (atof(yyvsp[0]) != 0);
            }
        }
        decrease_indent();
    }
#line 1863 "parser.tab.c"
    break;

  case 42: /* F: T_STRLITERAL  */
#line 434 "parser.y"
                 {
                    print_ast("STRING_LITERAL", yyvsp[0]);
                    increase_indent();
                    yyval=strdup(yyvsp[0]);
                    vtype=1;
                    if(vtype!=type) {
                        fprintf(stderr,"Cannot assign char * to type %d\n",type);
                        yyerror( yyvsp[0] );
                    }
                    decrease_indent();
                 }
#line 1879 "parser.tab.c"
    break;

  case 43: /* F: INCREMENT  */
#line 445 "parser.y"
              {
      print_ast("INCREMENT_EXPR", NULL);
      increase_indent();
      decrease_indent();
    }
#line 1889 "parser.tab.c"
    break;

  case 44: /* INCREMENT: T_INC T_ID  */
#line 452 "parser.y"
                       {
                print_ast("PRE_INCREMENT", yyvsp[0]);
                increase_indent();
                symbol *s=get_symbol(yyvsp[0],scope,func);
                if(s==NULL) {
                    fprintf(stderr,"%s is not declared\n",yyvsp[0]);
                    yyerror(yyvsp[0]);
                }
                if(!strcmp(s->val,"~")) {
                    fprintf(stderr,"%s is not initialized\n",yyvsp[0]);
                    yyerror(yyvsp[0]);
                }
                char new_value[32];
                if(s->type==INT) {
                    int val = atoi(s->val) + 1;
                    sprintf(new_value,"%d",val);
                } else if(s->type==FLOAT || s->type==DOUBLE) {
                    double val = atof(s->val) + 1.0;
                    sprintf(new_value,"%lf",val);
                }
                insert_value_to_symbol(s,new_value);
                yyval=strdup(new_value);
                vtype=s->type;
                decrease_indent();
            }
#line 1919 "parser.tab.c"
    break;

  case 45: /* INCREMENT: T_DEC T_ID  */
#line 477 "parser.y"
               {
                print_ast("PRE_DECREMENT", yyvsp[0]);
                increase_indent();
                symbol *s=get_symbol(yyvsp[0],scope,func);
                if(s==NULL) {
                    fprintf(stderr,"%s is not declared\n",yyvsp[0]);
                    yyerror(yyvsp[0]);
                }
                if(!strcmp(s->val,"~")) {
                    fprintf(stderr,"%s is not initialized\n",yyvsp[0]);
                    yyerror(yyvsp[0]);
                }
                char new_value[32];
                if(s->type==INT) {
                    int val = atoi(s->val) - 1;
                    sprintf(new_value,"%d",val);
                } else if(s->type==FLOAT || s->type==DOUBLE) {
                    double val = atof(s->val) - 1.0;
                    sprintf(new_value,"%lf",val);
                }
                insert_value_to_symbol(s,new_value);
                yyval=strdup(new_value);
                vtype=s->type;
                decrease_indent();
            }
#line 1949 "parser.tab.c"
    break;

  case 46: /* INCREMENT: T_ID T_INC  */
#line 502 "parser.y"
               {
                print_ast("POST_INCREMENT", yyvsp[-1]);
                increase_indent();
                symbol *s=get_symbol(yyvsp[-1],scope,func);
                if(s==NULL) {
                    fprintf(stderr,"%s is not declared\n",yyvsp[-1]);
                    yyerror(yyvsp[-1]);
                }
                if(!strcmp(s->val,"~")) {
                    fprintf(stderr,"%s is not initialized\n",yyvsp[-1]);
                    yyerror(yyvsp[-1]);
                }
                yyval=strdup(s->val);
                char new_value[32];
                if(s->type==INT) {
                    int val = atoi(s->val) + 1;
                    sprintf(new_value,"%d",val);
                } else if(s->type==FLOAT || s->type==DOUBLE) {
                    double val = atof(s->val) + 1.0;
                    sprintf(new_value,"%lf",val);
                }
                insert_value_to_symbol(s,new_value);
                vtype=s->type;
                decrease_indent();
            }
#line 1979 "parser.tab.c"
    break;

  case 47: /* INCREMENT: T_ID T_DEC  */
#line 527 "parser.y"
               {
                print_ast("POST_DECREMENT", yyvsp[-1]);
                increase_indent();
                symbol *s=get_symbol(yyvsp[-1],scope,func);
                if(s==NULL) {
                    fprintf(stderr,"%s is not declared\n",yyvsp[-1]);
                    yyerror(yyvsp[-1]);
                }
                if(!strcmp(s->val,"~")) {
                    fprintf(stderr,"%s is not initialized\n",yyvsp[-1]);
                    yyerror(yyvsp[-1]);
                }
                yyval=strdup(s->val);
                char new_value[32];
                if(s->type==INT) {
                    int val = atoi(s->val) - 1;
                    sprintf(new_value,"%d",val);
                } else if(s->type==FLOAT || s->type==DOUBLE) {
                    double val = atof(s->val) - 1.0;
                    sprintf(new_value,"%lf",val);
                }
                insert_value_to_symbol(s,new_value);
                vtype=s->type;
                decrease_indent();
            }
#line 2009 "parser.tab.c"
    break;

  case 48: /* REL_OP: T_LESSEREQ  */
#line 554 "parser.y"
                    {
           print_ast("RELATIONAL_OPERATOR", "<=");
           yyval = "<=";
         }
#line 2018 "parser.tab.c"
    break;

  case 49: /* REL_OP: T_GREATEREQ  */
#line 558 "parser.y"
                     {
           print_ast("RELATIONAL_OPERATOR", ">=");
           yyval = ">=";
         }
#line 2027 "parser.tab.c"
    break;

  case 50: /* REL_OP: '<'  */
#line 562 "parser.y"
             {
           print_ast("RELATIONAL_OPERATOR", "<");
           yyval = "<";
         }
#line 2036 "parser.tab.c"
    break;

  case 51: /* REL_OP: '>'  */
#line 566 "parser.y"
             {
           print_ast("RELATIONAL_OPERATOR", ">");
           yyval = ">";
         }
#line 2045 "parser.tab.c"
    break;

  case 52: /* REL_OP: T_EQCOMP  */
#line 570 "parser.y"
                  {
           print_ast("RELATIONAL_OPERATOR", "==");
           yyval = "==";
         }
#line 2054 "parser.tab.c"
    break;

  case 53: /* REL_OP: T_NOTEQUAL  */
#line 574 "parser.y"
                    {
           print_ast("RELATIONAL_OPERATOR", "!=");
           yyval = "!=";
         }
#line 2063 "parser.tab.c"
    break;

  case 54: /* $@2: %empty  */
#line 580 "parser.y"
                       {
          print_ast("MAIN_FUNCTION", "main");
          increase_indent();
          temp=func;func=0;
       }
#line 2073 "parser.tab.c"
    break;

  case 55: /* $@3: %empty  */
#line 584 "parser.y"
                               {scope++;}
#line 2079 "parser.tab.c"
    break;

  case 56: /* MAIN: TYPE T_MAIN '(' $@2 EMPTY_LISTVAR ')' '{' $@3 STMT '}'  */
#line 584 "parser.y"
                                                   {
          scope--; 
          func=temp;
          decrease_indent();
       }
#line 2089 "parser.tab.c"
    break;

  case 57: /* $@4: %empty  */
#line 591 "parser.y"
                    {
          print_ast("FUNCTION", yyvsp[-1]);
          increase_indent();
          ++func;
       }
#line 2099 "parser.tab.c"
    break;

  case 58: /* $@5: %empty  */
#line 595 "parser.y"
                               {scope++;}
#line 2105 "parser.tab.c"
    break;

  case 59: /* FUNC: TYPE T_ID '(' $@4 EMPTY_LISTVAR ')' '{' $@5 STMT '}'  */
#line 595 "parser.y"
                                                   {
          scope--;
          decrease_indent();
       }
#line 2114 "parser.tab.c"
    break;

  case 60: /* EMPTY_LISTVAR: LISTVAR  */
#line 601 "parser.y"
                        {
                  print_ast("PARAMETER_LIST", "with_params");
                  increase_indent();
                  decrease_indent();
                }
#line 2124 "parser.tab.c"
    break;

  case 61: /* EMPTY_LISTVAR: %empty  */
#line 606 "parser.y"
                {
                  print_ast("PARAMETER_LIST", "empty");
                }
#line 2132 "parser.tab.c"
    break;

  case 66: /* STMT_NO_BLOCK: DECLR ';'  */
#line 617 "parser.y"
                          {
                  print_ast("DECLARATION_STATEMENT", NULL);
                  increase_indent();
                  decrease_indent();
                }
#line 2142 "parser.tab.c"
    break;

  case 67: /* STMT_NO_BLOCK: ASSGN ';'  */
#line 622 "parser.y"
                          {
                  print_ast("ASSIGNMENT_STATEMENT", NULL);
                  increase_indent();
                  decrease_indent();
                }
#line 2152 "parser.tab.c"
    break;

  case 68: /* STMT_NO_BLOCK: IF_STMT  */
#line 627 "parser.y"
                        {
                  print_ast("IF_STATEMENT", NULL);
                  increase_indent();
                  decrease_indent();
                }
#line 2162 "parser.tab.c"
    break;

  case 69: /* STMT_NO_BLOCK: error ';'  */
#line 632 "parser.y"
                          {
                  print_ast("ERROR", "statement_error");
                  error_count++;
                }
#line 2171 "parser.tab.c"
    break;

  case 70: /* $@6: %empty  */
#line 638 "parser.y"
                            {
            print_ast("IF", NULL);
            increase_indent();
            if(!condition_result) {
                skip_execution = 1;
            }
            print_ast("CONDITION", condition_result ? "true" : "false");
            decrease_indent();
        }
#line 2185 "parser.tab.c"
    break;

  case 71: /* $@7: %empty  */
#line 646 "parser.y"
                       {
            skip_execution = 0;
        }
#line 2193 "parser.tab.c"
    break;

  case 73: /* $@8: %empty  */
#line 651 "parser.y"
                   {
            print_ast("ELSE", NULL);
            increase_indent();
            if(condition_result) {
                skip_execution = 1;
            }
        }
#line 2205 "parser.tab.c"
    break;

  case 74: /* ELSE_PART: T_ELSE $@8 '{' STMT '}'  */
#line 657 "parser.y"
                       {
            skip_execution = 0;
            decrease_indent();
        }
#line 2214 "parser.tab.c"
    break;

  case 75: /* ELSE_PART: %empty  */
#line 661 "parser.y"
          {
            print_ast("NO_ELSE", NULL);
          }
#line 2222 "parser.tab.c"
    break;

  case 76: /* LOOP_STMT: WHILE_LOOP  */
#line 666 "parser.y"
                       {
              print_ast("LOOP", "while");
              increase_indent();
              decrease_indent();
            }
#line 2232 "parser.tab.c"
    break;

  case 77: /* LOOP_STMT: DO_WHILE_LOOP  */
#line 671 "parser.y"
                          {
              print_ast("LOOP", "do_while");
              increase_indent();
              decrease_indent();
            }
#line 2242 "parser.tab.c"
    break;

  case 78: /* LOOP_STMT: FOR_LOOP  */
#line 676 "parser.y"
                     {
              print_ast("LOOP", "for");
              increase_indent();
              decrease_indent();
            }
#line 2252 "parser.tab.c"
    break;

  case 79: /* $@9: %empty  */
#line 683 "parser.y"
                                  {
               print_ast("WHILE_LOOP", NULL);
               increase_indent();
               if(!condition_result) {
                   skip_execution = 1;
               }
               print_ast("CONDITION", condition_result ? "true" : "false");
               decrease_indent();
           }
#line 2266 "parser.tab.c"
    break;

  case 80: /* WHILE_LOOP: T_WHILE '(' COND ')' $@9 BLOCK  */
#line 691 "parser.y"
                   {
               skip_execution = 0;
           }
#line 2274 "parser.tab.c"
    break;

  case 81: /* $@10: %empty  */
#line 696 "parser.y"
                     {
                  print_ast("DO_WHILE_LOOP", NULL);
                  increase_indent();
                }
#line 2283 "parser.tab.c"
    break;

  case 82: /* DO_WHILE_LOOP: T_DO $@10 BLOCK T_WHILE '(' COND ')' ';'  */
#line 699 "parser.y"
                                                 {
                  print_ast("CONDITION", condition_result ? "true" : "false");
                  decrease_indent();
                }
#line 2292 "parser.tab.c"
    break;

  case 83: /* $@11: %empty  */
#line 705 "parser.y"
                                                          {
             print_ast("FOR_LOOP", NULL);
             increase_indent();
             if(!condition_result) {
                 skip_execution = 1;
             }
             print_ast("CONDITION", condition_result ? "true" : "false");
             decrease_indent();
         }
#line 2306 "parser.tab.c"
    break;

  case 84: /* FOR_LOOP: T_FOR '(' FOR_INIT ';' COND ';' FOR_UPDATE ')' $@11 BLOCK  */
#line 713 "parser.y"
                 {
             skip_execution = 0;
         }
#line 2314 "parser.tab.c"
    break;

  case 85: /* FOR_INIT: DECLR  */
#line 718 "parser.y"
                 {
             print_ast("FOR_INIT", "declaration");
             increase_indent();
             decrease_indent();
           }
#line 2324 "parser.tab.c"
    break;

  case 86: /* FOR_INIT: ASSGN  */
#line 723 "parser.y"
                 {
             print_ast("FOR_INIT", "assignment");
             increase_indent();
             decrease_indent();
           }
#line 2334 "parser.tab.c"
    break;

  case 87: /* FOR_INIT: %empty  */
#line 728 "parser.y"
           {
             print_ast("FOR_INIT", "empty");
           }
#line 2342 "parser.tab.c"
    break;

  case 88: /* FOR_UPDATE: INCREMENT  */
#line 733 "parser.y"
                       {
               print_ast("FOR_UPDATE", "increment");
               increase_indent();
               decrease_indent();
             }
#line 2352 "parser.tab.c"
    break;

  case 89: /* FOR_UPDATE: ASSGN  */
#line 738 "parser.y"
                   {
               print_ast("FOR_UPDATE", "assignment");
               increase_indent();
               decrease_indent();
             }
#line 2362 "parser.tab.c"
    break;

  case 90: /* FOR_UPDATE: %empty  */
#line 743 "parser.y"
             {
               print_ast("FOR_UPDATE", "empty");
             }
#line 2370 "parser.tab.c"
    break;

  case 91: /* $@12: %empty  */
#line 748 "parser.y"
            {
          print_ast("BLOCK", NULL);
          increase_indent();
          scope++;
        }
#line 2380 "parser.tab.c"
    break;

  case 92: /* BLOCK: '{' $@12 STMT '}'  */
#line 752 "parser.y"
                   {
          scope--;
          decrease_indent();
        }
#line 2389 "parser.tab.c"
    break;

  case 93: /* COND: EXPR  */
#line 758 "parser.y"
            {
         print_ast("CONDITION_EXPR", NULL);
         increase_indent();
         decrease_indent();
       }
#line 2399 "parser.tab.c"
    break;

  case 94: /* COND: ASSGN  */
#line 763 "parser.y"
             {
         print_ast("CONDITION_ASSGN", NULL);
         increase_indent();
         decrease_indent();
       }
#line 2409 "parser.tab.c"
    break;


#line 2413 "parser.tab.c"

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

#line 770 "parser.y"


void yyerror(char* s)
{
    printf("Error :%s at %d \n", s, yylineno);
    error_count++;
    yyclearin;
}

int main(int argc, char* argv[])
{
    t = allocate_space_for_table();
    fp = fopen("1.txt", "w");
    fprintf(fp, "ABSTRACT SYNTAX TREE\n");
    
    yyparse();
    
    if (error_count == 0) {
    } else {
        printf("Invalid syntax - %d error(s) found\n", error_count);
    }
    
    fclose(fp);
    display_symbol_table();
    return 0;
}
