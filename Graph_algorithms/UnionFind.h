/*
 * UnionFind.h
 *
 *  Created on: 2023/01/08
 *      Author: Sin Shimozono
 */

#ifndef UNIONFIND_H_
#define UNIONFIND_H_

// A structure to represent a subset for union-find
typedef struct Subset {
	int parent;
	int rank;
} Subset;

// A utility function to find set of an element i
// (uses path compression technique)
int Find(Subset subsets[], int i);

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(Subset subsets[], int x, int y);

#endif /* UNIONFIND_H_ */
