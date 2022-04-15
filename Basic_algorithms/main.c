/*
 * main.c
 *
 *  Created on: 2022/04/15
 *      Author: Sin Shimozono
 */
#include <stdio.h>
#include <stdlib.h>

long gcd_euclidean(long a, long b);

int main(const int argc, const char * argv[]) {
	long int var[3] = { 0, 0, 0, };
	unsigned int argcount = (argc - 1 > 3) ? 3 : argc -1 ;
	for (int i = 0; i < argcount; ++i)
		var[i] = strtol(argv[i+1], NULL, 10);
	for(int i = 0; i < argcount; ++i) {
		printf("%ld, ", var[i]);
	}
	printf("\n");

	long result = gcd_euclidean(var[0], var[1]);

	printf("result = %ld.\n", result);
	return EXIT_SUCCESS;
}
