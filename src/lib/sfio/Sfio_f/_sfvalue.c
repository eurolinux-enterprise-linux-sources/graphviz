/* $Id: _sfvalue.c,v 1.3 2009/06/03 01:10:55 ellson Exp $ $Revision: 1.3 $ */
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

#include	"sfhdr.h"

#undef sfvalue

#if __STD_C
ssize_t sfvalue(reg Sfio_t * f)
#else
ssize_t sfvalue(f)
reg Sfio_t *f;
#endif
{
    return __sf_value(f);
}
