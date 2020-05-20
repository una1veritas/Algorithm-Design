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

uint64_t counter_fibo = 0;
uint64_t counter_fibo_loop = 0;

uint64_t fibo(uint64_t n) {
	counter_fibo++;

	if ( n < 2 )
		return 1;
	return fibo(n-1) + fibo(n-2);
}

uint64_t fibo_loop(uint64_t n) {
	uint64_t f_1 = 1;
	uint64_t f_2 = 1;
	uint64_t f;

	if ( n < 2 )
		return f_1;
	uint64_t i;
	for(i = 2; i <= n; i++) {
		counter_fibo_loop++;

		f = f_1 + f_2;
		f_2 = f_1;
		f_1 = f;
	}
	return f;
}

int main(int argc, char * argv[]) {
	uint64_t n, result;

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

	return 0;
}


