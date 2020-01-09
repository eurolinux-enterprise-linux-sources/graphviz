
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* All symbols defined below should begin with html or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 17 "../../lib/common/htmlparse.y"


#include "render.h"
#include "htmltable.h"
#include "htmllex.h"

extern int htmlparse(void);

typedef struct sfont_t {
    htmlfont_t *cfont;	
    struct sfont_t *pfont;
} sfont_t;

static struct {
  htmllabel_t* lbl;       /* Generated label */
  htmltbl_t*   tblstack;  /* Stack of tables maintained during parsing */
  Dt_t*        fitemList; /* Dictionary for font text items */
  Dt_t*        fparaList; 
  agxbuf*      str;       /* Buffer for text */
  sfont_t*     fontstack;
} HTMLstate;

/* free_ritem:
 * Free row. This closes and frees row's list, then
 * the pitem itself is freed.
 */
static void
free_ritem(Dt_t* d, pitem* p,Dtdisc_t* ds)
{
  dtclose (p->u.rp);
  free (p);
}

/* free_item:
 * Generic Dt free. Only frees container, assuming contents
 * have been copied elsewhere.
 */
static void
free_item(Dt_t* d, void* p,Dtdisc_t* ds)
{
  free (p);
}

/* cleanTbl:
 * Clean up table if error in parsing.
 */
static void
cleanTbl (htmltbl_t* tp)
{
  dtclose (tp->u.p.rows);
  free_html_data (&tp->data);
  free (tp);
}

/* cleanCell:
 * Clean up cell if error in parsing.
 */
static void
cleanCell (htmlcell_t* cp)
{
  if (cp->child.kind == HTML_TBL) cleanTbl (cp->child.u.tbl);
  else if (cp->child.kind == HTML_TEXT) free_html_text (cp->child.u.txt);
  free_html_data (&cp->data);
  free (cp);
}

/* free_citem:
 * Free cell item during parsing. This frees cell and pitem.
 */
static void
free_citem(Dt_t* d, pitem* p,Dtdisc_t* ds)
{
  cleanCell (p->u.cp);
  free (p);
}

static Dtdisc_t rowDisc = {
    offsetof(pitem,u),
    sizeof(void*),
    offsetof(pitem,link),
    NIL(Dtmake_f),
    (Dtfree_f)free_ritem,
    NIL(Dtcompar_f),
    NIL(Dthash_f),
    NIL(Dtmemory_f),
    NIL(Dtevent_f)
};
static Dtdisc_t cellDisc = {
    offsetof(pitem,u),
    sizeof(void*),
    offsetof(pitem,link),
    NIL(Dtmake_f),
    (Dtfree_f)free_item,
    NIL(Dtcompar_f),
    NIL(Dthash_f),
    NIL(Dtmemory_f),
    NIL(Dtevent_f)
};

typedef struct {
    Dtlink_t    link;
    textitem_t  ti;
} fitem;

typedef struct {
    Dtlink_t     link;
    htextpara_t  lp;
} fpara;

static void 
free_fitem(Dt_t* d, fitem* p, Dtdisc_t* ds)
{
    if (p->ti.str)
	free (p->ti.str);
    if (p->ti.font)
        free_html_font (p->ti.font);
    free (p);
}

static void 
free_fpara(Dt_t* d, fpara* p, Dtdisc_t* ds)
{
    textitem_t* ti;

    if (p->lp.nitems) {
	int i;
	ti = p->lp.items;
	for (i = 0; i < p->lp.nitems; i++) {
	    if (ti->str) free (ti->str);
	    if (ti->font) free_html_font (ti->font);
	    ti++;
	}
	free (p->lp.items);
    }
    free (p);
}

static Dtdisc_t fstrDisc = {
    0,
    0,
    offsetof(fitem,link),
    NIL(Dtmake_f),
    (Dtfree_f)free_item,
    NIL(Dtcompar_f),
    NIL(Dthash_f),
    NIL(Dtmemory_f),
    NIL(Dtevent_f)
};


static Dtdisc_t fparaDisc = {
    0,
    0,
    offsetof(fpara,link),
    NIL(Dtmake_f),
    (Dtfree_f)free_item,
    NIL(Dtcompar_f),
    NIL(Dthash_f),
    NIL(Dtmemory_f),
    NIL(Dtevent_f)
};

/* dupFont:
 */
static htmlfont_t *
dupFont (htmlfont_t *f)
{
    if (f) f->cnt++;
    return f;
}

/* appendFItemList:
 * Append a new fitem to the list.
 */
static void
appendFItemList (agxbuf *ag)
{
    fitem *fi = NEW(fitem);

    fi->ti.str = strdup(agxbuse(ag));
    fi->ti.font = dupFont (HTMLstate.fontstack->cfont);
    dtinsert(HTMLstate.fitemList, fi);
}	

/* appendFLineList:
 */
static void 
appendFLineList (int v)
{
    int cnt;
    fpara *ln = NEW(fpara);
    fitem *fi;
    Dt_t *ilist = HTMLstate.fitemList;

    cnt = dtsize(ilist);
    ln->lp.nitems = cnt;
    ln->lp.just = v;
    if (cnt) {
        int i = 0;
	ln->lp.items = N_NEW(cnt, textitem_t); 

	fi = (fitem*)dtflatten(ilist);
	for (; fi; fi = (fitem*)dtlink(fitemList,(Dtlink_t*)fi)) {
	    ln->lp.items[i] = fi->ti;
	    i++;
	}
    }

    dtclear(ilist);

    dtinsert(HTMLstate.fparaList, ln);
}

