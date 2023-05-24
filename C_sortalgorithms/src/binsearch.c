/*
 * binsearch.c
 *
 *  Created on: 2022/04/30
 *      Author: Sin Shimozono
 */

#include "datadef.h"
#include "sort_algorithms.h"

long binsearch(data * a[], data b, long l, long r) {
	printf("[%ld, %ld)\n", l, r);
	if (l >= r)
		return -1;
	if (r - l < 4) {
		for(; l < r; ++l) {
			printf("a[%ld] = %ld == %ld > ",l,*a[l],b);
			if ( equals(a[l], &b) )
				return l;
		}
		return -1;
	}
	long m = l + (r-l-1)/2 + 1;
	printf("m = %ld\n", m);
	if ( lessthan(&b, a[m]) ) {
		return binsearch(a,b,l,m+1);
	}
	//else if (a[idx[m]] < b) {
	return binsearch(a,b,m+1,r);
	//}
}
