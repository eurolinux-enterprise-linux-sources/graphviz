/* $Id: sparse_solve.h,v 1.6 2009/06/03 01:10:54 ellson Exp $ $Revision: 1.6 $ */
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


#ifndef SPARSE_SOLVER_H
#define SPARSE_SOLVER_H

#include "SparseMatrix.h"

enum {SOLVE_METHOD_CG};


typedef struct Operator_struct *Operator;

struct Operator_struct {
  void *data;
  real* (*Operator_apply)(Operator o, real *in, real *out);
};

real SparseMatrix_solve(SparseMatrix A, int dim, real *x0, real *rhs, real tol, int maxit, int method, int *flag);

#endif
 
