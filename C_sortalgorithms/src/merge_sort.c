/*
 * mergesort.c
 *
 *  Created on: 2023/05/09
 *      Author: Sin Shimozono
 */

#include "datadef.h"

void merge(data * dst[], data * a[], int l, data * b[], int m) {
	int i, j, t;

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

void merge_sort(data * array[], int n) {
	int i, l = n/2, m = n - l;
	if (n <= 1)
		return;
	data ** a = array;     // & a[0] の意味
	data ** b = array + l; // & a[l] の意味
	merge_sort(a, l);
	merge_sort(b, m);
	data * temp[n];  // merge のための一時的な併合列. 関数終了時に解放される
	merge(temp, a, l, b, m);
	for(i = 0; i < n; ++i)
		array[i] = temp[i];
	return;
}

