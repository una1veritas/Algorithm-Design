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

#include "datadef.h"
#include "sort_algorithm.h"

int lessthan(const data * x, const data * y) {
	return *x < *y;
}

long passcount[] = { 0, 0 };

int main(int argc, char **argv) {
	long num = argc - 1;
	data db[num];
	long idx[num];

	for(long i = 0; i < num; ++i) {
		idx[i] = i;
		db[i] = atoi(argv[1+i]);
		printf("%ld, ", db[i]);
	}
	printf("\n");

	insertion_sort(db, idx, num);
	//selection_sort(db, idx, num);
	//heap_sort(db, idx, num);

	for(long i = 0; i < num; ++i) {
		printf("%ld, ", db[idx[i]]);
	}
	printf("\n");

	//printf("passcount [0] = %ld, [1] = %ld\n", passcount[0], passcount[1]);

	return EXIT_SUCCESS;
}
