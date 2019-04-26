/*
 * sort_algorithms.c
 *
 *  Created on: Apr 24, 2019
 *      Author: sin
 */

#include <stdio.h>

#include "sort_algorithms.h"

unsigned int lessthan(data x, data y) {
	return x < y;
}

unsigned int lessthan_or_equal(data x, data y) {
	return (x < y) || (x == y);
}

unsigned int insertionSort(data a[], unsigned int n) {
	unsigned int sorted_end;
	data t;
	for (sorted_end = 1; sorted_end < n
			&& lessthan_or_equal(a[sorted_end-1], a[sorted_end]); ++sorted_end);
	if ( sorted_end == n )
		return 0;

	t = a[sorted_end];
	do {
		a[sorted_end] = a[sorted_end-1];
		--sorted_end;
	} while(lessthan(t, a[sorted_end]) && sorted_end > 0);
	a[sorted_end] = t;

	return 1;
}


unsigned int selectionSort(data a[], unsigned int n) {
	unsigned int i, imin, sorted_end;
	data t;
	for (sorted_end = 1; sorted_end < n
			&& lessthan_or_equal(a[sorted_end-1], a[sorted_end]); ++sorted_end);
//	printf("sorted_end: %d\n", sorted_end);
	if ( sorted_end == n )
		return 0;

	imin = sorted_end;
	for(i = sorted_end + 1; i < n; ++i)
		if ( lessthan(a[i], a[imin]) ) {
			imin = i;
		}
//	printf("imin = %d\n", imin);
	for(i = 0; i < sorted_end && lessthan_or_equal(a[i], a[imin]); ++i);
//	printf("swap: %d\n", i);
	t = a[i];
	a[i] = a[imin];
	a[imin] = t;
	return 1;
}

unsigned int mergeSort(data a[], unsigned int n) {
	data t[n];
	unsigned int left_begin, left_end, right_begin, right_end;

	return 0;
}
