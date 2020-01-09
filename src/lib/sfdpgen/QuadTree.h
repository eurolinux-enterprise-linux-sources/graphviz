/* $Id: QuadTree.h,v 1.6 2009/06/03 01:10:54 ellson Exp $ $Revision: 1.6 $ */
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

#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "LinkedList.h"
#include "sfdpinternal.h"
#include <stdio.h>

typedef struct QuadTree_struct *QuadTree;

struct QuadTree_struct {
  /* a data structure containing coordinates of n items, their average is in "average".
     The current level is a square or cube of width "width", which is subdivided into 
     2^dim QuadTrees qts. At the last level, all coordinates are stored in a single linked list l. 
     total_weight is the combined weights of the nodes */
  int n;/* number of items */
  real total_weight;
  int dim;
  real *center;/* center of the bounding box, array of dimension dim. Allocated inside */
  real width;/* center +/- width gives the lower/upper bound, so really width is the 
		"radius" */
  real *average;/* the average coordinates. Array of length dim. Allocated inside  */
  QuadTree *qts;/* subtree . If dim = 2, there are 4, dim = 3 gives 8 */
  SingleLinkedList l;
  int max_level;
  void *data;
};


QuadTree QuadTree_new(int dim, real *center, real width, int max_level);

void QuadTree_delete(QuadTree q);

QuadTree QuadTree_add(QuadTree q, real *coord, real weight, int id);/* coord is copied in */

void QuadTree_print(FILE *fp, QuadTree q);

QuadTree QuadTree_new_from_point_list(int dim, int n, int max_level, real *coord, real *weight);

real point_distance(real *p1, real *p2, int dim);

void QuadTree_get_supernodes(QuadTree qt, real bh, real *point, int nodeid, int *nsuper, 
			     int *nsupermax, real **center, real **supernode_wgts, real **distances, real *counts, int *flag);

void QuadTree_get_repulvice_force(QuadTree qt, real *force, real *x, real bh, real p, real KP, real *counts, int *flag);
#endif
