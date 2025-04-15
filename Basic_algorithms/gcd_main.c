/*
 * main.c
 *
 *  Created on: 2022/04/15
 *      Author: Sin Shimozono
 *
 */

#include <stdio.h>
#include <stdlib.h>
//#include <ctype.h>
#include <time.h>
#include <math.h>
#include <errno.h>

#include "gcd.h"

int main(int argc, char * argv[]) {
	if (argc == 1) {
		printf("Run with argument(s).\n");
		return EXIT_FAILURE;
	}

	int datacount = argc - 1;
	long inputs[datacount];
	for(int i = 0; i < datacount; ++i) {
		char * ptr;
		inputs[i] = strtoll(argv[i+1], &ptr, 0);
		if ( errno == ERANGE ) {
			printf("Failed to interpret '%s' an argument to an integer.\n", ptr);
			return EXIT_FAILURE;
		}
	}

	clock_t swatch;

	unsigned long long result;
	printf("inputs: %ld, %ld\n", inputs[0], inputs[1]);

	swatch = clock();
	result = gcd_naive(inputs[0], inputs[1]);
	swatch = clock() - swatch;
	printf("swatch = %.3f sec.\n", (float)swatch/CLOCKS_PER_SEC);

	printf("By naive gcd = %llu\n", result);

	swatch = clock();
	result = gcd_euclidean(inputs[0], inputs[1]);
	swatch = clock() - swatch;
	printf("swatch = %.3f sec.\n", (float)swatch/CLOCKS_PER_SEC);

	printf("By Euclidean gcd = %llu\n", result);
	printf("\n");

	return EXIT_SUCCESS;
}
