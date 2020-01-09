/* $Id: filter.h,v 1.5 2009/10/09 18:28:17 erg Exp $ $Revision: 1.5 $ */
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

#ifndef FILTER_H
#define FILTER_H
#include "btree.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct _tv_filters {
	tv_filter **filters;
	int filter_count;
    } tv_filters;

    int clear_filter(tv_filter * f);
    int init_filters(tv_filters * filters);
    int add_filter_to_filters(tv_filters * filters, tv_filter * filter);
    int clear_filters(tv_filters * filters);
    int union_filter(tv_filter * f1, tv_filter * f2);
    int intersect_filter(tv_filter * f1, tv_filter * f2);

#ifdef __cplusplus
}				/* end extern "C" */
#endif
#endif
