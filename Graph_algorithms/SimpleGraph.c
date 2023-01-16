/*
 * SimpleGraph.c
 *
 *  Created on: 2023/01/08
 *      Author: Sin Shimozono
 */

#include <stdio.h>

#include "simplegraph.h"

void Graph_init(Graph * gp, Vertex v[], int n, Edge e[], int m) {
	gp->vsize = 0;
	gp->esize = 0;
	for(int i = 0; i < n; ++i) {
		Graph_add_vertex(gp, v[i]);
	}
	for(int i = 0; i < m; i += 1) {
		Graph_add_edge(gp, e[i]);
	}
	return;
}

void Graph_init_empty(Graph * gp) {
	gp->vsize = 0;
	gp->esize = 0;
	return;
}

int Graph_has_vertex(Graph * gp, Vertex a) {
	for(int i = 0; i < gp->vsize; ++i) {
		if ( gp->vertices[i] == a )
			return 1;
	}
	return 0;
}

// 無向グラフとしての隣接性
int Graph_adjacent(Graph * gp, Vertex a, Vertex b) {
	Vertex u, v;
	if (a < b) {
		u = a; v = b;
	} else {
		u = b; v = a;
	}
	if (u == v)
		return 1; // 自分自身は常に隣接
	int i;
	for(i = 0; i < gp->esize; ++i) {
		if ( gp->edges[i].src == u )
			break;
	}
	if ( gp->edges[i].src != u )
		return 0;
	for( ; i < gp->esize; ++i) {
		if ( gp->edges[i].src != u )
			break;
		if ( gp->edges[i].dst == v )
			return 1;
	}
	return 0;
}

// 有向グラフとしての隣接性
int Graph_adjacent_directed(Graph * gp, Vertex a, Vertex b) {
	Vertex u = a, v = b;
	if (u == v)
		return 1; // 自分自身は常に隣接
	int i;
	for(i = 0; i < gp->esize; ++i) {
		if ( gp->edges[i].src == u )
			break;
	}
	if ( gp->edges[i].src != u )
		return 0;
	for( ; i < gp->esize; ++i) {
		if ( gp->edges[i].src != u )
			break;
		if ( gp->edges[i].dst == v )
			return 1;
	}
	return 0;
}

void Graph_add_vertex(Graph * gp, int v) {
	int i;
	// インサーションソート（昇順）で追加
	for(i = 0; i < gp->vsize; i += 1) {
		if (gp->vertices[i] == v)
			return; // 既にある
		if (gp->vertices[i] > v)
			break;
	}
	if ( !(gp->vsize < MAX_VERTICES_SIZE) ) {
		printf("Error: The number of vertices has reached to MAX_VERTICES_SIZE.\n");
		return;
	}
	gp->vsize += 1;
	for(int j = gp->vsize - 1; j >= i; j -= 1) {
		gp->vertices[j] = gp->vertices[j-1];
	}
	gp->vertices[i] = v;
}

// 無向辺の追加
void Graph_add_edge(Graph * gp, Edge e) {
	int t;
	if ( e.src == e.dst )
		return;
	if ( !Graph_has_vertex(gp, e.src) || !Graph_has_vertex(gp, e.dst) )
		return;
	if ( e.src > e.dst ) { // 常に src < dst
		t = e.src; e.src = e.dst; e.dst = t;
	}
	// インサーションソート（辞書式昇順）で追加
	int i;
	for(i = 0; i < gp->esize; ++i) {
		if ( gp->edges[i].src == e.src && gp->edges[i].dst == e.dst ) {
			// すでにある
			return;
		}
		if ( gp->edges[i].src > e.src || (gp->edges[i].dst > e.dst) ) {
			// 追加する辺よりも後になる辺が見つかった
			break;
		}
	}
	gp->esize += 1;
	for(int j = gp->esize - 1; j >= i; j -= 1) {
		gp->edges[j] = gp->edges[j-1];
	}
	gp->edges[i] = e;
}

// 有向辺の追加
void Graph_add_directed_edge(Graph * gp, Edge e) {
	if ( e.src == e.dst )
		return;
	if ( !Graph_has_vertex(gp, e.src) || !Graph_has_vertex(gp, e.dst) )
		return;
	// インサーションソート（辞書式昇順）で追加
	int i;
	for(i = 0; i < gp->esize; ++i) {
		if ( gp->edges[i].src == e.src && gp->edges[i].dst == e.dst ) {
			// すでにある
			return;
		}
		if ( gp->edges[i].src > e.src || (gp->edges[i].dst > e.dst) ) {
			// 追加する辺よりも後になる辺が見つかった
			break;
		}
	}
	gp->esize += 1;
	for(int j = gp->esize - 1; j >= i; j -= 1) {
		gp->edges[j] = gp->edges[j-1];
	}
	gp->edges[i] = e;
}

void Graph_print(Graph * gp) {
	printf("G=({");
	for(int i = 0; i < gp->vsize; ++i) {
		printf("%d", gp->vertices[i]);
		if (i+1 < gp->vsize)
			printf(", ");
	}
	printf("}, {");
	for(int i = 0; i < gp->esize; ++i) {
		printf("(%d, %d)", gp->edges[i].src, gp->edges[i].dst);
		if (gp->edges[i].weight != 1) {
			printf(":%d",gp->edges[i].weight);
		}
		if (i+1 < gp->esize)
			printf(", ");
	}
	printf("})\n");
}
