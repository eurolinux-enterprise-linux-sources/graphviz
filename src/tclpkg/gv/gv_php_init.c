/* $Id: gv_php_init.c,v 1.4 2009/06/03 01:10:58 ellson Exp $ $Revision: 1.4 $ */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2008 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/

#include <php.h>
#include "gvc.h"
#include "gvplugin.h"
#include "gvcjob.h"
#include "gvcint.h"

static size_t gv_string_writer (GVJ_t *job, const char *s, size_t len)
{
    return PHPWRITE(s, len);
}

static size_t gv_channel_writer (GVJ_t *job, const char *s, size_t len)
{
    return PHPWRITE(s, len);
}

void gv_string_writer_init(GVC_t *gvc)
{
    gvc->write_fn = gv_string_writer;
}

void gv_channel_writer_init(GVC_t *gvc)
{
    gvc->write_fn = gv_channel_writer;
}

