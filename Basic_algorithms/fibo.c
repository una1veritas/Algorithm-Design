/*
 * fibo.cpp
 *
 *  Created on: Feb 18, 2020
 *      Author: sin
 */

unsigned long long fibo_recursive(const unsigned long long n) {
	if ( n < 2 )
		return 1;
	return fibo_recursive(n-1) + fibo_recursive(n-2);
}

