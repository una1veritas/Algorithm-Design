/*
 * dijkstra.c
 *
 *  Created on: 2023/01/16
 *      Author: Sin Shimozono
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "simplegraph.h"

int count_nonzero(int a[], int n) {
	int count = 0;
	for(int i = 0; i < n; ++i) {
		if ( a[i] != 0 )
			count += 1;
	}
	return count;
}

int vertex_index(Graph * g, int val) {
	int i;
	for (i = 0; i < g->vsize; ++i)
		if (g->vertices[i] == val)
			break;
	return i;
}

Vertex * Dijkstra(Graph *g, int start, int goal) {
	// 整数 0,...,g->vsize - 1 を点の表現とし，
	// 点（のラベル，名前）は g->vertices[i] で参照，
	// 隣接関係（辺）は (g->vertices[i], g->vertices[j]) で参照
	int l[g->vsize];
	for(int i = 0; i < g->vsize; ++i) {
		l[i] = INT_MAX;
		if ( g->vertices[i] == start )
			l[i] = 0;
	}

	int P[g->vsize]; // P[i] == 1 で i in P
	for(int i = 0; i < g->vsize; ++i)
		P[i] = 0;
	while ( !(count_nonzero(P, g->vsize) < g->vsize) ) {
		// find the point u to which the path is shortest
		int vindex = -1;
		int lmin = INT_MAX;
		for(int i = 0; i < g->vsize; ++i) {
			if ( P[i] == 0 && l[i] < lmin ) {
				vindex = i;
				lmin = l[i];
			}
		}
		printf("nearest vindex = %d, l[vindex] = %d\n", vindex, l[vindex]);
		if (vindex == -1) {
			printf("unreachable points exist.\n");
			return NULL; // unreachable points?
		}
		P[vindex] = 1; // the dist. of the shortest path to u is determined.
		/*
		 // abandon the remaining since the dist to goal has been determined.
		if ( g->vertices[vindex] == goal ) {
			// reached to the goral
			break;
		}
		*/
	}

	// backtrack
	int vindex = vertex_index(g, goal);
	int path_length = 0;
	Vertex * path = (Vertex *) malloc(sizeof(Vertex) * g->vsize);  // 長過ぎか
	path[path_length++] = vindex;
	while ( g->vertices[vindex] != start ) {
		for(int u = 0; u < g->vsize; ++u) {
			if ( Graph_adjacent(g, g->vertices[vindex], g->vertices[u]) == 1
					&& Graph_edge_weight(g, g->vertices[vindex], g->vertices[u]) + l[u] == l[vindex] ) {
				path[path_length++] = u;
				vindex = u;
			}
		}
	}
	path[path_length] = -1;
	return path;
}
