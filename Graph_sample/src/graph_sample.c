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

int adjacent(edge * edges, int u, int v) {
	for(edge * ptr = edges; !(ptr->u == 0 && ptr->v == 0); ++ptr) {
		if ( (ptr->u == u && ptr->v == v) || (ptr->u == v && ptr->v == u) )
			return 1;
	}
	return 0;
}

int main(int agrc, char * argv[]) {
	const int size = 5; // 頂点数．辺の最大数は size*(size-1)/2
	char * labels[] = { "A", "B", "C", "D", "E" };      // 名前は size 個必要．

	// 辺を整数の組（構造体 edge 型）で，辺の集合をその配列で表す方法．
	edge edges[] = { {0,1}, {0,3}, {1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {0,0} };

	// 辺を隣接行列（size x size の整数の二次元配列）で表す方法
	int adjmatrix[size][size] = {
			{0,1,0,1,0},
			{1,0,1,1,1},
			{0,1,0,1,1},
			{1,0,1,0,0},
			{0,1,1,0,0},
	};

	// 辺を隣接リストで表す方法
	// 便宜的に size x size の配列に収めているが，本来は可変長
	int adjlist[size][size] = {
			{1, 3, 0},
			{2, 3, 4, 0},
			{3, 4, 0},
			{0},
			{0},
	};

	printf("%d\n", size);
	for(int i = 0; i < size; ++i)
		printf("%s\n", labels[i]);
	for(int i = 0; !(edges[i].u == 0 && edges[i].v == 0); ++i)
		printf("(%d, %d)\n", edges[i].u, edges[i].v);
	if (adjacent(edges, 3, 1)) {
		printf("yes\n");
	} else {
		printf("no\n");
	}
	return 0;
}
