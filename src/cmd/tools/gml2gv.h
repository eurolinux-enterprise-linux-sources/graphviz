/* $Id: gml2gv.h,v 1.1 2009/07/08 21:00:58 erg Exp $Revision: */
/* vim:set shiftwidth=4 ts=8: */

#include <stdio.h>
#include <cgraph.h>

typedef struct {
    Dtlink_t link;
    unsigned short kind;
    unsigned short sort;
    char* name;
    union {
	char* value;
	Dt_t* lp;
    }u;
} gmlattr;

typedef struct {
    Dtlink_t link;
    char* id;
    Dt_t* attrlist;  
} gmlnode;

typedef struct {
    Dtlink_t link;
    char* source;
    char* target;
    Dt_t* attrlist;  
} gmledge;

typedef struct gmlgraph {
    Dtlink_t link;
    struct gmlgraph* parent;
    int directed;
    Dt_t* attrlist;  
    Dt_t* nodelist;  
    Dt_t* edgelist;  
    Dt_t* graphlist;  
} gmlgraph;

extern int gmllex(void);
extern void gmllexeof(void);
extern void gmlerror(char *);
extern int gmlerrors(void);
extern void initgmlscan (FILE*);
extern Agraph_t* gml_to_gv (FILE*, int, int*);
