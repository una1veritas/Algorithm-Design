/*
 ============================================================================
 Name        : C_longest_increasing_subsequence.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char * argv[]) {
	int n = argc - 1;
	int a[n];

	fprintf(stdout,"n = %d\n", n);
	for(int i = 1, ix = 0; i < argc; ++i, ++ix) {
		a[ix] = (int) strtol(argv[i], NULL, 10);
		fprintf(stdout,"%d, ",a[ix]);
	}
	fprintf(stdout,"\n");

	int start_longest = 0, length_longest = 1;
	int start = 0, length = 1;
	for(int i = 1; i < n; ++i) {
		if ( a[i-1] <= a[i] ) {
			length += 1;
			if ( length > length_longest ) {
				start_longest = start;
				length_longest = length;
			}
		} else {
			start = i;
			length = 1;
		}
		fprintf(stdout, "start = %d, length = %d\n", start, length);
	}
	fprintf(stdout, "longest increasing sequence starts from %d with length %d.\n", start_longest, length_longest);
	return EXIT_SUCCESS;
}
