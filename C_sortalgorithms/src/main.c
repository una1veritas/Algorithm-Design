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

#include "binsearch.h"
#include "datadef.h"
#include "sort_algorithms.h"

long passcount[] = { 0, 0 };

int main(int argc, char **argv) {
	long num = argc - 1;
	data db[num];
	data * a[num];

	for(long i = 0; i < num; ++i) {
		db[i] = atol(argv[1+i]);
		printf("%ld, ", db[i]);
		a[i] = &db[i];
		//LList_append(&list, &db[i]);
	}
	printf("\n");

	//long range = 100;
	//counting_sort(a, num, 0, 101, keyval);
	//insertion_sort(a, num);
	//selection_sort_reverse(a, num);
	//heap_sort(a, num);
	//merge_sort(a, num);
	bucket_sort(a, num, 0, 201, keyval);
	//bucket_sort_fixed(a, num, 0, 101, keyval);

	for(long i = 0; i < num; ++i) {
		printf("%ld, ", *a[i]);
	}
	printf("\n");

	//printf("passcount [0] = %ld, [1] = %ld\n", passcount[0], passcount[1]);

	return EXIT_SUCCESS;
}

// 55 11 26 17 86 102 43 11 98
