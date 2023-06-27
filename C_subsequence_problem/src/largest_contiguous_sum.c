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

tuple largest_contiguous_sum(const int a[], const int n) {
	tuple ans;
	ans.start = 0;
	ans.length = 1;
	ans.sum = a[0];
	int start = 0, length = 1, sum = a[0];
	for(int i = 1; i < n; ++i) {
		if ( sum + a[i] < a[i] ) {
			start = i;
			length = 1;
			sum = a[i];
		} else {
			length += 1;
			sum += a[i];
		}
		if (sum > ans.sum) {
			ans.sum = sum;
			ans.start = start;
			ans.length = length;
		}
	}
	return ans;
}
