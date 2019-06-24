/*
 * heapsort.c
 *
 *  Created on: 2019/06/23
 *      Author: Sin Shimozono
 */

#include <stdio.h>
#include "sorting.h"

void down_to_leaf(data a[], unsigned int i, unsigned int n, int (*comp)(const void *, const void *)) {
	unsigned int j;
	data t;
	while ( 1 ) {
		j = (i<<1) + 1; // the left child
		if ( !(j < n) )
			break;
		if ( j+1 < n ) { // i has the right child
			if ( comp(&a[j], &a[j+1]) < 0 )
				j += 1; // select the right child
		}
		if ( comp(&a[j], &a[i]) < 0 )
			break;
		//printf("<-> ");
		t = a[i]; a[i] = a[j]; a[j] = t;
		i = j;
	}
	//printf("\n");
}

void make_heap(data a[], unsigned int n, int (*comp)(const void *, const void *) ) {
	for(unsigned int i = (n-1)>>1; ; --i) {
		down_to_leaf(a, i, n, comp);
		if ( i == 0 )
			break;
	};
}


void heapSort(data a[], unsigned int n, int (*comp)(const void *, const void *) ){
	unsigned int i;
	data t;
	make_heap(a, n, comp);
	for(i = n - 1; i > 0; --i) {
		t = a[i]; a[i] = a[0]; a[0] = t;
		down_to_leaf(a, 0, i, comp);
	}
}

