/*
 * main.c
 *
 *  Created on: 2022/04/15
 *      Author: Sin Shimozono
67280421310721, 6442450941,
result = 1.
counter = 21.
swatch = 0.000 sec.
result = 1.
counter = 6442450940.
swatch = 33.802 sec.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#include "gcd.h"

int main(int argc, char * const argv[]) {
	ullong input[2] = { 0, 0, };

	if (argc == 2) {
		char * ptr = argv[1];
		input[0] = strtoull(ptr, &ptr, 10);
		while ( !isdigit(*++ptr) );
		if ( ! *ptr )
			exit(1);
		input[1] = strtoull(ptr, NULL, 10);
	} else {
		for (int i = 0; i < argc - 1; ++i) {
			input[i] = strtoull(argv[i+1], NULL, 10);
		}
	}
	printf("inputs: %lld, %lld\n", input[0], input[1]);
	printf("length: %lld\n", (ullong)ceil(log10((input[0] < input[1])? input[0] : input[1])));

	ullong output;
	clock_t swatch;

	swatch = clock();
	counter = 0;
	output = gcd_euclidean(input[0], input[1]);
	swatch = clock() - swatch;
	printf("result = %lld.\n", output);
	printf("counter = %lld.\n", counter);
	printf("swatch = %.3f sec.\n", (float)swatch/CLOCKS_PER_SEC);

	swatch = clock();
	counter = 0;
	output = gcd_naive(input[0], input[1]);
	swatch = clock() - swatch;
	printf("result = %lld.\n", output);
	printf("counter = %lld.\n", counter);
	printf("swatch = %.3f sec.\n", (float)swatch/CLOCKS_PER_SEC);

	return EXIT_SUCCESS;
}
