/* $Id: toolboxcallbacks.h,v 1.10 2009/10/09 18:28:17 erg Exp $ $Revision: 1.10 $ */
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

#ifndef TOOLBOXCALLBACKS_H
#define TOOLBOXCALLBACKS_H
#include <gtk/gtk.h>
#include "gui.h"
#if WIN32
#define _BB  __declspec(dllexport)
#else
#define _BB /**/
#endif
#ifdef __cplusplus
extern "C" {
#endif

    _BB void btnToolSingleSelect_clicked(GtkWidget * widget,
					 gpointer user_data);
    _BB void btnToolRectSelect_clicked(GtkWidget * widget,
				       gpointer user_data);
    _BB void btnToolRectXSelect_clicked(GtkWidget * widget,
					gpointer user_data);

    _BB void btnToolAntiRectSelect_clicked(GtkWidget * widget,
					   gpointer user_data);
    _BB void btnToolAntiRectXSelect_clicked(GtkWidget * widget,
					    gpointer user_data);



    _BB void btnToolPan_clicked(GtkWidget * widget, gpointer user_data);
    _BB void btnToolZoom_clicked(GtkWidget * widget, gpointer user_data);
    _BB void btnToolZoomIn_clicked(GtkWidget * widget, gpointer user_data);
    _BB void btnToolZoomOut_clicked(GtkWidget * widget,
				    gpointer user_data);
    _BB void btnToolZoomFit_clicked(GtkWidget * widget,
				    gpointer user_data);
    _BB void btnToolFit_clicked(GtkWidget * widget, gpointer user_data);
    _BB void btnToolMove_clicked(GtkWidget * widget, gpointer user_data);
    _BB void btnToolAddNode_clicked(GtkWidget * widget,
				    gpointer user_data);
    _BB void btnToolDeleteNode_clicked(GtkWidget * widget,
				       gpointer user_data);
    _BB void btnToolFindNode_clicked(GtkWidget * widget,
				     gpointer user_data);
    _BB void btnToolAddEdge_clicked(GtkWidget * widget,
				    gpointer user_data);
    _BB void btnToolDeleteEdge_clicked(GtkWidget * widget,
				       gpointer user_data);
    _BB void btnToolFindEdge_clicked(GtkWidget * widget,
				     gpointer user_data);
    _BB void btnToolCursor_clicked(GtkWidget * widget, gpointer user_data);
    _BB void on_btnActivateGraph_clicked(GtkWidget * widget,
					 gpointer user_data);

    void write_to_console(char *text);

#ifdef __cplusplus
}				/* end extern "C" */
#endif
#endif
