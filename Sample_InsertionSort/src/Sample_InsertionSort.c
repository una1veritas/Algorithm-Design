/*
 ============================================================================
 Name        : Sample_InsertionSort.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/* counters by global variables */
unsigned long passcount[] = { 0, 0, };

typedef int data;
int lessthan(data x, data y) {
	return x < y;
}

void insertionSort(data a[], unsigned int n) {
	unsigned int i, sorted_end = 1;
	data t;
	while (sorted_end < n) {
		++passcount[0];
		if ( !lessthan(a[sorted_end-1], a[sorted_end]) ) {
			i = sorted_end;
			t = a[sorted_end];
			do {
				++passcount[1];
				a[i] = a[i-1];
				--i;
			} while(lessthan(t, a[i]) && i > 0);
			a[i] = t;
		}
		++sorted_end;
	}
}

int main(int argc, char **argv) {
	unsigned int length = argc - 1;
	data array[argc-1];
	for(unsigned int i = 0; i < length; ++i) {
		array[i] = atoi(argv[1+i]);
		printf("%d, ", array[i]);
	}
	printf("\n");
	insertionSort(array, length);

	for(unsigned int i = 0; i < length; ++i) {
		printf("%d, ", array[i]);
	}
	printf("\n");

	printf("passcount [0] = %u, [1] = %u\n", passcount[0], passcount[1]);

	return EXIT_SUCCESS;
}

/*
 3, 1, 6, 9, 8, 13, -5, 10, 2, 2,
-5, 2, 2, 1, 3, 8, 6, 10, 9, 13,
passcount [0] = 9, [1] = 25
 *
 *
 -1, 2, 2, 5, 6, 8, 9, 11, 11, 19, 22,
-1, 2, 2, 5, 6, 8, 9, 11, 11, 19, 22,
passcount [0] = 10, [1] = 2
 *
 *
 *
 33, 19, 11, 11, 9, 6, 4, 2, 2, -3,
-3, 2, 2, 4, 6, 9, 11, 11, 19, 33,
passcount [0] = 9, [1] = 45
 *
 */
