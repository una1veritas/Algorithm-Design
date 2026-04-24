/*
 ============================================================================
 Name        : main_test.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "binsearch.h"
#include "datadef.h"
#include "sort_algorithms.h"

long passcount[] = { 0, 0 };

int strncpytochr(char * dst, char * src, int n, char delim) {
	int pos;
	for (pos = 0; src[pos] != delim && src[pos] != '\0' && pos < n; ++pos) {
		dst[pos] = src[pos];
	}
	dst[pos] = '\0';
	return pos;
}

int main(int argc, char **argv) {
	long num = argc - 1;
	data db[num];
	data * a[num];

	for(long i = 0; i < num; ++i) {
		char * id = argv[1+i];
		char * name;
		int len = strncpytochr(db[i].id, id, 8, ':');
		name = id + len + 1;
		strncpy(db[i].name, name, 15);
		db[i].name[15] = '\0';
		a[i] = &db[i];
		//LList_append(&list, &db[i]);
		fprintf_data(stdout, a[i]);
		printf(", ");
	}
	printf("\n");

	//long range = 100;
	//counting_sort(a, num, 0, 101, keyval);
	insertion_sort(a, num, lessthan);
	//selection_sort(a, num, lessthan);
	//heap_sort(a, num, lessthan);
	//merge_sort_recursive(a, num);
	//merge_sort_doubles(a, num);
	//bucket_sort(a, num, 0, 201, keyval);
	//bucket_sort_fixed(a, num, 0, 101, keyval);

	printf("result:\n");
	for(long i = 0; i < num; ++i) {
		fprintf_data(stdout, a[i]);
		fprintf(stdout,", ");
	}
	printf("\n");

	//printf("passcount [0] = %ld, [1] = %ld\n", passcount[0], passcount[1]);

	return EXIT_SUCCESS;
}

// 55 11 26 17 86 102 43 11 98
/*
 * hektor, summicron, elmarit, nokton, planar, sonnar, distagon, xenotar, tessar,
making heap..
heap:
xenotar tessar sonnar summicron planar elmarit distagon nokton hektor

result:
distagon, elmarit, hektor, nokton, planar, sonnar, summicron, tessar, xenotar,
 *
 */

/*
 * summilux,, elmar,, noctilux,, planar,, sonnar,, distagon,, xenotar,, tessar,
making heap..
heap:
xenotar, tessar summilux, planar, sonnar, distagon, noctilux, elmar,

result:
distagon,, elmar,, noctilux,, planar,, sonnar,, summilux,, tessar, xenotar,,
 *
 */

