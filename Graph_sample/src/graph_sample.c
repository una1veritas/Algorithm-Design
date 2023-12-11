//============================================================================
// Name        : Graph_sample.c
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : A simple program dealing with graphs.
//============================================================================

#include <stdio.h>

struct edge {
	int u, v;
};
typedef struct edge edge;

int adjacent_vertices(edge * edges, int u, int v) {
	for(edge * ptr = edges; !(ptr->u == 0 && ptr->v == 0); ++ptr) {
		if ( (ptr->u == u && ptr->v == v) || (ptr->u == v && ptr->v == u) )
			return 1;
	}
	return 0;
}

int main(int agrc, char * argv[]) {
	int size = 5;
	char * labels[] = { "A", "B", "C", "D", "E" };      // 名前は size 個必要．
	edge edges[] = { {0,1}, {0,2}, {1,3}, {2,3}, {0, 0} };    // 長さ 2 の配列が一つの辺．

	printf("%d\n", size);
	for(int i = 0; i < size; ++i)
		printf("%s\n", labels[i]);
	for(int i = 0; edges[i].u != 0 || edges[i].v != 0; ++i)
		printf("(%d, %d)\n", edges[i].u, edges[i].v);
	if (adjacent_vertices(edges, 3, 1)) {
		printf("yes\n");
	} else {
		printf("no\n");
	}
	return 0;
}
