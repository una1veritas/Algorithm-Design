#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort_algorithms.h"
//#include "mt19937ar.h"

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
		srand((unsigned)time(NULL));
		for(unsigned int i = 0; i < length; ++i)
			array[i] = rand() % (length<<1);
	}
	printf(" input: ");
	for(unsigned int i = 0; i < length; ++i) {
		printf("%d, ", array[i]);
	}
	printf("\n");

	while ( selectionSort(array, length) ) ;

	printf("result: ");
	for(unsigned int i = 0; i < length; ++i) {
		printf("%d, ", array[i]);
	}
	printf("\n");

	return EXIT_SUCCESS;
}
