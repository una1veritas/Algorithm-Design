/*
 * binsearch.c
 *
 *  Created on: 2022/04/30
 *      Author: Sin Shimozono
 */

#include "datadef.h"
#include "sort_algorithm.h"

long binsearch(data a[], long idx[], data b, long l, long r) {
	printf("[%ld, %ld)\n", l, r);
	if (l >= r)
		return -1;
	if (r - l < 4) {
		for(; l < r; ++l) {
			printf("a[idx[%ld]] = %ld == %ld > ",l,a[idx[l]],b);
			if (a[idx[l]] == b)
				return l;
		}
		return -1;
	}
	long m = l + (r-l)/2;
	printf("m = %ld\n", m);
	if (b <= a[idx[m]]) {
		return binsearch(a,idx,b,l,m+1);
	}
	//else if (a[idx[m]] < b) {
	return binsearch(a,idx, b,m+1,r);
	//}
}
