/*
 * gcd.c
 *
 *  Created on: 2022/04/15
 *      Author: Sin Shimozono
 */

#include <stdio.h>

#include "gcd.h"

unsigned long long counter;

unsigned long long gcd_euclidean(unsigned long long a, unsigned long long b) {
	unsigned long long t;
	do {
		t = a % b;
		a = b;
		b = t;
		 counter += 1;
	} while (b != 0);
	return a;
}

unsigned long long gcd_naive(unsigned long long a, unsigned long long b) {
	unsigned long long c = (a <= b) ? a : b;
	while ( c > 1 ) {
		 counter += 1;
		if ( (a % c) == 0 && (b % c) == 0 )
			break;
		c -= 1;
	}
	return c;
}
