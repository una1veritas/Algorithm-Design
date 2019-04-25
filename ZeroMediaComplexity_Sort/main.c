#include <stdio.h>
#include <stdlib.h>

#include "sort_algorithms.h"

int main(int argc, char **argv) {
	unsigned int length = argc - 1;
	data array[length];
	for(unsigned int i = 0; i < length; ++i) {
		array[i] = atoi(argv[1+i]);
		printf("%d, ", array[i]);
	}
	printf("\n");

	while ( selectionSort(array, length) ) ;

	for(unsigned int i = 0; i < length; ++i) {
		printf("%d, ", array[i]);
	}
	printf("\n");

	return EXIT_SUCCESS;
}
