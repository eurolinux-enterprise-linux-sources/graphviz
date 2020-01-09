/* $Id: glcomppanel.h,v 1.5 2009/10/09 17:25:34 erg Exp $Revision: */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2007 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/
#ifndef GLCOMPPANEL_H
#define GLCOMPPANEL_H

#include "glcompdefs.h"

#ifdef __cplusplus
extern "C" {
#endif

    extern glCompPanel *glCompPanelNew(glCompObj * parentObj, GLfloat x,
				       GLfloat y, GLfloat w, GLfloat h);
    extern int glCompSetAddPanel(glCompSet * s, glCompPanel * p);
    extern int glCompSetRemovePanel(glCompSet * s, glCompPanel * p);
    extern int glCompPanelShow(glCompPanel * p);
    extern int glCompPanelHide(glCompPanel * p);
    extern void glCompSetPanelText(glCompPanel * p, char *t);

/*events*/
    extern int glCompPanelDraw(glCompObj * o);
    extern void glCompPanelClick(glCompObj * o, GLfloat x, GLfloat y,
				 glMouseButtonType t);
    extern void glCompPanelDoubleClick(glCompObj * obj, GLfloat x,
				       GLfloat y, glMouseButtonType t);
    extern void glCompPanelMouseDown(glCompObj * obj, GLfloat x, GLfloat y,
				     glMouseButtonType t);
    extern void glCompPanelMouseIn(glCompObj * obj, GLfloat x, GLfloat y);
    extern void glCompPanelMouseOut(glCompObj * obj, GLfloat x, GLfloat y);
    extern void glCompPanelMouseOver(glCompObj * obj, GLfloat x,
				     GLfloat y);
    extern void glCompPanelMouseUp(glCompObj * obj, GLfloat x, GLfloat y,
				   glMouseButtonType t);

#ifdef __cplusplus
}
#endif
#endif
