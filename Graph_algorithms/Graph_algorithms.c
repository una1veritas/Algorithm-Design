#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VERTICES 16

typedef int Vertex;
typedef struct Edge {
	int u, v;
} Edge;

// 単純グラフ型
typedef struct Graph {
	int vertices[MAX_VERTICES];
	int vsize;
	Edge edges[MAX_VERTICES*(MAX_VERTICES-1)];
	int esize;
} Graph;

void Graph_add_vertex(Graph * gp, int v);
void Graph_add_edge(Graph * gp, Edge e);

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

int Graph_adjacent(Graph * gp, Vertex a, Vertex b) {
	Vertex u = a, v = b;
	if (u == v)
		return 1;
	if (u > v) {
		u = b; v = a;
	}
	int i;
	for(i = 0; i < gp->esize; ++i) {
		if ( gp->edges[i].u == u )
			break;
	}
	if ( gp->edges[i].u != u )
		return 0;
	for( ; i < gp->esize; ++i) {
		if ( gp->edges[i].u != u )
			break;
		if ( gp->edges[i].v == v )
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
	gp->vsize += 1;
	for(int j = gp->vsize - 1; j >= i; j -= 1) {
		gp->vertices[j] = gp->vertices[j-1];
	}
	gp->vertices[i] = v;
}

void Graph_add_edge(Graph * gp, Edge e) {
	int t;
	if ( e.u == e.v )
		return;
	if ( !Graph_has_vertex(gp, e.u) || !Graph_has_vertex(gp, e.v) )
		return;
	if ( e.u > e.v ) { // 常に u < v
		t = e.u; e.u = e.v; e.v = t;
	}
	// インサーションソート（辞書式昇順）で追加
	int i;
	for(i = 0; i < gp->esize; ++i) {
		if ( gp->edges[i].u == e.u && gp->edges[i].v == e.v ) {
			// すでにある
			return;
		}
		if ( gp->edges[i].u > e.u || (gp->edges[i].v > e.v) ) {
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
		printf("(%d, %d)", gp->edges[i].u, gp->edges[i].v);
		if (i+1 < gp->esize)
			printf(", ");
	}
	printf("})\n");
}

int isoneof(const char c, const char * charlist) {
	for(int i = 0; charlist[i] != 0; ++i) {
		if ( c == charlist[i] )
			return 1;
	}
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 3) {
		printf("Requires two arguments: (1) the number of vertices and (2) edge definitions in '1-2, 2-3,...' form .\n");
	}
	char buf[512];
	Graph g;
	Graph_init_empty(&g);
	if ( !sscanf(argv[1], "%511[0-9]", buf) ) {
		printf("No number of the vertices.\n");
		return EXIT_FAILURE;
	}
	int n = strtol(buf, NULL, 10);
	printf("n = %d\n", n);
	for(Vertex i = 0; i < n; ++i) {
		Graph_add_vertex(&g, i);
	}
	char * ptr = argv[2];
	unsigned long u, v;
	Edge anedge = {0, 0};
	do {
		for( ; isoneof(*ptr," ,\t\n"); ++ptr);   // " ,\t\n" をスキップ
		u = strtol(ptr, &ptr, 10);
		for( ; isoneof(*ptr, "- "); ++ptr );   // "- " をスキップ
		v = strtol(ptr, &ptr, 10);
		//printf("%lu, %lu\n", u, v);
		anedge.u = u;
		anedge.v = v;
		Graph_add_edge(&g,anedge);
		for( ; isoneof(*ptr, " ,\t\n"); ++ptr);   // " ,\t\n" をスキップ
	} while ( *ptr );

	Graph_print(&g);
	return 0;
}
