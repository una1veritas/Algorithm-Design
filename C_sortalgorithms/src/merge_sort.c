/*
 * mergesort.c
 *
 *  Created on: 2023/05/09
 *      Author: Sin Shimozono
 */

#include "datadef.h"

/*
 * 長さ l の昇順列 a と長さ m の昇順列 b を dst に併合する
 */
void merge(data * dst[], data * a[], long l, data * b[], long m) {
	long i, j, t;

	// a[i] が列 a の先頭，l が a の長さ，b[j] が列 b の先頭，m が b の長さ，dst[t] が併合列 dst の末尾を表す．
	for (i = 0, j = 0, t = 0; i < l || j < m; t++) {
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

void merge_sort_recursive(data * array[], long n) {
	long i, l = n/2, m = n - l;
	if (n <= 1)
		return;
	data ** a = array;     // & a[0] の意味
	data ** b = array + l; // & a[l] の意味
	merge_sort_recursive(a, l);
	merge_sort_recursive(b, m);
	data * temp[n];  // merge のための併合列の置き場所. 関数終了時に解放
	merge(temp, a, l, b, m);
	for(i = 0; i < n; ++i)
		array[i] = temp[i];
	return;
}


void merge_sort_doubles(data * array[], long n) {
	data * tmp[n/2 + 1];
	long l, i, right_begin, right_length, t;

	printf("n = %ld\n", n);
	for(l = 1; l < n; l <<= 1) {
		printf("l = %ld\n", l);
		// (log n) loop
		for(i = 0; i < n; i += (l<<1) ) {
			// (n / (2l)) loop
			right_begin = i + l;
			printf("left = %ld, right = %ld\n", i, right_begin);
			if ( right_begin >= n ) {
				printf("right is empty\n");
				break;
			}
			right_length = (n < right_begin + l) ? n - right_begin : l; // min{ }
			printf("right_length = %ld\n", right_length);
			fflush(stdout);
			for(t = 0; t < n; ++t) {
				fprintf_data(stdout, array[t]);
				printf(" ");
			}
			printf("\n");
			fflush(stdout);
			merge(tmp, array + i, l, array + right_begin, right_length);
			for(t = 0; t < n; ++t) {
				fprintf_data(stdout, array[t]);
				printf(" ");
			}
			printf("\n");
			fflush(stdout);
			printf("right_length = %ld\n", right_length);
			fflush(stdout);
			printf("now copying back. %ld\n", l + right_length);
			fflush(stdout);
			for(t = 0; t < l + right_length; ++t) {
				printf("i = %ld, t = %ld\n", i, t);
				array[i+t] = tmp[t];
			}
		}
	}
	return;
}

