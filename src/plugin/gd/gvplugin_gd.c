/* $Id: gvplugin_gd.c,v 1.16 2009/06/03 01:10:56 ellson Exp $ $Revision: 1.16 $ */
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

extern gvplugin_installed_t gvrender_gd_types[];
extern gvplugin_installed_t gvrender_vrml_types[];
extern gvplugin_installed_t gvtextlayout_gd_types[];
extern gvplugin_installed_t gvloadimage_gd_types[];
extern gvplugin_installed_t gvdevice_gd_types[];
extern gvplugin_installed_t gvdevice_gd_types2[];
extern gvplugin_installed_t gvdevice_vrml_types[];

static gvplugin_api_t apis[] = {
    {API_render, gvrender_gd_types},
    {API_render, gvrender_vrml_types},
    {API_textlayout, gvtextlayout_gd_types},
    {API_loadimage, gvloadimage_gd_types},
    {API_device, gvdevice_gd_types},
    {API_device, gvdevice_gd_types2},
    {API_device, gvdevice_vrml_types},
    {(api_t)0, 0},
};

#ifdef WIN32_DLL /*visual studio*/
#ifndef GVPLUGIN_GD_EXPORTS
__declspec(dllimport) gvplugin_library_t gvplugin_gd_LTX_library = { "gd", apis };
#else
__declspec(dllexport) gvplugin_library_t gvplugin_gd_LTX_library = { "gd", apis };
#endif
#else /*end visual studio*/
#ifdef GVDLL
__declspec(dllexport) gvplugin_library_t gvplugin_gd_LTX_library = { "gd", apis };
#else
gvplugin_library_t gvplugin_gd_LTX_library = { "gd", apis };
#endif
#endif


