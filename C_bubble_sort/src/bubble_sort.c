/*
 ============================================================================
 Name        : C_bubble_sort.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char * const argv[]) {
	/*
	if ( !(argc > 1) ) {
		fprintf(stderr,"supply an input integer sequence to be sorted.");
		exit(EXIT_FAILURE);
	}
*/
	long a[argc-1];
	long n;

	for(n = 1; n < argc; ++n) {
		a[n - 1] = atol(argv[n]);
	}

	for(long i = 0; i < n; ++i)
		fprintf(stdout, "%ld, ", a[i]);
	fprintf(stdout,"\n");

	for(long i = 0; i < n; ++i) {
		for(long j = n - 1; j > i; --j) {
			if ( a[j-1] > a[j] ) {
				long t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	for(long i = 0; i < n; ++i)
		fprintf(stdout, "%ld, ", a[i]);
	fprintf(stdout,"\n");

	return EXIT_SUCCESS;
}
