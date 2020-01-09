/* $Id: gvcontext.c,v 1.36 2009/10/04 20:15:42 ellson Exp $ $Revision: 1.36 $ */
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
    A gvcontext is a single instance of a GVC_t data structure providing
    for a set of plugins for processing one graph at a time, and a job
    description provividing for a sequence of graph jobs.

    Sometime in the future it may become the basis for a thread.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdlib.h>

#include "builddate.h"
#include "types.h"
#include "gvplugin.h"
#include "gvcjob.h"
#include "gvcint.h"
#include "gvcproc.h"
#include "gvc.h"

/* from common/utils.c */
extern void *zmalloc(size_t);

/* from common/emit.c */
extern void emit_once_reset(void);

/* from common/globals.c */
extern int graphviz_errors;

static char *LibInfo[] = {
    "graphviz",         /* Program */
    VERSION,            /* Version */
    BUILDDATE           /* Build Date */
};

GVC_t *gvNEWcontext(const lt_symlist_t *builtins, int demand_loading)
{
    GVC_t *gvc = zmalloc(sizeof(GVC_t));

    if (gvc) {
	gvc->common.info = LibInfo;
	gvc->common.errorfn = agerrorf;
	gvc->common.builtins = builtins;
	gvc->common.demand_loading = demand_loading;
    }
    return gvc;
}

void gvFinalize(GVC_t * gvc)
{
    if (gvc->active_jobs)
	gvrender_end_job(gvc->active_jobs);
}


int gvFreeContext(GVC_t * gvc)
{
    GVG_t *gvg, *gvg_next;
    gvplugin_package_t *package, *package_next;

    emit_once_reset();
    gvg_next = gvc->gvgs;
    while ((gvg = gvg_next)) {
	gvg_next = gvg->next;
	free(gvg);
    }
    package_next = gvc->packages;
    while ((package = package_next)) {
	package_next = package->next;
	free(package->path);
	free(package->name);
	free(package);
    }
    gvjobs_delete(gvc);
    if (gvc->config_path)
	free(gvc->config_path);
    if (gvc->input_filenames)
	free(gvc->input_filenames);
    free(gvc);
    return (graphviz_errors + agerrors());
}