static htmltxt_t*
mkText(void)
{
    int cnt;
    Dt_t * ipara = HTMLstate.fparaList;
    fpara *fl ;
    htmltxt_t *hft = NEW(htmltxt_t);
    
    if (dtsize (HTMLstate.fitemList)) 
	appendFLineList (UNSET_ALIGN);

    cnt = dtsize(ipara);
    hft->nparas = cnt;
    	
    if (cnt) {
	int i = 0;
	hft->paras = N_NEW(cnt,htextpara_t);	
    	for(fl=(fpara *)dtfirst(ipara); fl; fl=(fpara *)dtnext(ipara,fl)) {
    	    hft->paras[i] = fl->lp;
    	    i++;
    	}
    }
    
    dtclear(ipara);

    return hft;
}

/* addRow:
 * Add new cell row to current table.
 */
static void addRow (void)
{
  Dt_t*      dp = dtopen(&cellDisc, Dtqueue);
  htmltbl_t* tbl = HTMLstate.tblstack;
  pitem*     sp = NEW(pitem);
  sp->u.rp = dp;
  dtinsert (tbl->u.p.rows, sp);
}

/* setCell:
 * Set cell body and type and attach to row
 */
static void setCell (htmlcell_t* cp, void* obj, int kind)
{
  pitem*     sp = NEW(pitem);
  htmltbl_t* tbl = HTMLstate.tblstack;
  pitem*     rp = (pitem*)dtlast (tbl->u.p.rows);
  Dt_t*      row = rp->u.rp;
  sp->u.cp = cp;
  dtinsert (row, sp);
  cp->child.kind = kind;
  
  if(kind == HTML_TEXT)
  	cp->child.u.txt = (htmltxt_t*)obj;
  else if (kind == HTML_IMAGE)
    cp->child.u.img = (htmlimg_t*)obj;
  else
    cp->child.u.tbl = (htmltbl_t*)obj;
}

/* mkLabel:
 * Create label, given body and type.
 */
static htmllabel_t* mkLabel (void* obj, int kind)
{
  htmllabel_t* lp = NEW(htmllabel_t);

  lp->kind = kind;
  if (kind == HTML_TEXT)
    lp->u.txt = (htmltxt_t*)obj;
  else
    lp->u.tbl = (htmltbl_t*)obj;
  return lp;
}

/* freeFontstack:
 * Free all stack items but the last, which is
 * put on artificially during in parseHTML.
 */
static void
freeFontstack(void)
{
    sfont_t* s;
    sfont_t* next;

    for (s = HTMLstate.fontstack; (next = s->pfont); s = next) {
	free_html_font (s->cfont);
	free(s);
    }
}

/* cleanup:
 * Called on error. Frees resources allocated during parsing.
 * This includes a label, plus a walk down the stack of
 * tables. Note that we use the free_citem function to actually
 * free cells.
 */
static void cleanup (void)
{
  htmltbl_t* tp = HTMLstate.tblstack;
  htmltbl_t* next;

  if (HTMLstate.lbl) {
    free_html_label (HTMLstate.lbl,1);
    HTMLstate.lbl = NULL;
  }
  cellDisc.freef = (Dtfree_f)free_citem;
  while (tp) {
    next = tp->u.p.prev;
    cleanTbl (tp);
    tp = next;
  }
  cellDisc.freef = (Dtfree_f)free_item;

  fstrDisc.freef = (Dtfree_f)free_fitem;
  dtclear (HTMLstate.fitemList);
  fstrDisc.freef = (Dtfree_f)free_item;

  fparaDisc.freef = (Dtfree_f)free_fpara;
  dtclear (HTMLstate.fparaList);
  fparaDisc.freef = (Dtfree_f)free_item;

  freeFontstack();
}

/* nonSpace:
 * Return 1 if s contains a non-space character.
 */
static int nonSpace (char* s)
{
  char   c;

  while ((c = *s++)) {
    if (c != ' ') return 1;
  }
  return 0;
}

/* pushFont:
 * Fonts are allocated in the lexer.
 */
static void
pushFont (htmlfont_t *f)
{
    sfont_t *ft = NEW(sfont_t);
    htmlfont_t* curfont = HTMLstate.fontstack->cfont;

    if (curfont) {
	if (!f->color && curfont->color)
	    f->color = strdup(curfont->color);
	if ((f->size < 0.0) && (curfont->size >= 0.0))
	    f->size = curfont->size;
	if (!f->name && curfont->name)
	    f->name = strdup(curfont->name);
	if (!f->flags && curfont->flags)
	    f->flags = curfont->flags;
    }

    ft->cfont = dupFont (f);
    ft->pfont = HTMLstate.fontstack;
    HTMLstate.fontstack = ft;
}

/* popFont:
 */
static void 
popFont (void)
{
    sfont_t* curfont = HTMLstate.fontstack;
    sfont_t* prevfont = curfont->pfont;

    free_html_font (curfont->cfont);
    free (curfont);
    HTMLstate.fontstack = prevfont;
}



/* Line 189 of yacc.c  */
#line 466 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum htmltokentype {
     T_end_br = 258,
     T_end_img = 259,
     T_row = 260,
     T_end_row = 261,
     T_html = 262,
     T_end_html = 263,
     T_end_table = 264,
     T_end_cell = 265,
     T_end_font = 266,
     T_string = 267,
     T_error = 268,
     T_n_italic = 269,
     T_n_bold = 270,
     T_n_underline = 271,
     T_BR = 272,
     T_br = 273,
     T_IMG = 274,
     T_img = 275,
     T_table = 276,
     T_cell = 277,
     T_font = 278,
     T_italic = 279,
     T_bold = 280,
     T_underline = 281
   };
