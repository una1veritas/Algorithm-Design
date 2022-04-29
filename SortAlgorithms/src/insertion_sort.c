/*
 ============================================================================
 Name        : Sample_InsertionSort.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "datadef.h"
#include "sort_algorithm.h"

void insertion_sort(const data d[], long a[], long n) {
	long i, t;
	for (long sorted_end = 1; sorted_end < n; ++sorted_end) {
		//++passcount[0];
		t = a[sorted_end];
		for (i = sorted_end; i > 0 && !lessthan(d+a[i-1], d+t); --i ) {
			a[i] = a[i-1];
			//++passcount[1];
		}
		a[i] = t;
	}
}
