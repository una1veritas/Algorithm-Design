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

#include "datadef.h"

/*
 * data 型用関数
 */
int eq_byname(const data * x, const data * y) {
	return strcmp(x->name, y->name) == 0;
}

int lessthan_byname(const data * x, const data * y) {
	return strcmp(x->name, y->name) < 0;
}

long keyval_byname(const data * x) {
	char * str = x->name;
	long t = 0;
	for (int i = 0; str[i]; ++i) {
		t+= str[i]*31;
	}
	return t;
}

int  fprintf_data(FILE * fp, const data * d) {
	return fprintf(fp, "%s", d->name);
}
/*
 * data 型用関数　おわり
 */

#include "binsearch.h"
#include "sort_algorithms.h"

long passcount[] = { 0, 0 };

int main(int argc, char **argv) {
	long num = argc - 1;
	data db[num];
	data * a[num];

	for(long i = 0; i < num; ++i) {
		db[i].id = atoi(argv[1+i]);
		strcpy(db[i].name, argv[1+i+1]);
		a[i] = &db[i];
		//LList_append(&list, &db[i]);
		fprintf_data(stdout, a[i]);
		printf(" ");
	}
	printf("\n");

	//long range = 100;
	//counting_sort(a, num, 0, 101, keyval);
	//insertion_sort_reverse(a, num);
	//selection_sort(a, num, (int (*)(const void *, const void *)) lessthan_byname);
	heap_sort(a, num, (int (*)(const void *, const void *)) lessthan_byname);
	//merge_sort_recursive(a, num);
	//merge_sort_doubles(a, num);
	//bucket_sort(a, num, 0, 201, keyval);
	//bucket_sort_fixed(a, num, 0, 101, keyval);

	printf("result:\n");
	for(long i = 0; i < num; ++i) {
		fprintf_data(stdout, a[i]);
		printf(", ");
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

