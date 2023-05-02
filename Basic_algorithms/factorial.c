/*
 * factorial.c
 *
 *  Created on: Feb 18, 2020
 *      Author: sin
 */
#include <stdio.h>

long long factorial(const long long n) {
	printf(".\n");
	if ( n == 0 )
		return 1;
	return factorial(n-1) * n;
}
