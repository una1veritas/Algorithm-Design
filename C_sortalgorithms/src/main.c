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

// compfunc
int equals(const void * x, const void * y) {
	const data * a = (const data *)x, * b = (const data *) y;
	return strcmp(a->name, b->name) == 0;
}

int lessthan(const void * x, const void * y) {
	const data * a = (const data *)x, * b = (const data *) y;
	return strcmp(a->name, b->name) < 0;
}

// hashfunc
long keyval(const void * x) {
	const char * str = ((const data *)x)->name;
	long t = 0;
	for (int i = 0; str[i]; ++i) {
		t *= 31;
		t += str[i];
	}
	return t;
}

int  fprintf_data(FILE * fp, const data * d) {
	//return fprintf(fp, "%s", *d);
	return fprintf(fp, "%s: %s", d->id, d->name);
}

int strpbrkncpy(char * dst, char * src, int n, const char * delimchars) {
	char * ptr = strpbrk(src, delimchars);
	int l = ptr - src;
	l = l > n ? n : l ;
	strncpy(dst, src, l);
	dst[l] = '\0';
	return l;
}

int main(int argc, char **argv) {
	long num = argc - 1;
	data db[num];
	data * a[num];

	for(long i = 0; i < num; ++i) {
		char * id = argv[1+i];
		char * name;
		int len = strpbrkncpy(db[i].id, id, 8, ",:");
		name = id + len + 1;
		strncpy(db[i].name, name, 15);
		db[i].name[15] = '\0';
		a[i] = &db[i];
		//LList_append(&list, &db[i]);
		fprintf_data(stdout, a[i]);
		printf(",\n");
	}
	printf("\n");

	//long range = 100;
	//insertion_sort(a, num, lessthan);
	selection_sort(a, num, lessthan);
	//heap_sort(a, num, lessthan);
	//merge_sort_recursive(a, num, lessthan);
	//merge_sort_doubles(a, num, lessthan);
	//bucket_sort(a, num, 0, 201, keyval);
	//bucket_sort_fixed(a, num, 0, 101, keyval);
	//counting_sort(a, num, 0, 101, keyval);
	//qsort(a, num, sizeof(a[0]), lessthan);

	printf("result:\n");
	for(long i = 0; i < num; ++i) {
		fprintf_data(stdout, a[i]);
		fprintf(stdout,",\n");
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

