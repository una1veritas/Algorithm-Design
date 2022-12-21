#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void Graph_add_vertex(Graph * gp, int v) {
	int i;
	// インサーションソート（昇順）で追加
	for(i = 0; i < gp->vsize; i += 1) {
		if (gp->vertices[i] == v)
			return;
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
	if ( e.u > e.v ) {
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
		printf("%d, ", gp->vertices[i]);
	}
	printf("}, {");
	for(int i = 0; i < gp->esize; ++i) {
		printf("(%d, %d), ", gp->edges[i].u, gp->edges[i].v);
	}
	printf(")\n");
}

int isoneof(const char c, const char * charlist) {
	for(int i = 0; charlist[i] != 0; ++i) {
		if ( c == charlist[i] )
			return 1;
	}
	return 0;
}

int main(int argc, char **argv) {
	char buf[512];
	if ( !sscanf(argv[1], "%511[0-9]", buf) ) {
		printf("No number of the vertices.\n");
		return EXIT_FAILURE;
	}
	unsigned long n = strtol(buf, NULL, 10);
	printf("n = %ld\n", n);
	char * ptr = argv[2];
	unsigned long u, v;
	do {
		for( ; isoneof(*ptr," ,\t\n"); ++ptr);
		u = strtol(ptr, &ptr, 10);
		for( ; isoneof(*ptr, "- "); ++ptr );
		v = strtol(ptr, &ptr, 10);
		printf("%lu, %lu\n", u, v);
		for( ; isoneof(*ptr, " ,\t\n"); ++ptr);
	} while ( *ptr );
	int vertices[] = {1, 6, 2, 3, 4, 5, };
	Edge edges[] ={{1, 2}, {2, 3}, {3, 4}, {5, 6}, {6, 1}};
	Graph g;
	Graph_init(&g, vertices, 6, edges, 5);
	Graph_print(&g);
	return 0;
}
