/*
 * selelection_sort.c
 * selection sort sample
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "datadef.h"


void selection_sort(const data d[], long a[], long n) {
	long t;
	for (long i = 0; i < n; ++i) {
		for (long j = i + 1; j < n; ++j) {
			if (lessthan(&d[a[j]], &d[a[i]])) {
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
	return;
}
