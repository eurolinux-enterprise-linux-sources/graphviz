/* $Id: vmclear.c,v 1.3 2009/06/03 01:10:55 ellson Exp $ $Revision: 1.3 $ */
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

#include	"vmhdr.h"

/*	Clear out all allocated space.
**
**	Written by Kiem-Phong Vo, kpv@research.att.com, 01/16/94.
*/
#if __STD_C
int vmclear(Vmalloc_t * vm)
#else
int vmclear(vm)
Vmalloc_t *vm;
#endif
{
    reg Seg_t *seg;
    reg Seg_t *next;
    reg Block_t *tp;
    reg size_t size, s;
    reg Vmdata_t *vd = vm->data;

    if (!(vd->mode & VM_TRUST)) {
	if (ISLOCK(vd, 0))
	    return -1;
	SETLOCK(vd, 0);
    }

    vd->free = vd->wild = NIL(Block_t *);
    vd->pool = 0;

    if (vd->mode & (VM_MTBEST | VM_MTDEBUG | VM_MTPROFILE)) {
	vd->root = NIL(Block_t *);
	for (s = 0; s < S_TINY; ++s)
	    TINY(vd)[s] = NIL(Block_t *);
	for (s = 0; s <= S_CACHE; ++s)
	    CACHE(vd)[s] = NIL(Block_t *);
    }

    for (seg = vd->seg; seg; seg = next) {
	next = seg->next;

	tp = SEGBLOCK(seg);
	size = seg->baddr - ((Vmuchar_t *) tp) - 2 * sizeof(Head_t);

	SEG(tp) = seg;
	SIZE(tp) = size;
	if ((vd->mode & (VM_MTLAST | VM_MTPOOL)))
	    seg->free = tp;
	else {
	    SIZE(tp) |= BUSY | JUNK;
	    LINK(tp) = CACHE(vd)[C_INDEX(SIZE(tp))];
	    CACHE(vd)[C_INDEX(SIZE(tp))] = tp;
	}

	tp = BLOCK(seg->baddr);
	SEG(tp) = seg;
	SIZE(tp) = BUSY;
    }

    CLRLOCK(vd, 0);
    return 0;
}
