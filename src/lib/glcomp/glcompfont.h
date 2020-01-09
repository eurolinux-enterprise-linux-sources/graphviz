/* $Id: glcompfont.h,v 1.3 2009/10/15 17:21:19 arif Exp $Revision: */
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
#ifndef glCompFont_H
#define glCompFont_H

#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include "glpangofont.h"
typedef float GLfloat;
#else
#include <unistd.h>
#include <GL/gl.h>
#endif
#include "glcompdefs.h"
#include <GL/glut.h>

#ifdef __cplusplus
extern "C" {
#endif
    extern fontset_t *fontset_init(void);
    extern void free_font_set(fontset_t * fontset);
    extern void copy_font(glCompFont * targetfont,
			  const glCompFont * sourcefont);
    extern glCompFont *add_font(fontset_t * fontset, char *fontdesc,
				int fs);
    extern glCompFont *add_glut_font(fontset_t * fontset, void *glutfont);
    extern void glprintf(glCompFont *, GLfloat, GLfloat, GLfloat, GLfloat,
			 char *);
    extern void glprintfglut(void *font, GLfloat xpos, GLfloat ypos,
			     GLfloat zpos, char *bf);
    extern glCompFont *font_init(void);
    extern void fontColor(glCompFont * font, float r, float g, float b,
			  float a);
    extern int glCompLoadFontPNG(char *name, int id);
	extern glCompFont *new_font(glCompSet * s, char *text, glCompColor * c,glCompFontType type, char *fontdesc, int fs,int is2D);
    extern glCompFont *new_font_from_parent(glCompObj * o, char *text);
    extern void delete_font(glCompFont * f);
	extern void glCompDrawText(glCompFont * f,GLfloat x,GLfloat y);
	extern void glCompRenderText(glCompFont * f, glCompObj * parentObj);
	extern void glCompDrawText3D(glCompFont * f,GLfloat x,GLfloat y,GLfloat z,GLfloat w,GLfloat h);

#ifdef __cplusplus
}
#endif
#endif
