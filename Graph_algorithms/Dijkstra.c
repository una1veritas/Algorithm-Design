/*
 * dijkstra.c
 *
 *  Created on: 2023/01/16
 *      Author: Sin Shimozono
 */

#include <stdio.h>
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
	int l[g->vsize];
	for(int i = 0; i < g->vsize; ++i) {
		l[i] = INT_MAX;
		if ( g->vertices[i] == start )
			l[i] = 0;
	}

	int P[g->vsize];
	for(int i = 0; i < g->vsize; ++i)
		P[i] = 0;
	l[vertex_index(g, start)] = 0;
	while ( !(count_nonzero(P, g->vsize) < g->vsize) ) {
		// find the point u to which the path is shortest
		int vindex = -1;
		int lmin = INT_MAX;
		for(int i = 0; i < g->vsize; ++i) {
			if ( l[i] < lmin ) {
				vindex = i;
				lmin = l[i];
			}
		}
		printf("nearest vindex = %d, l[vindex] = %d\n", vindex, l[vindex]);
		if (vindex == -1)
			break; // unreachable points?
		P[vindex] = 1; // the dist. of the shortest path to u is determined.
		if (g->vertices[vindex] == goal)
			break;
		// for each point adjacent to u and in vertices
		//cout << "update adjacents. " << endl;
	for(const auto & v : ggraph.adjacent_nodes(u) ) {
		if ( vertices.contains(v) ) {  // C++20
			double dist_uv = ggraph.point(u).distance_to(ggraph.point(v));
			if ( el[v] > el[u] + dist_uv ) {
				el[v] = el[u] + dist_uv;
			}
		}
	}
}

// find the shortest path from the start to the goal by back-tracking

vector < uint64_t > path;
path.push_back(osmid_goal);
uint64_t curr_id = osmid_goal;
while (curr_id != osmid_start) {
for(const auto & adj : ggraph.adjacent_nodes(curr_id) ) {
	double dist = ggraph.point(adj).distance_to(ggraph.point(curr_id));
	if ( el[curr_id] == el[adj] + dist ) {
		curr_id = adj;
		path.push_back(adj);
	}
}
}
}

