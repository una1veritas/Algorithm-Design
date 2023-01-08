/*
 * SimpleGraph.c
 *
 *  Created on: 2023/01/08
 *      Author: Sin Shimozono
 */

#ifndef SIMPLEGRAPH_H_
#define SIMPLEGRAPH_H_

// 点数最大 16 (0,...,15) の辺重み付き単純グラフ

#define MAX_VERTICES_SIZE 16

typedef int Vertex;
typedef struct Edge {
	int src, dst;
	int weight;
} Edge;

// 単純グラフ型
typedef struct Graph {
	int vertices[MAX_VERTICES_SIZE];
	int vsize;
	Edge edges[MAX_VERTICES_SIZE*(MAX_VERTICES_SIZE-1)];
	int esize;
} Graph;

void Graph_init(Graph * gp, Vertex v[], int n, Edge e[], int m);
void Graph_init_empty(Graph * gp);

int Graph_has_vertex(Graph * gp, Vertex a);
int Graph_adjacent(Graph * gp, Vertex a, Vertex b);
int Graph_adjacent_directed(Graph * gp, Vertex a, Vertex b);
void Graph_add_vertex(Graph * gp, int v);
// 無向辺の追加
void Graph_add_edge(Graph * gp, Edge e);
// 有向辺の追加
void Graph_add_directed_edge(Graph * gp, Edge e);
void Graph_print(Graph * gp);

#endif /* SIMPLEGRAPH_H_ */
