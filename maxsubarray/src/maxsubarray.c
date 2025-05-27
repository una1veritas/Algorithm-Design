/*
 ============================================================================
 Name        : maxsubarray.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	if ( argc <= 1 ) {
		fprintf(stderr,"A list of integers is requested.\n");
		return EXIT_FAILURE;
	}

	int num = 0;
	int a[argc - 1];
	for(int i = 1; i < argc; ++i, ++num) {
		char * ptr;
		a[num] = (int) strtol(argv[i], &ptr, 10);
		// printf("%d ", a[num]);
		if ( *ptr != 0 ) {
			a[num] = 0;
			break;
		}
	}

	fprintf(stdout, "\nInput: \n");
	for(int i = 0; i < num; ++i) {
		fprintf(stdout, "%d, ",a[i]);
	}
	fprintf(stdout, "\n");

	fprintf(stdout, "\nFind a subarray whose sum is the maximum.\n");

	int subsum[num];
	int max_start = 0, max_last = 0, max_sum = a[0];
	int start, last;
	subsum[0] = a[0];
	for(last = 1, start = 0; last < num; ++last) {
		if ( subsum[last-1] + a[last] >= a[last] ) {
			subsum[last] = subsum[last-1] + a[last];
		} else {
			subsum[last] = a[last];
			start = last;
		}
		if ( subsum[last] > max_sum ) {
			max_start = start, max_last = last, max_sum = subsum[last];
		}
		fprintf(stdout, "subsum[%d] = %d, max_start = %d, max_last = %d, max_sum = %d\n", last, subsum[last], max_start, max_last, max_sum);
	}
	fprintf(stdout, "\nsubsum:\n");
	for(int i = 0; i <= num; i++) {
		fprintf(stdout, "%d, ", subsum[i]);
	}
	fprintf(stdout, "\n");
	fprintf(stdout, "best subarray max last = %d, max_length = %d, the sum is %d\n", max_last, max_length, max_sum);
	return EXIT_SUCCESS;
}
