/* $Id: gvplugin_dot_layout.c,v 1.7 2009/06/03 01:10:56 ellson Exp $ $Revision: 1.7 $ */
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

extern gvplugin_installed_t gvlayout_dot_layout[];

static gvplugin_api_t apis[] = {
    {API_layout, gvlayout_dot_layout},
    {(api_t)0, 0},
};
/*visual studio*/
#ifdef WIN32_DLL
#ifndef GVPLUGIN_DOT_LAYOUT_EXPORTS
__declspec(dllimport) gvplugin_library_t gvplugin_dot_layout_LTX_library = { "dot_layout", apis };
#else
__declspec(dllexport) gvplugin_library_t gvplugin_dot_layout_LTX_library = { "dot_layout", apis };
#endif
#endif
/*end visual studio*/


#ifndef WIN32_DLL
#ifdef GVDLL
__declspec(dllexport) gvplugin_library_t gvplugin_dot_layout_LTX_library = { "dot_layout", apis };
#else
gvplugin_library_t gvplugin_dot_layout_LTX_library = { "dot_layout", apis };
#endif
#endif


