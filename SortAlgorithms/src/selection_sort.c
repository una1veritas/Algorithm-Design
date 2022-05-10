/*
 * selelection_sort.c
 * selection sort sample
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "datadef.h"


void selection_sort(data * d[], long n) {
	data * t;
	for (long i = 0; i < n; ++i) {
		for (long j = i + 1; j < n; ++j) {
			if ( lessthan(d[j], d[i]) ) {
				t = d[i];
				d[i] = d[j];
				d[j] = t;
			}
		}
	}
	return;
}