#endif
/* Tokens.  */
#define T_end_br 258
#define T_end_img 259
#define T_row 260
#define T_end_row 261
#define T_html 262
#define T_end_html 263
#define T_end_table 264
#define T_end_cell 265
#define T_end_font 266
#define T_string 267
#define T_error 268
#define T_n_italic 269
#define T_n_bold 270
#define T_n_underline 271
#define T_BR 272
#define T_br 273
#define T_IMG 274
#define T_img 275
#define T_table 276
#define T_cell 277
#define T_font 278
#define T_italic 279
#define T_bold 280
#define T_underline 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 409 "../../lib/common/htmlparse.y"

  int    i;
  htmltxt_t*  txt;
  htmlcell_t*  cell;
  htmltbl_t*   tbl;
  htmlfont_t*  font;
  htmlimg_t*   img;



/* Line 214 of yacc.c  */
#line 565 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define htmlstype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 577 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 htmltype_uint8;
#else
typedef unsigned char htmltype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 htmltype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char htmltype_int8;
#else
typedef short int htmltype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 htmltype_uint16;
#else
typedef unsigned short int htmltype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 htmltype_int16;
#else
typedef short int htmltype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int htmli)
#else
static int
YYID (htmli)
    int htmli;
#endif
{
  return htmli;
}
#endif

#if ! defined htmloverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined htmloverflow || YYERROR_VERBOSE */


