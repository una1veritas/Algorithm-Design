#include <stdio.h>

#define MAX_VERTICES 16

typedef int Vertex;
typedef struct Edge {
	int u, v;
} Edge;

typedef struct Graph {
	int vertices[MAX_VERTICES];
	int vsize;
	Edge edges[MAX_VERTICES*(MAX_VERTICES-1)];
	int esize;
} Graph;

void Graph_int(Grapg * gp, Vertex v[], int n, Edge e[], int m) {
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

void graph_add_vertex(graph * g, int v) {
	int i;
	for(i = 0; i < g->vsize; i += 1) {
		if (g->vertices[i] == v)
			return;
		if (g->vertices[i] > v)
			break;
	}
	g->vsize += 1;
	for(int j = g->vsize - 1; j >= i; j -= 1) {
		g->vertices[j] = g->vertices[j-1];
	}
	g->vertices[i] = v;
}

void graph_add_edge(graph * g, edge e) {
	int i;
	if ( e[0] > e[1] ) {
		i = e[1]; e[1] = e[0]; e[0] = i;
	}
	for(i = 0; i < g->esize; i += 1) {
		if ( g->edges[i][0] == e[0] && g->edges[i][1] == e[1] )
			return;
		if ( g->edges[i][0] > e[0] || (g->edges[i][0] == e[0] && g->edges[i][1] > e[1]) )
			break;
	}
	g->esize += 1;
	for(int j = g->esize - 1; j >= i; j -= 1) {
		g->edges[j][0] = g->edges[j-1][0];
		g->edges[j][1] = g->edges[j-1][1];
	}
	g->edges[i][0] = e[0];
	g->edges[i][1] = e[1];
}



void graph_print(graph * g) {
	printf("({");
	for(int i = 0; i < g->vsize; ++i) {
		printf("%d, ", g->vertices[i]);
	}
	printf("}, {");
	for(int i = 0; i < g->esize; ++i) {
		printf("(%d, %d), ", g->edges[i][0], g->edges[i][1]);
	}
	printf(")\n");
}

int main(int argc, char **argv) {
	int v[] = {1, 6, 2, 3, 4, 5, };
	edge e[] ={{1, 2}, {2, 3}, {3, 4}, {5, 6}, {6, 1}};
	graph g = graph_init(v, 6, e, 5);
	graph_print(&g);
	return 0;
}
