/*
 * fibo.cpp
 *
 *  Created on: Feb 18, 2020
 *      Author: sin
 */

#include <stdlib.h>

unsigned long long fibo_recursive(const unsigned long long n) {
	if ( n < 2 )
		return 1;
	return fibo_recursive(n-1) + fibo_recursive(n-2);
}

unsigned long long fibo_rdp(const unsigned long long n, unsigned long long f[]) {
	if ( f[n-1] == 0 )
		fibo_rdp(n-1, f);
	f[n] = f[n-1] + f[n-2];
	return f[n];
}

unsigned long long fibo_recursive_dp(const unsigned long long n) {
	unsigned long long * f = (unsigned long long *) malloc(n * sizeof(unsigned long long));
	unsigned long long r;
	f[0] = 1;
	f[1] = 1;
	for(unsigned long long i = 2; i <= n; ++i)
		f[i] = 0;
	r = fibo_rdp(n, f);
	free(f);
	return r;
}