#if (! defined htmloverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union htmlalloc
{
  htmltype_int16 htmlss_alloc;
  YYSTYPE htmlvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union htmlalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (htmltype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T htmli;				\
	  for (htmli = 0; htmli < (Count); htmli++)	\
	    (To)[htmli] = (From)[htmli];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T htmlnewbytes;						\
	YYCOPY (&htmlptr->Stack_alloc, Stack, htmlsize);			\
	Stack = &htmlptr->Stack_alloc;					\
	htmlnewbytes = htmlstacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	htmlptr += htmlnewbytes / sizeof (*htmlptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   117

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNRULES -- Number of states.  */
#define YYNSTATES  83

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? htmltranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const htmltype_uint8 htmltranslate[] =
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
      25,    26
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const htmltype_uint8 htmlprhs[] =
{
       0,     0,     3,     7,    11,    13,    15,    18,    20,    22,
      24,    28,    32,    36,    40,    42,    44,    46,    48,    50,
      52,    54,    56,    59,    61,    63,    66,    67,    74,    76,
      80,    84,    88,    92,    94,    95,    97,   100,   101,   106,
     108,   111,   112,   117,   118,   123,   124,   129,   130,   134,
     137
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const htmltype_int8 htmlrhs[] =
{
      28,     0,    -1,     7,    29,     8,    -1,     7,    44,     8,
      -1,     1,    -1,    30,    -1,    30,    31,    -1,    31,    -1,
      41,    -1,    40,    -1,    32,    30,    33,    -1,    34,    30,
      35,    -1,    38,    30,    39,    -1,    36,    30,    37,    -1,
      23,    -1,    11,    -1,    24,    -1,    14,    -1,    25,    -1,
      15,    -1,    26,    -1,    16,    -1,    18,     3,    -1,    17,
      -1,    12,    -1,    41,    12,    -1,    -1,    45,    21,    43,
      46,     9,    45,    -1,    42,    -1,    32,    42,    33,    -1,
      34,    42,    35,    -1,    38,    42,    39,    -1,    36,    42,
      37,    -1,    41,    -1,    -1,    47,    -1,    46,    47,    -1,
      -1,     5,    48,    49,     6,    -1,    50,    -1,    49,    50,
      -1,    -1,    22,    44,    51,    10,    -1,    -1,    22,    29,
      52,    10,    -1,    -1,    22,    55,    53,    10,    -1,    -1,
      22,    54,    10,    -1,    20,     4,    -1,    19,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const htmltype_uint16 htmlrline[] =
{
       0,   436,   436,   437,   438,   441,   444,   445,   448,   449,
     450,   451,   452,   453,   456,   459,   462,   465,   468,   471,
     474,   477,   480,   481,   484,   485,   488,   488,   509,   510,
     511,   512,   513,   516,   517,   520,   521,   524,   524,   527,
     528,   531,   531,   532,   532,   533,   533,   534,   534,   537,
     538
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const htmltname[] =
{
  "$end", "error", "$undefined", "T_end_br", "T_end_img", "T_row",
  "T_end_row", "T_html", "T_end_html", "T_end_table", "T_end_cell",
  "T_end_font", "T_string", "T_error", "T_n_italic", "T_n_bold",
  "T_n_underline", "T_BR", "T_br", "T_IMG", "T_img", "T_table", "T_cell",
  "T_font", "T_italic", "T_bold", "T_underline", "$accept", "html",
  "fonttext", "text", "textitem", "font", "n_font", "italic", "n_italic",
  "bold", "n_bold", "underline", "n_underline", "br", "string", "table",
  "@1", "fonttable", "opt_space", "rows", "row", "$@2", "cells", "cell",
  "$@3", "$@4", "$@5", "$@6", "image", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const htmltype_uint16 htmltoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const htmltype_uint8 htmlr1[] =
{
       0,    27,    28,    28,    28,    29,    30,    30,    31,    31,
      31,    31,    31,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    40,    41,    41,    43,    42,    44,    44,
      44,    44,    44,    45,    45,    46,    46,    48,    47,    49,
      49,    51,    50,    52,    50,    53,    50,    54,    50,    55,
      55
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const htmltype_uint8 htmlr2[] =
{
       0,     2,     3,     3,     1,     1,     2,     1,     1,     1,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     2,     0,     6,     1,     3,
       3,     3,     3,     1,     0,     1,     2,     0,     4,     1,
       2,     0,     4,     0,     4,     0,     4,     0,     3,     2,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const htmltype_uint8 htmldefact[] =
{
       0,     4,    34,     0,    24,    23,     0,    14,    16,    18,
      20,     0,     5,     7,    34,    34,    34,    34,     9,     8,
      28,     0,     0,     1,    22,     2,     6,     0,     0,     0,
       0,     8,     0,     0,     0,     0,     0,     0,     0,     0,
      25,     3,    26,    15,    10,    29,    17,    11,    30,    19,
      13,    32,    21,    12,    31,     0,    37,     0,    35,     0,
      34,    36,    34,     0,    39,    33,    27,    50,     0,    43,
      41,     0,    45,    38,    40,    49,     0,     0,    48,     0,
      44,    42,    46
};

/* YYDEFGOTO[NTERM-NUM].  */
static const htmltype_int8 htmldefgoto[] =
{
      -1,     3,    11,    12,    13,    27,    44,    28,    47,    29,
      50,    30,    53,    18,    31,    20,    55,    21,    22,    57,
      58,    59,    63,    64,    77,    76,    79,    71,    72
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -9
static const htmltype_int8 htmlpact[] =
{
      17,    -9,    82,    11,    -9,    -9,     7,    -9,    -9,    -9,
      -9,     9,    82,    -9,    82,    82,    82,    82,    -9,    33,
      -9,    15,    25,    -9,    -9,    -9,    -9,    82,    82,    82,
      82,    18,    26,    36,    53,    34,    57,    40,    72,    43,
      -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,    -9,
      -9,    -9,    -9,    -9,    -9,    51,    -9,    48,    -9,    44,
      56,    -9,    16,    10,    -9,    18,    -9,    -9,    69,    -9,
      -9,    75,    -9,    -9,    -9,    -9,    76,    77,    -9,    81,
      -9,    -9,    -9
};

/* YYPGOTO[NTERM-NUM].  */
static const htmltype_int8 htmlpgoto[] =
{
      -9,    -9,    30,    -8,    -7,    -1,    60,     0,    74,     1,
      73,     2,    78,    -9,    -2,    87,    -9,    49,    52,    -9,
      58,    -9,    -9,    50,    -9,    -9,    -9,    -9,    -9
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -48
static const htmltype_int8 htmltable[] =
{
      19,    14,    15,    16,    17,    26,    32,    34,    36,    38,
      24,    23,    19,    19,    19,    19,    73,    25,     1,    32,
      34,    36,    38,    41,     2,    26,   -47,    26,     4,    26,
      40,    26,    62,     5,     6,    67,    68,    43,     4,     7,
       8,     9,    10,     5,     6,    40,    42,    43,    46,     7,
       8,     9,    10,    56,   -33,    49,    56,    60,    65,    52,
      19,    14,    15,    16,    17,     4,    62,    46,     4,     4,
       5,     6,    49,    75,     5,     6,     7,     8,     9,    10,
       7,     8,     9,    10,     4,    78,    80,    81,    52,     5,
       6,    82,    69,    45,     4,     7,     8,     9,    10,     5,
       6,    33,    35,    37,    39,     7,     8,     9,    10,    48,
      51,    70,    66,    74,     0,    61,     0,    54
};

static const htmltype_int8 htmlcheck[] =
{
       2,     2,     2,     2,     2,    12,    14,    15,    16,    17,
       3,     0,    14,    15,    16,    17,     6,     8,     1,    27,
      28,    29,    30,     8,     7,    32,    10,    34,    12,    36,
      12,    38,    22,    17,    18,    19,    20,    11,    12,    23,
      24,    25,    26,    17,    18,    12,    21,    11,    14,    23,
      24,    25,    26,     5,    21,    15,     5,     9,    60,    16,
      62,    62,    62,    62,    62,    12,    22,    14,    12,    12,
      17,    18,    15,     4,    17,    18,    23,    24,    25,    26,
      23,    24,    25,    26,    12,    10,    10,    10,    16,    17,
      18,    10,    62,    33,    12,    23,    24,    25,    26,    17,
      18,    14,    15,    16,    17,    23,    24,    25,    26,    35,
      37,    62,    60,    63,    -1,    57,    -1,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const htmltype_uint8 htmlstos[] =
{
       0,     1,     7,    28,    12,    17,    18,    23,    24,    25,
      26,    29,    30,    31,    32,    34,    36,    38,    40,    41,
      42,    44,    45,     0,     3,     8,    31,    32,    34,    36,
      38,    41,    30,    42,    30,    42,    30,    42,    30,    42,
      12,     8,    21,    11,    33,    33,    14,    35,    35,    15,
      37,    37,    16,    39,    39,    43,     5,    46,    47,    48,
       9,    47,    22,    49,    50,    41,    45,    19,    20,    29,
      44,    54,    55,     6,    50,     4,    52,    51,    10,    53,
      10,    10,    10
};

#define htmlerrok		(htmlerrstatus = 0)
#define htmlclearin	(htmlchar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto htmlacceptlab
#define YYABORT		goto htmlabortlab
#define YYERROR		goto htmlerrorlab


/* Like YYERROR except do call htmlerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto htmlerrlab

#define YYRECOVERING()  (!!htmlerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (htmlchar == YYEMPTY && htmllen == 1)				\
    {								\
      htmlchar = (Token);						\
      htmllval = (Value);						\
      htmltoken = YYTRANSLATE (htmlchar);				\
      YYPOPSTACK (1);						\
      goto htmlbackup;						\
    }								\
  else								\
    {								\
      htmlerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `htmllex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX htmllex (YYLEX_PARAM)
#else
# define YYLEX htmllex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (htmldebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (htmldebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      html_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
html_symbol_value_print (FILE *htmloutput, int htmltype, YYSTYPE const * const htmlvaluep)
#else
static void
html_symbol_value_print (htmloutput, htmltype, htmlvaluep)
    FILE *htmloutput;
    int htmltype;
    YYSTYPE const * const htmlvaluep;
#endif
{
  if (!htmlvaluep)
    return;
# ifdef YYPRINT
  if (htmltype < YYNTOKENS)
    YYPRINT (htmloutput, htmltoknum[htmltype], *htmlvaluep);
# else
  YYUSE (htmloutput);
# endif
  switch (htmltype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
html_symbol_print (FILE *htmloutput, int htmltype, YYSTYPE const * const htmlvaluep)
#else
static void
html_symbol_print (htmloutput, htmltype, htmlvaluep)
    FILE *htmloutput;
    int htmltype;
    YYSTYPE const * const htmlvaluep;
#endif
{
  if (htmltype < YYNTOKENS)
    YYFPRINTF (htmloutput, "token %s (", htmltname[htmltype]);
  else
    YYFPRINTF (htmloutput, "nterm %s (", htmltname[htmltype]);

  html_symbol_value_print (htmloutput, htmltype, htmlvaluep);
  YYFPRINTF (htmloutput, ")");
}

/*------------------------------------------------------------------.
| html_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
html_stack_print (htmltype_int16 *htmlbottom, htmltype_int16 *htmltop)
#else
static void
html_stack_print (htmlbottom, htmltop)
    htmltype_int16 *htmlbottom;
    htmltype_int16 *htmltop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; htmlbottom <= htmltop; htmlbottom++)
    {
      int htmlbot = *htmlbottom;
      YYFPRINTF (stderr, " %d", htmlbot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (htmldebug)							\
    html_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
html_reduce_print (YYSTYPE *htmlvsp, int htmlrule)
#else
static void
html_reduce_print (htmlvsp, htmlrule)
    YYSTYPE *htmlvsp;
    int htmlrule;
#endif
{
  int htmlnrhs = htmlr2[htmlrule];
  int htmli;
  unsigned long int htmllno = htmlrline[htmlrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     htmlrule - 1, htmllno);
  /* The symbols being reduced.  */
  for (htmli = 0; htmli < htmlnrhs; htmli++)
    {
      YYFPRINTF (stderr, "   $%d = ", htmli + 1);
      html_symbol_print (stderr, htmlrhs[htmlprhs[htmlrule] + htmli],
		       &(htmlvsp[(htmli + 1) - (htmlnrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (htmldebug)				\
    html_reduce_print (htmlvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int htmldebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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

# ifndef htmlstrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define htmlstrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
htmlstrlen (const char *htmlstr)
#else
static YYSIZE_T
htmlstrlen (htmlstr)
    const char *htmlstr;
#endif
{
  YYSIZE_T htmllen;
  for (htmllen = 0; htmlstr[htmllen]; htmllen++)
    continue;
  return htmllen;
}
#  endif
# endif

# ifndef htmlstpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define htmlstpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
htmlstpcpy (char *htmldest, const char *htmlsrc)
#else
static char *
htmlstpcpy (htmldest, htmlsrc)
    char *htmldest;
    const char *htmlsrc;
#endif
{
  char *htmld = htmldest;
  const char *htmls = htmlsrc;

  while ((*htmld++ = *htmls++) != '\0')
    continue;

  return htmld - 1;
}
#  endif
# endif

# ifndef htmltnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for htmlerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from htmltname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
htmltnamerr (char *htmlres, const char *htmlstr)
{
  if (*htmlstr == '"')
    {
      YYSIZE_T htmln = 0;
      char const *htmlp = htmlstr;

      for (;;)
	switch (*++htmlp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++htmlp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (htmlres)
	      htmlres[htmln] = *htmlp;
	    htmln++;
	    break;

	  case '"':
	    if (htmlres)
	      htmlres[htmln] = '\0';
	    return htmln;
	  }
    do_not_strip_quotes: ;
    }

  if (! htmlres)
    return htmlstrlen (htmlstr);

  return htmlstpcpy (htmlres, htmlstr) - htmlres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
htmlsyntax_error (char *htmlresult, int htmlstate, int htmlchar)
{
  int htmln = htmlpact[htmlstate];

  if (! (YYPACT_NINF < htmln && htmln <= YYLAST))
    return 0;
  else
    {
      int htmltype = YYTRANSLATE (htmlchar);
      YYSIZE_T htmlsize0 = htmltnamerr (0, htmltname[htmltype]);
      YYSIZE_T htmlsize = htmlsize0;
      YYSIZE_T htmlsize1;
      int htmlsize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *htmlarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int htmlx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *htmlfmt;
      char const *htmlf;
      static char const htmlunexpected[] = "syntax error, unexpected %s";
      static char const htmlexpecting[] = ", expecting %s";
      static char const htmlor[] = " or %s";
      char htmlformat[sizeof htmlunexpected
		    + sizeof htmlexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof htmlor - 1))];
      char const *htmlprefix = htmlexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int htmlxbegin = htmln < 0 ? -htmln : 0;

      /* Stay within bounds of both htmlcheck and htmltname.  */
      int htmlchecklim = YYLAST - htmln + 1;
      int htmlxend = htmlchecklim < YYNTOKENS ? htmlchecklim : YYNTOKENS;
      int htmlcount = 1;

      htmlarg[0] = htmltname[htmltype];
      htmlfmt = htmlstpcpy (htmlformat, htmlunexpected);

      for (htmlx = htmlxbegin; htmlx < htmlxend; ++htmlx)
	if (htmlcheck[htmlx + htmln] == htmlx && htmlx != YYTERROR)
	  {
	    if (htmlcount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		htmlcount = 1;
		htmlsize = htmlsize0;
		htmlformat[sizeof htmlunexpected - 1] = '\0';
		break;
	      }
	    htmlarg[htmlcount++] = htmltname[htmlx];
	    htmlsize1 = htmlsize + htmltnamerr (0, htmltname[htmlx]);
	    htmlsize_overflow |= (htmlsize1 < htmlsize);
	    htmlsize = htmlsize1;
	    htmlfmt = htmlstpcpy (htmlfmt, htmlprefix);
	    htmlprefix = htmlor;
	  }

      htmlf = YY_(htmlformat);
      htmlsize1 = htmlsize + htmlstrlen (htmlf);
      htmlsize_overflow |= (htmlsize1 < htmlsize);
      htmlsize = htmlsize1;

      if (htmlsize_overflow)
	return YYSIZE_MAXIMUM;

      if (htmlresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *htmlp = htmlresult;
	  int htmli = 0;
	  while ((*htmlp = *htmlf) != '\0')
	    {
	      if (*htmlp == '%' && htmlf[1] == 's' && htmli < htmlcount)
		{
		  htmlp += htmltnamerr (htmlp, htmlarg[htmli++]);
		  htmlf += 2;
		}
	      else
		{
		  htmlp++;
		  htmlf++;
		}
	    }
	}
      return htmlsize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
htmldestruct (const char *htmlmsg, int htmltype, YYSTYPE *htmlvaluep)
#else
static void
htmldestruct (htmlmsg, htmltype, htmlvaluep)
    const char *htmlmsg;
    int htmltype;
    YYSTYPE *htmlvaluep;
#endif
{
  YYUSE (htmlvaluep);

  if (!htmlmsg)
    htmlmsg = "Deleting";
  YY_SYMBOL_PRINT (htmlmsg, htmltype, htmlvaluep, htmllocationp);

  switch (htmltype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int htmlparse (void *YYPARSE_PARAM);
#else
int htmlparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int htmlparse (void);
#else
int htmlparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int htmlchar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE htmllval;

/* Number of syntax errors so far.  */
int htmlnerrs;



/*-------------------------.
| htmlparse or htmlpush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
htmlparse (void *YYPARSE_PARAM)
#else
int
htmlparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
htmlparse (void)
#else
int
htmlparse ()

#endif
#endif
{


    int htmlstate;
    /* Number of tokens to shift before error messages enabled.  */
    int htmlerrstatus;

    /* The stacks and their tools:
       `htmlss': related to states.
       `htmlvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow htmloverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    htmltype_int16 htmlssa[YYINITDEPTH];
    htmltype_int16 *htmlss;
    htmltype_int16 *htmlssp;

    /* The semantic value stack.  */
    YYSTYPE htmlvsa[YYINITDEPTH];
    YYSTYPE *htmlvs;
    YYSTYPE *htmlvsp;

    YYSIZE_T htmlstacksize;

  int htmln;
  int htmlresult;
  /* Lookahead token as an internal (translated) token number.  */
  int htmltoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE htmlval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char htmlmsgbuf[128];
  char *htmlmsg = htmlmsgbuf;
  YYSIZE_T htmlmsg_alloc = sizeof htmlmsgbuf;
#endif

#define YYPOPSTACK(N)   (htmlvsp -= (N), htmlssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int htmllen = 0;

  htmltoken = 0;
  htmlss = htmlssa;
  htmlvs = htmlvsa;
  htmlstacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  htmlstate = 0;
  htmlerrstatus = 0;
  htmlnerrs = 0;
  htmlchar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  htmlssp = htmlss;
  htmlvsp = htmlvs;

  goto htmlsetstate;

/*------------------------------------------------------------.
| htmlnewstate -- Push a new state, which is found in htmlstate.  |
`------------------------------------------------------------*/
 htmlnewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  htmlssp++;

 htmlsetstate:
  *htmlssp = htmlstate;

  if (htmlss + htmlstacksize - 1 <= htmlssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T htmlsize = htmlssp - htmlss + 1;

#ifdef htmloverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *htmlvs1 = htmlvs;
	htmltype_int16 *htmlss1 = htmlss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if htmloverflow is a macro.  */
	htmloverflow (YY_("memory exhausted"),
		    &htmlss1, htmlsize * sizeof (*htmlssp),
		    &htmlvs1, htmlsize * sizeof (*htmlvsp),
		    &htmlstacksize);

	htmlss = htmlss1;
	htmlvs = htmlvs1;
      }
#else /* no htmloverflow */
# ifndef YYSTACK_RELOCATE
      goto htmlexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= htmlstacksize)
	goto htmlexhaustedlab;
      htmlstacksize *= 2;
      if (YYMAXDEPTH < htmlstacksize)
	htmlstacksize = YYMAXDEPTH;

      {
	htmltype_int16 *htmlss1 = htmlss;
	union htmlalloc *htmlptr =
	  (union htmlalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (htmlstacksize));
	if (! htmlptr)
	  goto htmlexhaustedlab;
	YYSTACK_RELOCATE (htmlss_alloc, htmlss);
	YYSTACK_RELOCATE (htmlvs_alloc, htmlvs);
#  undef YYSTACK_RELOCATE
	if (htmlss1 != htmlssa)
	  YYSTACK_FREE (htmlss1);
      }
# endif
#endif /* no htmloverflow */

      htmlssp = htmlss + htmlsize - 1;
      htmlvsp = htmlvs + htmlsize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) htmlstacksize));

      if (htmlss + htmlstacksize - 1 <= htmlssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", htmlstate));

  if (htmlstate == YYFINAL)
    YYACCEPT;

  goto htmlbackup;

/*-----------.
| htmlbackup.  |
`-----------*/
htmlbackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  htmln = htmlpact[htmlstate];
  if (htmln == YYPACT_NINF)
    goto htmldefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (htmlchar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      htmlchar = YYLEX;
    }

  if (htmlchar <= YYEOF)
    {
      htmlchar = htmltoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      htmltoken = YYTRANSLATE (htmlchar);
      YY_SYMBOL_PRINT ("Next token is", htmltoken, &htmllval, &htmllloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  htmln += htmltoken;
  if (htmln < 0 || YYLAST < htmln || htmlcheck[htmln] != htmltoken)
    goto htmldefault;
  htmln = htmltable[htmln];
  if (htmln <= 0)
    {
      if (htmln == 0 || htmln == YYTABLE_NINF)
	goto htmlerrlab;
      htmln = -htmln;
      goto htmlreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (htmlerrstatus)
    htmlerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", htmltoken, &htmllval, &htmllloc);

  /* Discard the shifted token.  */
  htmlchar = YYEMPTY;

  htmlstate = htmln;
  *++htmlvsp = htmllval;

  goto htmlnewstate;


/*-----------------------------------------------------------.
| htmldefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
htmldefault:
  htmln = htmldefact[htmlstate];
  if (htmln == 0)
    goto htmlerrlab;
  goto htmlreduce;


/*-----------------------------.
| htmlreduce -- Do a reduction.  |
`-----------------------------*/
htmlreduce:
  /* htmln is the number of a rule to reduce with.  */
  htmllen = htmlr2[htmln];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  htmlval = htmlvsp[1-htmllen];


  YY_REDUCE_PRINT (htmln);
  switch (htmln)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 436 "../../lib/common/htmlparse.y"
    { HTMLstate.lbl = mkLabel((htmlvsp[(2) - (3)].txt),HTML_TEXT); }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 437 "../../lib/common/htmlparse.y"
    { HTMLstate.lbl = mkLabel((htmlvsp[(2) - (3)].tbl),HTML_TBL); }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 438 "../../lib/common/htmlparse.y"
    { cleanup(); YYABORT; }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 441 "../../lib/common/htmlparse.y"
    { (htmlval.txt) = mkText(); }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 448 "../../lib/common/htmlparse.y"
    { appendFItemList(HTMLstate.str);}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 449 "../../lib/common/htmlparse.y"
    {appendFLineList((htmlvsp[(1) - (1)].i));}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 456 "../../lib/common/htmlparse.y"
    { pushFont ((htmlvsp[(1) - (1)].font)); }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 459 "../../lib/common/htmlparse.y"
    { popFont (); }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 462 "../../lib/common/htmlparse.y"
    {pushFont((htmlvsp[(1) - (1)].font));}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 465 "../../lib/common/htmlparse.y"
    {popFont();}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 468 "../../lib/common/htmlparse.y"
    {pushFont((htmlvsp[(1) - (1)].font));}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 471 "../../lib/common/htmlparse.y"
    {popFont();}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 474 "../../lib/common/htmlparse.y"
    {pushFont((htmlvsp[(1) - (1)].font));}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 477 "../../lib/common/htmlparse.y"
    {popFont();}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 480 "../../lib/common/htmlparse.y"
    { (htmlval.i) = (htmlvsp[(1) - (2)].i); }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 481 "../../lib/common/htmlparse.y"
    { (htmlval.i) = (htmlvsp[(1) - (1)].i); }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 488 "../../lib/common/htmlparse.y"
    { 
          if (nonSpace(agxbuse(HTMLstate.str))) {
            htmlerror ("Syntax error: non-space string used before <TABLE>");
            cleanup(); YYABORT;
          }
          (htmlvsp[(2) - (2)].tbl)->u.p.prev = HTMLstate.tblstack;
          (htmlvsp[(2) - (2)].tbl)->u.p.rows = dtopen(&rowDisc, Dtqueue);
          HTMLstate.tblstack = (htmlvsp[(2) - (2)].tbl);
          (htmlvsp[(2) - (2)].tbl)->font = dupFont (HTMLstate.fontstack->cfont);
          (htmlval.tbl) = (htmlvsp[(2) - (2)].tbl);
        }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 499 "../../lib/common/htmlparse.y"
    {
          if (nonSpace(agxbuse(HTMLstate.str))) {
            htmlerror ("Syntax error: non-space string used after </TABLE>");
            cleanup(); YYABORT;
          }
          (htmlval.tbl) = HTMLstate.tblstack;
          HTMLstate.tblstack = HTMLstate.tblstack->u.p.prev;
        }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 509 "../../lib/common/htmlparse.y"
    { (htmlval.tbl) = (htmlvsp[(1) - (1)].tbl); }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 510 "../../lib/common/htmlparse.y"
    { (htmlval.tbl)=(htmlvsp[(2) - (3)].tbl); }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 511 "../../lib/common/htmlparse.y"
    { (htmlval.tbl)=(htmlvsp[(2) - (3)].tbl); }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 512 "../../lib/common/htmlparse.y"
    { (htmlval.tbl)=(htmlvsp[(2) - (3)].tbl); }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 513 "../../lib/common/htmlparse.y"
    { (htmlval.tbl)=(htmlvsp[(2) - (3)].tbl); }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 524 "../../lib/common/htmlparse.y"
    { addRow (); }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 531 "../../lib/common/htmlparse.y"
    { setCell((htmlvsp[(1) - (2)].cell),(htmlvsp[(2) - (2)].tbl),HTML_TBL); }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 532 "../../lib/common/htmlparse.y"
    { setCell((htmlvsp[(1) - (2)].cell),(htmlvsp[(2) - (2)].txt),HTML_TEXT); }
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 533 "../../lib/common/htmlparse.y"
    { setCell((htmlvsp[(1) - (2)].cell),(htmlvsp[(2) - (2)].img),HTML_IMAGE); }
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 534 "../../lib/common/htmlparse.y"
    { setCell((htmlvsp[(1) - (1)].cell),mkText(),HTML_TEXT); }
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 537 "../../lib/common/htmlparse.y"
    { (htmlval.img) = (htmlvsp[(1) - (2)].img); }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 538 "../../lib/common/htmlparse.y"
    { (htmlval.img) = (htmlvsp[(1) - (1)].img); }
    break;



/* Line 1455 of yacc.c  */
#line 2076 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", htmlr1[htmln], &htmlval, &htmlloc);

  YYPOPSTACK (htmllen);
  htmllen = 0;
  YY_STACK_PRINT (htmlss, htmlssp);

  *++htmlvsp = htmlval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  htmln = htmlr1[htmln];

  htmlstate = htmlpgoto[htmln - YYNTOKENS] + *htmlssp;
  if (0 <= htmlstate && htmlstate <= YYLAST && htmlcheck[htmlstate] == *htmlssp)
    htmlstate = htmltable[htmlstate];
  else
    htmlstate = htmldefgoto[htmln - YYNTOKENS];

  goto htmlnewstate;


/*------------------------------------.
| htmlerrlab -- here on detecting error |
`------------------------------------*/
htmlerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!htmlerrstatus)
    {
      ++htmlnerrs;
#if ! YYERROR_VERBOSE
      htmlerror (YY_("syntax error"));
#else
      {
	YYSIZE_T htmlsize = htmlsyntax_error (0, htmlstate, htmlchar);
	if (htmlmsg_alloc < htmlsize && htmlmsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T htmlalloc = 2 * htmlsize;
	    if (! (htmlsize <= htmlalloc && htmlalloc <= YYSTACK_ALLOC_MAXIMUM))
	      htmlalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (htmlmsg != htmlmsgbuf)
	      YYSTACK_FREE (htmlmsg);
	    htmlmsg = (char *) YYSTACK_ALLOC (htmlalloc);
	    if (htmlmsg)
	      htmlmsg_alloc = htmlalloc;
	    else
	      {
		htmlmsg = htmlmsgbuf;
		htmlmsg_alloc = sizeof htmlmsgbuf;
	      }
	  }

	if (0 < htmlsize && htmlsize <= htmlmsg_alloc)
	  {
	    (void) htmlsyntax_error (htmlmsg, htmlstate, htmlchar);
	    htmlerror (htmlmsg);
	  }
	else
	  {
	    htmlerror (YY_("syntax error"));
	    if (htmlsize != 0)
	      goto htmlexhaustedlab;
	  }
      }
#endif
    }



  if (htmlerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (htmlchar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (htmlchar == YYEOF)
	    YYABORT;
	}
      else
	{
	  htmldestruct ("Error: discarding",
		      htmltoken, &htmllval);
	  htmlchar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto htmlerrlab1;


/*---------------------------------------------------.
| htmlerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
htmlerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label htmlerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto htmlerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (htmllen);
  htmllen = 0;
  YY_STACK_PRINT (htmlss, htmlssp);
  htmlstate = *htmlssp;
  goto htmlerrlab1;


/*-------------------------------------------------------------.
| htmlerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
htmlerrlab1:
  htmlerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      htmln = htmlpact[htmlstate];
      if (htmln != YYPACT_NINF)
	{
	  htmln += YYTERROR;
	  if (0 <= htmln && htmln <= YYLAST && htmlcheck[htmln] == YYTERROR)
	    {
	      htmln = htmltable[htmln];
	      if (0 < htmln)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (htmlssp == htmlss)
	YYABORT;


      htmldestruct ("Error: popping",
		  htmlstos[htmlstate], htmlvsp);
      YYPOPSTACK (1);
      htmlstate = *htmlssp;
      YY_STACK_PRINT (htmlss, htmlssp);
    }

  *++htmlvsp = htmllval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", htmlstos[htmln], htmlvsp, htmllsp);

  htmlstate = htmln;
  goto htmlnewstate;


/*-------------------------------------.
| htmlacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
htmlacceptlab:
  htmlresult = 0;
  goto htmlreturn;

/*-----------------------------------.
| htmlabortlab -- YYABORT comes here.  |
`-----------------------------------*/
htmlabortlab:
  htmlresult = 1;
  goto htmlreturn;

#if !defined(htmloverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| htmlexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
htmlexhaustedlab:
  htmlerror (YY_("memory exhausted"));
  htmlresult = 2;
  /* Fall through.  */
#endif

htmlreturn:
  if (htmlchar != YYEMPTY)
     htmldestruct ("Cleanup: discarding lookahead",
		 htmltoken, &htmllval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (htmllen);
  YY_STACK_PRINT (htmlss, htmlssp);
  while (htmlssp != htmlss)
    {
      htmldestruct ("Cleanup: popping",
		  htmlstos[*htmlssp], htmlvsp);
      YYPOPSTACK (1);
    }
#ifndef htmloverflow
  if (htmlss != htmlssa)
    YYSTACK_FREE (htmlss);
#endif
#if YYERROR_VERBOSE
  if (htmlmsg != htmlmsgbuf)
    YYSTACK_FREE (htmlmsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (htmlresult);
}



/* Line 1675 of yacc.c  */
#line 541 "../../lib/common/htmlparse.y"


/* parseHTML:
 * Return parsed label or NULL if failure.
 * Set warn to 0 on success; 1 for warning message; 2 if no expat.
 */
htmllabel_t*
parseHTML (char* txt, int* warn, int charset)
{
  unsigned char buf[SMALLBUF];
  agxbuf        str;
  htmllabel_t*  l;
  sfont_t       dfltf;

  dfltf.cfont = NULL;
  dfltf.pfont = NULL;
  HTMLstate.fontstack = &dfltf;
  HTMLstate.tblstack = 0;
  HTMLstate.lbl = 0;
  HTMLstate.fitemList = dtopen(&fstrDisc, Dtqueue);
  HTMLstate.fparaList = dtopen(&fparaDisc, Dtqueue);

  agxbinit (&str, SMALLBUF, buf);
  HTMLstate.str = &str;
  
  if (initHTMLlexer (txt, &str, charset)) {/* failed: no libexpat - give up */
    *warn = 2;
    l = NULL;
  }
  else {
    htmlparse();
    *warn = clearHTMLlexer ();
    l = HTMLstate.lbl;
  }

  dtclose (HTMLstate.fitemList);
  dtclose (HTMLstate.fparaList);
  
  HTMLstate.fitemList = NULL;
  HTMLstate.fparaList = NULL;
  HTMLstate.fontstack = NULL;
  
  agxbfree (&str);

  return l;
}


