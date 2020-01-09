/* $Id: SF.h,v 1.3 2009/06/03 01:10:49 ellson Exp $ $Revision: 1.3 $ */
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

int XsraSelFile (
    Widget, char *, char *, char *, char *, char *, char *,
    int (*) (char *, char **, struct stat *), char *, int
);

#ifdef __cplusplus
}
#endif

