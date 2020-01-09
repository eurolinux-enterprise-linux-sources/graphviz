/* $Id: fPQ.h,v 1.3 2009/06/03 01:10:53 ellson Exp $Revision: */
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

#include <memory.h>
#include <stdio.h>

/* Priority queue:
 * To work, the following have to be defined before this file is
 * included:
 *   - PQTYPE   : type of object stored in the queue
 *   - PQVTYPE  : type of priority value
 *   - N_VAL(pq,n) : macro for (negative) priority value of object n in pq
 *   - N_IDX(pq,n) : macro for integer index > 0 of n in pq
 *   - guard, type PQTYPE, with N_VAL(guard) == 0
 *
 * Priorities are stored as negative numbers, with the item with the least
 * negative priority at the head (just after the guard).
 */

#ifdef PQ_TYPES
typedef struct {
    PQTYPE*  pq;
    int     PQcnt;
    int     PQsize;
} PQ;
#endif

#ifdef PQ_CODE
static void
PQgen(PQ* pq, int sz, PQTYPE guard)
{
    pq->pq = N_NEW(sz+1,PQTYPE);
    pq->pq[0] = guard;
    pq->PQsize = sz;
    pq->PQcnt = 0;
}

static void
PQfree(PQ* pq, int freeAll)
{
    free (pq->pq);
    if (freeAll) free (pq);
}

static void
PQinit(PQ* pq)
{
    pq->PQcnt = 0;
}

#ifdef PQCHECK
static int
PQcheck (PQ* pq)
{
    int i;
 
    for (i = 1; i <= pq->PQcnt; i++) {
	if (N_IDX(pq,pq->pq[i]) != i) {
	    return 1;
	}
    }
    return 0;
}
#endif

static void
PQupheap(PQ* ppq, int k)
{
    PQTYPE* pq = ppq->pq;
    PQTYPE x = pq[k];
    PQVTYPE v = N_VAL(ppq,x);
    int	 next = k/2;
    PQTYPE  n;
    
    while (N_VAL(ppq,n = pq[next]) < v) {
	pq[k] = n;
	N_IDX(ppq,n) = k;
	k = next;
	next /= 2;
    }
    pq[k] = x;
    N_IDX(ppq,x) = k;
}

static void
PQinsert(PQ* pq, PQTYPE np)
{
    if (pq->PQcnt == pq->PQsize) {
	fprintf (stderr, "Heap overflow\n");
	exit (1);
    }
    pq->PQcnt++;
    pq->pq[pq->PQcnt] = np;
    PQupheap (pq, pq->PQcnt);
#ifdef PQCHECK
    PQcheck(pq);
#endif
}

static void
PQdownheap (PQ* ppq, int k)
{
    PQTYPE*  pq = ppq->pq;
    PQTYPE x = pq[k];
    PQVTYPE v = N_VAL(ppq,x);
    int	  lim = ppq->PQcnt/2;
    PQTYPE n;
    int	   j;

    while (k <= lim) {
	j = k+k;
	n = pq[j];
	if (j < ppq->PQcnt) {
	    if (N_VAL(ppq,n) < N_VAL(ppq,pq[j+1])) {
		j++;
		n = pq[j];
	    }
	}
	if (v >= N_VAL(ppq,n)) break;
	pq[k] = n;
	N_IDX(ppq,n) = k;
	k = j;
    }
    pq[k] = x;
    N_IDX(ppq,x) = k;
}

static PQTYPE
PQremove (PQ* pq)
{
    PQTYPE n;

    if (pq->PQcnt) {
	n = pq->pq[1];
	pq->pq[1] = pq->pq[pq->PQcnt];
	pq->PQcnt--;
	if (pq->PQcnt) PQdownheap (pq, 1);
#ifdef PQCHECK
	PQcheck(pq);
#endif
	return n;
    }
    else return pq->pq[0];
}

static void
PQupdate (PQ* pq, PQTYPE n, PQVTYPE d)
{
    N_VAL(pq,n) = d;
    PQupheap (pq, N_IDX(pq,n));
#ifdef PQCHECK
    PQcheck(pq);
#endif
}

#ifdef DEBUG

static void
PQprint (PQ* pq)
{
    int	i;
    PQTYPE  n;

    fprintf (stderr, "Q: ");
    for (i = 1; i <= pq->PQcnt; i++) {
	n = pq->pq[i];
	fprintf (stderr, "(%d:%f) ", N_IDX(pq,n), N_VAL(pq,n));
    }
    fprintf (stderr, "\n");
}
#endif
#endif

