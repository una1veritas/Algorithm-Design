#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Dijkstra.h"
#include "simplegraph.h"

int oneof(const char c, const char * charlist) {
	for(int i = 0; charlist[i] != 0; ++i) {
		if ( c == charlist[i] )
			return 1;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc < 6) {
		printf("Requires four arguments: (1) sequence \"0, 1, 2...\" of the vertices, and (2) edge definitions in \"1-2:3, 2-3:1,...\" form, (3) start point and (4) goal point.\n");
	}

	Graph g;
	Graph_init_empty(&g);

	int start = 0, goal = 0;
	char * ptr;
	int u, v, w;
	// 点の列を読み取る
	ptr = argv[1];
	do {
		for( ; oneof(*ptr," ,\t\n"); ++ptr);   // " ,\t\n" をスキップ
		v = strtol(ptr, &ptr, 10);
		Graph_add_vertex(&g, v);
	} while ( *ptr );

	// 重みつき辺の列を読み取る
	ptr = argv[2];
	int found_colon;
	Edge anedge = {0, 0, 0};
	do {
		for( ; oneof(*ptr," ,\t\n"); ++ptr);   // " ,\t\n" をスキップ
		u = strtol(ptr, &ptr, 10);
		for( ; oneof(*ptr, "- "); ++ptr );   // "- " をスキップ
		v = strtol(ptr, &ptr, 10);
		found_colon = 0;
		// ": " をスキップ
		for( ; oneof(*ptr, ": "); ++ptr ) {
			if (*ptr == ':')
				found_colon = 1;
		}
		if (found_colon) {
			w = strtol(ptr, &ptr, 10);
		} else {
			w = 1;
		}
		anedge.src = u;
		anedge.dst = v;
		anedge.weight = w;
		Graph_add_edge(&g, anedge);
		for( ; oneof(*ptr, " ,\t\n"); ++ptr);   // " ,\t\n" をスキップ
	} while ( *ptr );

	// 出発点、到達点を読み取る
	start = strtol(argv[3], NULL, 10);
	goal = strtol(argv[4], NULL, 10);

	// 入力されたグラフの定義を表示
	Graph_print(&g);

	// ダイクストラのアルゴリズムを呼び出し
	Vertex * spath = Dijkstra(&g, start, goal);

	printf("\nShortest path: \n");
	for(int i = 0; spath[i] != -1; ++i) {
		printf("%d, ", spath[i]);
	}
	printf("\n");

	free(spath);

	return 0;
}

/* Let us create following weighted graph
		10
	0--------1
	| \	 |
	6| 5\ |15
	|	 \ |
	2--------3
		4

"0, 1, 2, 3" "0-1:10, 0-2:6, 0-3: 5, 1 - 3 : 15, 2 - 3: 4"
*/

