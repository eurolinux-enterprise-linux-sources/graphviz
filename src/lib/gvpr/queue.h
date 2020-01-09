/* $Id: queue.h,v 1.1 2009/06/23 22:12:55 erg Exp $ $Revision: 1.1 $ */
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

#ifndef QUEUE_H
#define QUEUE_H

#include "cgraph.h"

    typedef Dt_t queue;

    extern queue *mkQ(Dtmethod_t *);
    extern void push(queue *, void *);
    extern void *pop(queue *, int remove);
    extern void freeQ(queue *);

/* pseudo-functions:
extern queue* mkStack();
extern queue* mkQueue();
extern void* pull(queue*);
extern void* head(queue*);
 */

#define mkStack()  mkQ(Dtstack)
#define mkQueue()  mkQ(Dtqueue)
#define pull(q)  (pop(q,1))
#define head(q)  (pop(q,0))

#endif

#ifdef __cplusplus
}
#endif
