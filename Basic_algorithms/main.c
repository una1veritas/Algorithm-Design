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
#include <errno.h>

//#include "gcd.h"
//#include "factorial.h"
#include "fibo.h"

#define TYPE_INT 0
#define TYPE_STR 1

int main(int argc, char * const argv[]) {
	if (argc == 1) {
		exit(1);
	}

	int datacount = argc - 1;
	struct {
		int type;
		long long val;
	} inputs[datacount];
	for(int i = 0; i < datacount; ++i) {
		char * ptr;
		inputs[i].type = TYPE_INT;
		inputs[i].val = strtoll(argv[i+1], &ptr, 0);
		if ( errno == ERANGE ) {
			inputs[i].type = TYPE_STR;
			inputs[i].val = (long long) argv[i+1];
		}
	}

	clock_t swatch;

	long input = inputs[0].val;
	unsigned long long result;
	printf("inputs: %ld\n", input);

	swatch = clock();
	result = fibo_recursive(input);
	swatch = clock() - swatch;
	printf("swatch = %.3f sec.\n", (float)swatch/CLOCKS_PER_SEC);

	printf("result %llu\n", result);
	/*
	printf("inputs: %lld, %lld\n", input[0], input[1]);
	printf("length: %lld\n", (unsigned long long)ceil(log10((input[0] < input[1])? input[0] : input[1])));

	unsigned long long output;
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
	 */

	return EXIT_SUCCESS;
}
