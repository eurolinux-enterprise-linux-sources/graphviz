/* $Id$ $Revision$ */
/* vim:set shiftwidth=4 ts=8: */

/*************************************************************************
 * Copyright (c) 2011 AT&T Intellectual Property 
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors: See CVS logs. Details at http://www.graphviz.org/
 *************************************************************************/

/*
 * Glenn Fowler
 * AT&T Bell Laboratories
 *
 * return current PATH
 */

#include <ast.h>

char *pathbin(void)
{
    register char *bin;

    static char *val;

    if ((!(bin = getenv("PATH")) || !*bin) && !(bin = val)) {
	bin = "/bin:/usr/bin:/usr/local/bin";
	val = bin;
    }
    return bin;
}
