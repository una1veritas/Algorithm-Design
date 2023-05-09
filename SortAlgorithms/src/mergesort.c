/*
 * mergesort.c
 *
 *  Created on: 2023/05/09
 *      Author: Sin Shimozono
 */

#include "datadef.h"

void merge(data * dst[], data * a[], int l, data * b[], int m) {
	int i, j, t;
	for (i = 0, j = 0, t = 0; i < l && j < m; t++) {
		if (i == l) {
			dst[t] = b[j];
			++j;
		} else if (j == m) {
			dst[t] = a[i];
			++i;
		} else {
			if ( lessthanoreq( a[i], b[j]) ) {
				dst[t] = a[i];
				++i;
			} else {
				dst[t] = b[j];
				++j;
			}
		}
	}
}

void merge_sort(data * array[], int n) {
	int i, j, l = n/2, m = n - l;
	data * a[l];
	data * b[m];

	if (n <= 1)
		return;
	printf("copying... %d, %d, %d\n", l, m, n);
	for (i = 0; i < l; i++) {
		a[i] = array[i];
	}
	for (j = 0; j < m; ++j, ++i) {
		printf("i = %d\n",i);
		b[j] = array[i];
	}
	merge_sort(a, l);
	merge_sort(b, m);
	merge(array, a, l, b, m);
	printf("mergerd.\n");
	return;
}

/*
void mergeSort(const data d[], int array[], int n, int (*compare)(const data *, const int, const int)) {
	int buf[n];
	int i, len, start, llen, rstart, rlen;
	const int bubble_len = 8;

	for (len = bubble_len; len < n; len = len<<1) {
		for (start = 0; start < n; start += (len<<1)) {
			llen = MIN(len, n - start);
			rstart = start + len;
			rlen = MIN(len, n - rstart );
			if ( len == bubble_len ) {
				bubbleSort(d, array+start, llen, compare);
				if ( rstart < n )
					bubbleSort(d, array+rstart, rlen, compare);
			}
			if ( rstart < n ) {
				// merge array[start,...,start+len-1] and array[start+len,...,start+len+rlen-1]
				merge(d, buf+start, array+start, llen, array+rstart, rlen, compare);
				// copy back
				for (i = 0; i < llen + rlen; i++)
					array[start+i] = buf[start+i];
			}
		}
	}
	return;
}
*/
