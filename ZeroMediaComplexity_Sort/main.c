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

	passcount[0] = 0;
	passcount[1] = 0;

	while ( insertionSort(array, length)) ;

	for(unsigned int i = 0; i < length; ++i) {
		printf("%d, ", array[i]);
	}
	printf("\n");

	printf("passcount [0] = %u, [1] = %u\n", passcount[0], passcount[1]);

	return EXIT_SUCCESS;
}
