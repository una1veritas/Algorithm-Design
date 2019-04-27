#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mt19937ar.h"
#include "zmsort_algorithms.h"

int main(int argc, char **argv) {
	unsigned int length = argc - 1;

	if (length == 0) {
		return EXIT_FAILURE;
	} else if (length == 1) {
		length = atoi(argv[1]);
	}

	data array[length];
	if (length == argc - 1) {
		for(unsigned int i = 0; i < length; ++i)
			array[i] = atoi(argv[1+i]);
	} else {
		init_genrand((unsigned)time(NULL));
		srand((unsigned)time(NULL));
		for(unsigned int i = 0; i < length; ++i)
			array[i] = genrand_int32() % (length<<2);
	}
	printf(" input: ");
	for(unsigned int i = 0; i < min(length, 100); ++i) {
		printf("%d, ", array[i]);
	}
	printf("\n");

	while ( selectionSort(array, length) ) ;

	printf("result: ");
	for(unsigned int i = 0; i < min(length, 100); ++i) {
		printf("%d, ", array[i]);
	}
	printf("\n");

	return EXIT_SUCCESS;
}
