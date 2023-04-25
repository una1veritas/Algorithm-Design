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
	long a[argc - 1];
	for(int i = 1; i < argc; ++i, ++num) {
		char * ptr;
		a[num] = strtol(argv[i], &ptr, 10);
		// printf("%ld ", a[num]);
		if ( *ptr != 0 ) {
			a[num] = 0;
			break;
		}
	}

	fprintf(stdout, "\nInput: \n");
	for(int i = 0; i < num; ++i) {
		fprintf(stdout, "%ld, ",a[i]);
	}
	fprintf(stdout, "\n");

	fprintf(stdout, "\nFind a subarray whose sum is the maximum.\n");

	long suffixsum[num+1];
	suffixsum[0] = 0; // suffixsum[i] is the best sum from a[0] to a[i-1]
	long best = 0;
	int best_left = 0, best_end = 0; // best_right is the next index of the index of the last element
	for(int last = 0; last < num; ++last) {
		fprintf(stdout, "a[%d] = %ld, suffixsum = %ld\n", last, a[last], suffixsum[last]);
		if ( suffixsum[last] + a[last] < a[last] ) {
			best_left = last;
			suffixsum[last+1] = a[last];
			best_end = last + 1;
		} else if ( suffixsum[last] + a[last] >= a[last] ) {
			suffixsum[last+1] = suffixsum[last] + a[last];
			best_end = last + 1;
		}
	}
	fprintf(stdout, "\nsuffixsum:\n");
	for(int i = 0; i <= num; i++) {
		fprintf(stdout, "%ld, ", suffixsum[i]);
	}
	fprintf(stdout, "\n");
	fprintf(stdout, "best subarray [%d, %d), the sum is %ld\n", best_left, best_end, best);
	return EXIT_SUCCESS;
}
