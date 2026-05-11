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

unsigned long long fibo_memorize(const unsigned long long n, unsigned long long f[]) {
	if (n <= 1) {
		f[n] = 1;
	} else if ( f[n-1] == 0 ) {
		f[n] = fibo_memorize(n-1, f) + fibo_memorize(n-2, f);
	}
	return f[n];
}

unsigned long long fibo_dp(const unsigned long long n) {
	unsigned long long f[n];
	unsigned long long r;
	f[0] = 1;
	f[1] = 1;
	for(unsigned long long i = 2; i <= n; ++i)
		f[i] = f[i-1] + f[i-2];
	r = f[n];
	return r;
}

unsigned long long fibo(const unsigned long long n) {
	unsigned long long fnth = 1;
	if ( n >=2 ) {
		unsigned long long fn_2 = 1;
		unsigned long long fn_1 = 1;
		for(unsigned long long i = 2; i <= n; ++i) {
			fnth = fn_1 + fn_2;
			fn_2 = fn_1;
			fn_1 = fnth;
		}
	}
	return fnth;
}

/*
 * sin@alpheratz C_basic_algorithms % ./Debug/C_basic_algorithms 20
sin@alpheratz C_basic_algorithms % ./Debug/C_basic_algorithms 10
f_n = 89
spent clocks = 0.000006
f_n = 89
spent clocks = 0.000002
sin@alpheratz C_basic_algorithms % ./Debug/C_basic_algorithms 20
f_n = 10946
spent clocks = 0.000091
f_n = 10946
spent clocks = 0.000000
sin@alpheratz C_basic_algorithms % ./Debug/C_basic_algorithms 30
f_n = 1346269
spent clocks = 0.010219
f_n = 1346269
spent clocks = 0.000001
sin@alpheratz C_basic_algorithms % ./Debug/C_basic_algorithms 40
f_n = 165580141
spent clocks = 0.531966
f_n = 165580141
spent clocks = 0.000001
sin@alpheratz C_basic_algorithms % ./Debug/C_basic_algorithms 45
f_n = 1836311903
spent clocks = 5.616450
f_n = 1836311903
spent clocks = 0.000002
sin@alpheratz C_basic_algorithms % ./Debug/C_basic_algorithms 50
f_n = 20365011074
spent clocks = 61.890632
f_n = 20365011074
spent clocks = 0.000001
sin@alpheratz C_basic_algorithms % ./Debug/C_basic_algorithms 52
f_n = 53316291173
spent clocks = 161.458839
f_n = 53316291173
spent clocks = 0.000001
sin@alpheratz C_basic_algorithms %
 */
