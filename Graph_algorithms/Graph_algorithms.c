#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "simplegraph.h"

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
		anedge.src = u;
		anedge.dst = v;
		Graph_add_edge(&g,anedge);
		for( ; isoneof(*ptr, " ,\t\n"); ++ptr);   // " ,\t\n" をスキップ
	} while ( *ptr );

	Graph_print(&g);
	return 0;
}
