/*
 ============================================================================
 Name        : C_basic_algorithms.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef STRING_MATCHING_NAIVE
#include "strmatch_naive.h"
#endif

#include <time.h>

#include "fibo.h"

int main(const int argc, const char * argv[]) {
#ifdef STRING_MATCHING_NAIVE
	if ( argc < 3 ) {
		fprintf(stderr, "two strings, text and pattern, requested.\n");
		return EXIT_FAILURE;
	}

	const char * text = argv[1], * pattern = argv[2];
	fprintf(stdout, "text = %s, pattern = %s\n", text, pattern);

	int pos = 0;
	while ( (pos = strmatch_naive(text, pattern, pos)) != -1) {
		fprintf(stdout, "pattern found in text at %d\n", pos);
		pos += 1;
	}
#endif

	if (argc < 2) {
		fprintf(stderr, "argument(s) requested.\n");
		return EXIT_FAILURE;
	}

	unsigned long long fnth, n;
	clock_t swatch;

	for(int i = 1; i < argc; ++i) {

		n = strtoul(argv[i], NULL, 0);
		fprintf(stdout, "n = %llu\n", n);

		swatch = clock();
		fnth = fibo_recursive(n);
		swatch = clock() - swatch;
		fprintf(stdout, "f_n = %llu\n", fnth);
		fprintf(stdout, "fibo_recursive	fib_memorize	fibo_dp 	fibo simple\n");
		fprintf(stdout, "%4.6f	", (double) swatch / CLOCKS_PER_SEC);

		swatch = clock();
		unsigned long long memo[n+1];
		for (unsigned long long ix = 0; ix <= n; ++ix)
			memo[ix] = 0;
		fnth = fibo_memorize(n, memo);
		swatch = clock() - swatch;
		fprintf(stdout, "%4.6f	", (double) swatch / CLOCKS_PER_SEC);

		swatch = clock();
		fnth = fibo_dp(n);
		swatch = clock() - swatch;
		fprintf(stdout, "%4.6f	", (double) swatch / CLOCKS_PER_SEC);

		swatch = clock();
		fnth = fibo(n);
		swatch = clock() - swatch;
		fprintf(stdout, "%4.6f	", (double) swatch / CLOCKS_PER_SEC);

		fprintf(stdout, "\n\n");
	}

	return EXIT_SUCCESS;
}
