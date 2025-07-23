/*
 * selelection_sort.c
 * selection sort sample
 *
 */
#include <stdio.h>
#include <stdlib.h>

//#include "datadef.h"


void selection_sort(long a[], long n) {
	long i = 0, j = 0;
	long t;
	for (i = 0; i < n; ++i) {
		for (j = i + 1; j < n; ++j) {
			if ( a[i] > a[j] ) {
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
	return;
}

void selection_sort_reverse(long a[], long n) {
	long t;
	for (long i = n - 1; i > 0; --i) {
		for (long j = 0; j < i; ++j) {
			if ( a[j] > a[i] ) {
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
	return;
}

/*
 * 34, 67, 8, 44,
1: 0, 0
2: 3, 0
3: 3, 0
3: 3, 1
4: 3, 1
3: 3, 2
2: 2, 0
3: 2, 0
4: 2, 0
3: 2, 1
4: 2, 1
2: 1, 0
3: 1, 0
8, 34, 44, 67,
 *
 *
 *
34, 8, 44, 67,
1: 0, 0
2: 3, 0
3: 3, 0
3: 3, 1
3: 3, 2
2: 2, 0
3: 2, 0
3: 2, 1
2: 1, 0
3: 1, 0
4: 1, 0
8, 34, 44, 67,
 */
