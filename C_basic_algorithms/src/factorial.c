/*
 * factorial.c
 *
 *  Created on: Feb 18, 2020
 *      Author: sin
 */
#include <stdio.h>

long factorial(const long n) {
	if ( n == 0 )
		return 1;
	return factorial(n-1) * n;
}

long factorial_tailrecursive(const long n, const long r) {
	if ( n == 0 )
		return r;
	return factorial_tailrecursive(n-1, n * r);
}
