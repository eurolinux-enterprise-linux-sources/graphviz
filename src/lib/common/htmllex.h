/* $Id: htmllex.h,v 1.6 2009/06/03 01:10:52 ellson Exp $ $Revision: 1.6 $ */
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

#ifndef HTMLLEX_H
#define HTMLLEX_H

#include <agxbuf.h>

    extern int initHTMLlexer(char *, agxbuf *, int);
    extern int htmllex(void);
    extern int htmllineno(void);
    extern int clearHTMLlexer(void);
    void htmlerror(const char *);

#endif

#ifdef __cplusplus
}
#endif
