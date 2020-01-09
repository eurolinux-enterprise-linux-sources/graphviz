/* $Id: pathutil.h,v 1.6 2009/06/03 01:10:54 ellson Exp $ $Revision: 1.6 $ */
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



#ifndef _PATHUTIL_INCLUDE
#define _PATHUTIL_INCLUDE
#define _BLD_pathplan 1

#include "pathplan.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NOT
#define NOT(x)	(!(x))
#endif
#ifndef FALSE
#define FALSE	0
#define TRUE	(NOT(FALSE))
#endif

/*visual studio*/
#ifdef WIN32_DLL
#ifndef PATHPLAN_EXPORTS
#define extern __declspec(dllimport)
#endif
#endif
/*end visual studio*/
	typedef double COORD;
    extern COORD area2(Ppoint_t, Ppoint_t, Ppoint_t);
    extern int wind(Ppoint_t a, Ppoint_t b, Ppoint_t c);
    extern COORD dist2(Ppoint_t, Ppoint_t);
    extern int intersect(Ppoint_t a, Ppoint_t b, Ppoint_t c, Ppoint_t d);

    int in_poly(Ppoly_t argpoly, Ppoint_t q);
    Ppoly_t copypoly(Ppoly_t);
    void freepoly(Ppoly_t);

#undef extern
#ifdef __cplusplus
}
#endif
#endif
