/* $Id: gvio.h,v 1.15 2009/09/03 21:55:20 erg Exp $ $Revision: 1.15 $ */
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

#ifndef GVDEVICE_H
#define GVDEVICE_H

#include "gvcjob.h"

#ifdef __cplusplus
extern "C" {
#endif

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

    extern size_t gvwrite (GVJ_t * job, const char *s, size_t len);
    extern size_t gvfwrite (const void *ptr, size_t size, size_t nmemb, FILE *stream);
    extern int gvferror (FILE *stream);
    extern int gvputc(GVJ_t * job, int c);
    extern int gvputs(GVJ_t * job, const char *s);
    extern int gvflush (GVJ_t * job);
    extern void gvprintf(GVJ_t * job, const char *format, ...);
    extern void gvprintdouble(GVJ_t * job, double num); 
    extern void gvprintpointf(GVJ_t * job, pointf p);
    extern void gvprintpointflist(GVJ_t * job, pointf *p, int n);

#undef extern

#ifdef __cplusplus
}
#endif

#endif				/* GVDEVICE_H */
