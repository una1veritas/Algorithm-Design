/*
 * binsearch.c
 *
 *  Created on: 2022/04/30
 *      Author: Sin Shimozono
 */

#include "datadef.h"
#include "sort_algorithm.h"

long binsearch(data a[], data b, long l, long r) {
	long m = l + (r-l)/2;
	return binsearch(a, b, l, r);
}
