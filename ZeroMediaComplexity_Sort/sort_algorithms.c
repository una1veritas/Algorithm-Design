/*
 * sort_algorithms.c
 *
 *  Created on: Apr 24, 2019
 *      Author: sin
 */

#include <stdio.h>

#include "sort_algorithms.h"

int lessthan(data x, data y) {
	return x < y;
}

unsigned int insertionSort(data a[], unsigned int n) {
	unsigned int i, sorted_end;
	data t;
	for (sorted_end = 1; lessthan(a[sorted_end-1], a[sorted_end])
							&& sorted_end < n; ++sorted_end) {
		++passcount[0];
	}
	printf("sorted_end = %d\n", sorted_end);
	if (sorted_end == n)
		return 0;

	i = sorted_end;
	t = a[sorted_end];
	do {
		++passcount[1];
		a[i] = a[i-1];
		--i;
	} while(lessthan(t, a[i]) && i > 0);
	a[i] = t;
	return 1;
}


