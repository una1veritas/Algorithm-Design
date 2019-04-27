/*
 * zmsort_algorithms.c
 *
 *  Created on: Apr 24, 2019
 *      Author: sin
 */

#include "zmsort_algorithms.h"

#include <stdio.h>

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

void merge(data a[], unsigned int left, unsigned int right, unsigned int right_end, data buffer[]) {
	unsigned int mp = 0, lp = left, rp = right;
	while ( lp < right || rp < right_end ) {
		if (  lp < right && rp < right_end ) {
			if ( lessthan_or_equal(a[lp], a[rp]) ) {
				buffer[mp] = a[lp];
				++lp;
				++mp;
			} else {
				buffer[mp] = a[rp];
				++rp;
				++mp;
			}
		} else if ( lp < right ) {
			buffer[mp] = a[lp];
			++lp;
			++mp;
		} else { // right < right_end
			buffer[mp] = a[rp];
			++rp;
			++mp;
		}
	}
	for(lp = left, mp = 0; lp < right_end; ++lp, ++mp)
		a[lp] = buffer[mp];

}

unsigned int mergeSort(data a[], unsigned int n) {
	data t[n];
	unsigned int left_begin, left_end, right_begin, right_end;
	left_begin = 0;
	while (left_begin < n) {
		for(left_end = left_begin + 1; left_end < n && lessthan_or_equal(a[left_end-1], a[left_end]); ++left_end);
#ifdef DEBUG
		printf("left begin = %d, left end = %d, the end = %d.\n", left_begin, left_end, n);
#endif
		if ( left_end < n ) {
			right_begin = left_end;
			for(right_end = right_begin + 1; right_end < n && lessthan_or_equal(a[right_end-1], a[right_end]); ++right_end);
#ifdef DEBUG
			printf("%d - %d : %d - %d\n", left_begin, left_end, right_begin, right_end);
			for(int i = 0; i < n; ++i) {
				printf("%d, ",a[i]);
			}
			printf("\n");
			fflush(stdout);
#endif
			merge(a, left_begin, right_begin, right_end, t);
#ifdef DEBUG
			for(int i = 0; i < n; ++i) {
				printf("%d, ",a[i]);
			}
			printf("\n\n");
#endif
		} else if (left_begin == 0 && left_end == n) {
#ifdef DEBUG
			printf("the whole array has been sorted.\n");
#endif
			return 0;
		} else {
#ifdef DEBUG
			printf("right_begin reached to the end.\n");
#endif
			return 1;
		}
#ifdef DEBUG
		fflush(stdout);
#endif
		left_begin = right_end;
	}
	return 1;
}
