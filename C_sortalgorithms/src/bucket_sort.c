/*
 * bucketsort.c
 */
#include <stdio.h>
#include <stdlib.h>

#include "datadef.h"
#include "vlarray.h"

#define BUCKET_MAXLENGTH 5

typedef struct {
	unsigned int length;
	data * darray[BUCKET_MAXLENGTH];
} Bucket5;

void bucket_sort_fixed(data * a[], long n, long range_origin, long range_width, int (*keyval)(const data * d)) {
	Bucket5 bucket[range_width];
	for(long i = 0; i < range_width; ++i) {
		bucket[i].length = 0;
	}
	for(long i = 0; i < n; ++i) {
		long index = keyval(a[i]) - range_origin;
		if ( bucket[index].length < BUCKET_MAXLENGTH ) {
			bucket[index].darray[bucket[index].length++] = a[i];
		} else {
			fprintf(stderr, "bucket overflow occurred.\n");
		}
	}
	long dstindex = 0;
	for(long i = 0; i < range_width; ++i) {
		for(unsigned int j = 0; j < bucket[i].length; ++j) {
			a[dstindex++] = bucket[i].darray[j];
		}
	}
}

void bucket_sort(data * a[], long n, long range_origin, long range_width, int (*keyval)(const data * d)) {
	vlarray bucket[range_width];
	for(long i = 0; i < range_width; ++i) {
		vlarray_init(& bucket[i], 4);
		// assumes the number of same data would be no greater than 4.
	}
	for(long i = 0; i < n; ++i) {
		long index = keyval(a[i]) - range_origin;
		vlarray_append(&bucket[index], a[i]);
	}
	long dstindex = 0;
	for(long i = 0; i < range_width; ++i) {
		for(unsigned int j = 0; j < bucket[i].n; ++j) {
			a[dstindex++] = bucket[i].a[j];
		}
		vlarray_delete(&bucket[i]);
	}

}

