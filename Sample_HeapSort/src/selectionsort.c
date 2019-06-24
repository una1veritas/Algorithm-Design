/*
 * selectionsort.c
 *
 *  Created on: 2019/06/23
 *      Author: Sin Shimozono
 */


#include "sorting.h"

void selectionSort(data a[], unsigned int n,
		int (*compare)(const void *, const void *) ) {
	data t;
	for(int i = n - 1; i >= 0; --i) {
		for(int j = 0; j < i; ++j) {
			if ( compare(&a[i], &a[j]) < 0 ) { /*  compare(a+i, a+j) でもよい */
				t = a[i]; a[i] = a[j]; a[j] = t;
			}
		}
	}
}
