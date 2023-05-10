/*
 * mergesort.c
 *
 *  Created on: 2023/05/09
 *      Author: Sin Shimozono
 */

#include "datadef.h"

void merge(data * dst[], data * a[], int l, data * b[], int m) {
	int i, j, t;
	/*
	printf("\nl = %d, m = %d\n",l,m);
	printf("merge a[] = \n");
	for(i = 0; i < l; ++i) {
		printf("%ld, ", *a[i]);
	}
	printf("\nwith b[] = \n");
	for(i = 0; i < m; ++i) {
		printf("%ld, ", *(b[i]));
	}
	fflush(stdout);
	*/
	for (i = 0, j = 0, t = 0; i < l || j < m; t++) {
		/*
		if (i < l)
			printf("\ni = %d, *a[i] = %ld\n",i, *(a[i]));
		if (j < m)
			printf("\nj = %d, *b[j] = %ld, t = %d\n", j, *(b[j]), t);
		fflush(stdout);
		*/
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
	/*
	printf("\ndst[] = \n");
	for(i = 0; i < l+m; ++i) {
		printf("%ld, ", *(dst[i]));
	}
	printf("\n");
	fflush(stdout);
	*/
}

void merge_sort(data * array[], int n) {
	int i, l = n/2, m = n - l;
	if (n <= 1)
		return;
	data ** a = &array[0];
	data ** b = &array[l];
	merge_sort(a, l);
	merge_sort(b, m);
	data * temp[n];
	merge(temp, a, l, b, m);
	for(i = 0; i < n; ++i)
		array[i] = temp[i];
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
