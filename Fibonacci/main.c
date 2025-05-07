/*
 * main.c
 *
 *  Created on: 2013/12/12
 *      Author: sin
 */

/*
 * Hi.
input = 37
result = 39088169
.fibo called 78176337 time.
result by dp = 24157817
.fibo_dp looped 35 time.
 *
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

long long counter_fibo = 0;
long long counter_fibo_loop = 0;
long long counter_fibo_memo = 0;

long long fibo(long long n) {
	if ( n < 2 )
		return 1;
	counter_fibo++;
	return fibo(n-1) + fibo(n-2);
}

long long * f;
long long fibo_inner(long long n) {
	counter_fibo_memo++;
	if (f[n] != 0) return f[n];
	f[n] = fibo_inner(n-1) + fibo_inner(n-2);
	return f[n];
}

long long fibo_memo(long long n) {
	f = (long long *) malloc(sizeof(long long)*(n+1));
	f[0] = 1;
	f[1] = 1;
	for(long long i = 2; i < n+1; ++i)
		f[i] = 0;
	long long result = fibo_inner(n);
	free(f);
	return result;
}

long long fibo_loop(long long n) {
	long long f_1 = 1;
	long long f_2 = 1;
	long long f;

	if ( n < 2 )
		return f_1;
	long long i;
	for(i = 2; i <= n; i++) {
		counter_fibo_loop++;

		f = f_1 + f_2;
		f_2 = f_1;
		f_1 = f;
	}
	return f;
}

int main(int argc, char * argv[]) {
	long long n, result;

	n = atol(argv[1]);
	printf("input = %llu\n", n);

	clock_t swatch = clock(); 	/* 時間計測用 */
	result = fibo(n);
	swatch = clock() - swatch; 	/* 時間計測用 */
	printf("f(%llu) = %llu.\n", n, result);
	printf("the function fibo called %llu time, ", counter_fibo);
	printf("took %g ms.\n", swatch/(double)CLOCKS_PER_SEC * 1000); /* for stop watch */

	swatch = clock(); 	/* 時間計測用 */
	result = fibo_loop(n);
	swatch = clock() - swatch; 	/* 時間計測用 */
	printf("f(%llu) by loop = %llu.\n", n, result);
	printf("iterations in fibo_loop %llu time, ", counter_fibo_loop);
	printf("took %g ms.\n", swatch/(double)CLOCKS_PER_SEC * 1000); /* for stop watch */

	swatch = clock(); 	/* 時間計測用 */
	result = fibo_memo(n);
	swatch = clock() - swatch; 	/* 時間計測用 */
	printf("f(%llu) by loop = %llu.\n", n, result);
	printf("iterations in fibo_memo %llu time, ", counter_fibo_memo);
	printf("took %g ms.\n", swatch/(double)CLOCKS_PER_SEC * 1000); /* for stop watch */

	return 0;
}


