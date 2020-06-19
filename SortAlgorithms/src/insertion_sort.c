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
	long i, sorted_end;
	long t;
	for (sorted_end = 1; sorted_end < n; ++sorted_end) {
		printf("sorted_end = %ld\n", sorted_end);
		//++passcount[0];
		t = a[sorted_end];
		for (i = sorted_end; lessthan(d+t, d+a[i-1]) && i > 0; --i ) {
			printf("i = %ld, ",i);
			fflush(stdout);
			a[i] = a[i-1];
			//++passcount[1];
		}
		printf("i = %ld, ",i);
		fflush(stdout);
		a[i] = t;
	}
}
