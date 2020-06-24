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

#include "sort_algorithm.h"

void counting_sort(data d[], long index[], long n, long range, long (*keycode)(const data *)) {
	long number[range];
	long counter[range];

	for(long i = 0; i < range; ++i) {
		number[i] = 0;
	}
	for(long i = 0; i < n; ++i) {
		number[keycode(d+i)] += 1;
	}
	printf("\n");
	for(long i = 1; i < range; ++i) {
		number[i] += number[i-1];
		counter[i] = number[i-1];
	}
	counter[0] = 0;
	for(long i = 0; i < n; ) {
		long ix = keycode(d+index[i]);
		if ( counter[ix] != number[ix] ) {
			long t = index[counter[ix]];
			index[counter[ix]] = index[i];
			index[i] = t;
			counter[ix] += 1;
		} else {
			i += 1;
		}
	}
}
