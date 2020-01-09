/* $Id: gvplugin_rsvg.c,v 1.5 2009/06/03 01:10:57 ellson Exp $ $Revision: 1.5 $ */
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

#include "gvplugin.h"

extern gvplugin_installed_t gvloadimage_rsvg_types[];

static gvplugin_api_t apis[] = {
    {API_loadimage, gvloadimage_rsvg_types},
    {(api_t)0, 0},
};
#ifdef GVDLL
__declspec(dllexport) gvplugin_library_t gvplugin_rsvg_LTX_library = { "rsvg", apis };
#else
gvplugin_library_t gvplugin_rsvg_LTX_library = { "rsvg", apis };
#endif

