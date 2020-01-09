/* $Id: twopiinit.c,v 1.19 2009/08/11 21:21:20 erg Exp $ $Revision: 1.19 $ */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2004 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/


/*
 * Written by Emden R. Gansner
 * Derived from Graham Wills' algorithm described in GD'97.
 */

#include    "circle.h"
#include    "adjust.h"
#include    "pack.h"
#include    "neatoprocs.h"

static void twopi_init_edge(edge_t * e)
{
#ifdef WITH_CGRAPH
    agbindrec(e, "Agedgeinfo_t", sizeof(Agedgeinfo_t), TRUE);	//node custom data
#endif /* WITH_CGRAPH */
    common_init_edge(e);
    ED_factor(e) = late_double(e, E_weight, 1.0, 0.0);
}

static void twopi_init_node_edge(graph_t * g)
{
    node_t *n;
    edge_t *e;
    int i = 0;
    rdata* alg = N_NEW(agnnodes(g), rdata);

    GD_neato_nlist(g) = N_NEW(agnnodes(g) + 1, node_t *);
    for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
	neato_init_node(n);
	ND_alg(n) = alg + i;
	GD_neato_nlist(g)[i++] = n;
    }
    for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
	for (e = agfstout(g, n); e; e = agnxtout(g, e)) {
	    twopi_init_edge(e);
	}
    }
}

void twopi_init_graph(graph_t * g)
{
    setEdgeType (g, ET_LINE);
    /* GD_ndim(g) = late_int(g,agfindgraphattr(g,"dim"),2,2); */
	Ndim = GD_ndim(g)=2;	/* The algorithm only makes sense in 2D */
    twopi_init_node_edge(g);
}

/* twopi_layout:
 */
void twopi_layout(Agraph_t * g)
{
    Agnode_t *ctr = 0;
    char *s;

    twopi_init_graph(g);
    s = agget(g, "root");
    if (s && (*s != '\0')) {
	ctr = agfindnode(g, s);
	if (!ctr) {
	    agerr(AGWARN, "specified root node \"%s\" was not found.", s);
	    agerr(AGPREV, "Using default calculation for root node\n");
	}
    }
    if (agnnodes(g)) {
	Agraph_t **ccs;
	Agraph_t *sg;
	Agnode_t *c = NULL;
	int ncc;
	int i;

	ccs = ccomps(g, &ncc, 0);
	if (ncc == 1) {
	    circleLayout(g, ctr);
	    free(ND_alg(agfstnode(g)));
	    adjustNodes(g);
	    spline_edges(g);
	} else {
	    pack_info pinfo;
	    getPackInfo (g, l_node, CL_OFFSET, &pinfo);
	    pinfo.doSplines = 1;

	    for (i = 0; i < ncc; i++) {
		sg = ccs[i];
		if (ctr && agcontains(sg, ctr))
		    c = ctr;
		else
		    c = 0;
		nodeInduce(sg);
		circleLayout(sg, c);
		adjustNodes(sg);
		setEdgeType (sg, ET_LINE);
		spline_edges(sg);
	    }
	    free(ND_alg(agfstnode(g)));
	    packSubgraphs(ncc, ccs, g, &pinfo);
	}
	for (i = 0; i < ncc; i++) {
	    agdelete(g, ccs[i]);
	}
	free(ccs);
    }
    dotneato_postprocess(g);

}

static void twopi_cleanup_graph(graph_t * g)
{
    free(GD_neato_nlist(g));
    if (g != agroot(g))
#ifndef WITH_CGRAPH
	memset(&(g->u), 0, sizeof(Agraphinfo_t));
#else /* WITH_CGRAPH */
	agclean(g,AGRAPH,"Agraphinfo_t");
#endif /* WITH_CGRAPH */
}

void twopi_cleanup(graph_t * g)
{
    node_t *n;
    edge_t *e;

    for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
	for (e = agfstout(g, n); e; e = agnxtout(g, e)) {
	    gv_cleanup_edge(e);
	}
	gv_cleanup_node(n);
    }
    twopi_cleanup_graph(g);
}
