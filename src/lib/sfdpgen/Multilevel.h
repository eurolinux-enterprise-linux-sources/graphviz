/* $Id: Multilevel.h,v 1.6 2009/06/03 01:10:54 ellson Exp $ $Revision: 1.6 $ */
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

#ifndef MULTILEVEL_H
#define MULTILEVEL_H

#include "SparseMatrix.h"

typedef struct Multilevel_struct *Multilevel;

struct Multilevel_struct {
  int level;/* 0, 1, ... */
  int n;
  SparseMatrix A;
  SparseMatrix P; 
  SparseMatrix R; 
  real *node_weights;
  Multilevel next;
  Multilevel prev;
  int delete_top_level_A;
  int coarsen_scheme_used;/* to get from previous level to here */
};

enum {MAX_IND_VTX_SET_U = -100, MAX_IND_VTX_SET_F = -1, MAX_IND_VTX_SET_C = 0};

enum {MAX_CLUSTER_SIZE = 4};

enum {EDGE_BASED_STA, COARSEN_INDEPENDENT_EDGE_SET, COARSEN_INDEPENDENT_EDGE_SET_HEAVEST_EDGE_PERNODE, COARSEN_INDEPENDENT_EDGE_SET_HEAVEST_EDGE_PERNODE_LEAVES_FIRST, COARSEN_INDEPENDENT_EDGE_SET_HEAVEST_EDGE_PERNODE_SUPERNODES_FIRST, COARSEN_INDEPENDENT_EDGE_SET_HEAVEST_EDGE_PERNODE_DEGREE_SCALED, COARSEN_INDEPENDENT_EDGE_SET_HEAVEST_CLUSTER_PERNODE_LEAVES_FIRST, EDGE_BASED_STO, VERTEX_BASED_STA, COARSEN_INDEPENDENT_VERTEX_SET, COARSEN_INDEPENDENT_VERTEX_SET_RS, VERTEX_BASED_STO, COARSEN_HYBRID};


struct Multilevel_control_struct {
  int minsize;
  real min_coarsen_factor;
  int maxlevel;
  int randomize;
  int coarsen_scheme;
};

typedef struct Multilevel_control_struct *Multilevel_control;

Multilevel_control Multilevel_control_new(void);

void Multilevel_control_delete(Multilevel_control ctrl);

void Multilevel_delete(Multilevel grid);

Multilevel Multilevel_new(SparseMatrix A, real *node_weights, Multilevel_control ctrl);

Multilevel Multilevel_get_coarsest(Multilevel grid);

void print_padding(int n);

#define Multilevel_is_finest(grid) (!((grid)->prev))
#define Multilevel_is_coarsest(grid) (!((grid)->next))

#endif
