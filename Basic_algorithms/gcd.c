/*
 * gcd.c
 *
 *  Created on: 2022/04/15
 *      Author: Sin Shimozono
 */

#include <stdio.h>

long gcd_euclidean(long a, long b) {
	long counter = 0;
	long t;
	do {
		t = a % b;
		a = b;
		b = t;
		counter += 1;
		printf("%ld: a = %ld, b = %ld.\n", counter, a, b);
	} while (b != 0);
	return a;
}
