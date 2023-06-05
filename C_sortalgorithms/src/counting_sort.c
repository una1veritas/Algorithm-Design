/*
 ============================================================================
 Name        : C_CountingSort.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "datadef.h"
#include "sort_algorithms.h"

void counting_sort(data * a[], long n, long range_origin, long range_width, long (*keyval)(const data * d)) {
	data * result[n];
	long counter[range_width];

	for(long i = 0; i < range_width; ++i) {
		counter[i] = 0;
	}
	for(long i = 0; i < n; ++i) {
		++counter[keyval(a[i]) - range_origin];
	}
	// let counter[i] be the first position of the i-th element (keyvalue i ). counter[0] = 0.
	long prev = counter[0];
	counter[0] = 0;
	for(long i = 1; i < range_width; ++i) {
		long t = counter[i];
		counter[i] = prev;
		prev += t;
	}

	// move each element to the sorted array result[].
	for(long i = 0; i < n; ++i) {
		long ix = keyval(a[i]) - range_origin;
		result[counter[ix]++] = a[i];
	}
	// copy back to a[].
	for(long i = 0; i < n; ++i)
		a[i] = result[i];
}
