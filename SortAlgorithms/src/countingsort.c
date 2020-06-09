/*
 ============================================================================
 Name        : C_CountingSort.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "sortalgorithms.h"

typedef void * data;

long key(const data d) {
	return (long)((long long) d);
}

int main(int argc, char * argv[]) {
	long n = argc - 1;
	data d[n];

	printf("input:\n");
	for(int i = 0; i < n; ++i) {
		d[i] = (void*) (long long) atoi(argv[i+1]);
		printf("%ld, ", (long) (long long) d[i]);
	}
	printf("\n");

	countingSort(d, n, 20, key);


	printf("\noutput:\n");
	for(int i = 0; i < n; ++i) {
		printf("%ld, ", (long) (long long) d[i]);
	}
	printf("\n");

return EXIT_SUCCESS;
}
