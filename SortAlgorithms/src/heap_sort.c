/*
 * heapchecker.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datadef.h"
#include "sort_algorithm.h"

int down_to_leaf(const data data[], long a[], long i, long n) {
	int j, t;
	for ( ;(j = (i<<1) + 1) < n ; i = j) {
		//printf("%s ", data[a[i]]);
		if ( (j + 1 < n) ) {
			if ( lessthan(data+a[j], data+a[j+1]) ) {
				j += 1;
			}
		}
		if ( lessthan(data+a[j], data+a[i]) )
			break;
		t = a[i], a[i] = a[j], a[j] = t;
	}
	return 1;
}

void make_heap(const data data[], long a[], long n) {
	long i;
	for (i = (n>>1); i > 0; --i) {
		down_to_leaf(data, a, i-1, n);
	}
	return;
}

void heap_sort(const data data[], long a[], long n) {
	long i, t;
	fprintf(stdout, "making heap..\n");
	make_heap(data, a, n);

	fprintf(stdout,"heap:\n");
	for(int j = 0; j < n; ++j) {
		fprintf_data(stdout, & data[a[j]]);
		fprintf(stdout, " ");
	}
	fprintf(stdout, "\n\n");

	for (i = n - 1; i > 0; --i) {
		// a[0] is always the maximum.
		t = a[0], a[0] = a[i], a[i] = t;
		down_to_leaf(data, a, 0, i);

		fprintf(stdout,"heap and sorted suffix [%ld, %ld):\n",i,n);
		for(int j = 0; j < n; ++j) {
			fprintf_data(stdout, &data[a[j]]);
			if (j+1 == i) {
				fprintf(stdout, "| ");
			} else {
				fprintf(stdout, " ");
			}
		}
		fprintf(stdout,"\n");
	}
	return;
}
