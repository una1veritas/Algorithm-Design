/*
 * factorial.c
 *
 *  Created on: Feb 18, 2020
 *      Author: sin
 */

long factorial(const long n) {
	if ( n == 0 )
		return 1;
	return factorial(n-1) * n;
}
