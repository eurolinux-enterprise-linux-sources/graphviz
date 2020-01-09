/* $Id: gvprpipe.h,v 1.8 2009/11/18 22:05:48 arif Exp $Revision:*/
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

#ifndef GVPRPIPE_H
#define GVPRPIPE_H

#include "cgraph.h"

#ifdef __cplusplus
extern "C" {
#endif
    extern int run_gvpr(Agraph_t * srcGraph, int argc, char *argv[]);


#ifdef __cplusplus
}				/* end extern "C" */
#endif
#endif
