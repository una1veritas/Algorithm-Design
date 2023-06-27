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

tuple longest_increasing(const int a[], const int n) {
	tuple ans;
	ans.start = 0;
	ans.length = 1;
	int start = 0, length = 1;
	for(int i = 1; i < n; ++i) {
		if ( a[i-1] <= a[i] ) {
			length += 1;
			if ( length > ans.length ) {
				ans.start = start;
				ans.length = length;
			}
		} else {
			start = i;
			length = 1;
		}
		fprintf(stdout, "start = %d, length = %d\n", start, length);
	}
	return ans;
}
