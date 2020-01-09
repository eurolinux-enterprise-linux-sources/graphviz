/* $Id: pointset.h,v 1.9 2009/07/24 21:07:07 erg Exp $ $Revision: 1.9 $ */
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

#ifndef _POINTSET_H
#define _POINTSET_H 1

#include <cdt.h>
#include <geom.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef Dict_t PointSet;
    typedef Dict_t PointMap;
#ifdef GVDLL
#define extern __declspec(dllexport)
#else
#define extern
#endif

/*visual studio*/
#ifdef WIN32_DLL
#ifndef GVC_EXPORTS
#define extern __declspec(dllimport)
#endif
#endif
/*end visual studio*/

	extern PointSet *newPS(void);
    extern void freePS(PointSet *);
    extern void insertPS(PointSet *, point);
    extern void addPS(PointSet *, int, int);
    extern int inPS(PointSet *, point);
    extern int isInPS(PointSet *, int, int);
    extern int sizeOf(PointSet *);
    extern point *pointsOf(PointSet *);

    extern PointMap *newPM(void);
    extern void clearPM(PointMap *);
    extern void freePM(PointMap *);
    extern int insertPM(PointMap *, int, int, int);
    extern int updatePM(PointMap * pm, int x, int y, int v);

#undef extern
#ifdef __cplusplus
}
#endif

#endif /* _POINTSET_H */
