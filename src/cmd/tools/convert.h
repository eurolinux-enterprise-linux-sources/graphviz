/* $Id: convert.h,v 1.8 2009/06/03 01:56:55 ellson Exp $ $Revision: 1.8 $ */
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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONVERT_H
#define CONVERT_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#include <string.h>

#include "cgraph.h"
#include "cghdr.h"

    extern void gv_to_gxl(Agraph_t *, FILE *);
#ifdef HAVE_EXPAT
    extern Agraph_t *gxl_to_gv(FILE *);
#endif

#endif

#ifdef __cplusplus
}
#endif
