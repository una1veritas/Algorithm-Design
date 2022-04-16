/*
 * gcd.c
 *
 *  Created on: 2022/04/15
 *      Author: Sin Shimozono
 */

#include <stdio.h>

#include "gcd.h"

ullong counter;

ullong gcd_euclidean(ullong a, ullong b) {
	ullong t;
	do {
		t = a % b;
		a = b;
		b = t;
		// counter += 1;
	} while (b != 0);
	return a;
}

ullong gcd_naive(ullong a, ullong b) {
	ullong c = (a <= b) ? a : b;
	while ( c > 1 ) {
		// counter += 1;
		if ( (a % c) == 0 && (b % c) == 0 )
			break;
		c -= 1;
	}
	return c;
}
