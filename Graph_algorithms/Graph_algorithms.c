#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "simplegraph.h"
#include "kruskal.h"

int isoneof(const char c, const char * charlist) {
	for(int i = 0; charlist[i] != 0; ++i) {
		if ( c == charlist[i] )
			return 1;
	}
	return 0;
}

int main(int argc, char **argv) {
	if (argc < 3) {
		printf("Requires two arguments: (1) sequence \"0, 1, 2...\" of the vertices, and (2) edge definitions in \"1-2, 2-3,...\" form .\n");
	}

	Graph g;
	Graph_init_empty(&g);

	char * ptr;
	int u, v, w;
	// read the sequence of verices
	ptr = argv[1];
	do {
		for( ; isoneof(*ptr," ,\t\n"); ++ptr);   // " ,\t\n" をスキップ
		v = strtol(ptr, &ptr, 10);
		Graph_add_vertex(&g, v);
	} while ( *ptr );

	// read the sequences of weighted wdges
	ptr = argv[2];
	int found_colon;
	Edge anedge = {0, 0, 0};
	do {
		for( ; isoneof(*ptr," ,\t\n"); ++ptr);   // " ,\t\n" をスキップ
		u = strtol(ptr, &ptr, 10);
		for( ; isoneof(*ptr, "- "); ++ptr );   // "- " をスキップ
		v = strtol(ptr, &ptr, 10);
		found_colon = 0;
		// ": " をスキップ
		for( ; isoneof(*ptr, ": "); ++ptr ) {
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
		for( ; isoneof(*ptr, " ,\t\n"); ++ptr);   // " ,\t\n" をスキップ
	} while ( *ptr );

	Graph_print(&g);

	KruskalMST(&g);

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

