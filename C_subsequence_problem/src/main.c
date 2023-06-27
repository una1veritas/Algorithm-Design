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
#include "subsequence_problem.h"

int main(const int argc, const char * argv[]) {
	int n = argc - 1;
	int a[n];

	fprintf(stdout,"n = %d\n", n);
	for(int i = 1, ix = 0; i < argc; ++i, ++ix) {
		a[ix] = (int) strtol(argv[i], NULL, 10);
		fprintf(stdout,"%d, ",a[ix]);
	}
	fprintf(stdout,"\n");

	tuple ans = largest_contiguous_sum(a, n);
	fprintf(stdout, "largest contiguous subsequence starts from %d with length %d, sum is %d.\n", ans.start, ans.length, ans.sum);

//	fprintf(stdout, "longest increasing sequence starts from %d with length %d.\n", ans.start, ans.length);
	return EXIT_SUCCESS;
}
