/*
 ============================================================================
 Name        : Find_Subsequence_Sum.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char * argv[]) {
	unsigned int a[argc-1];
	unsigned int n = argc - 1;
	for(int i = 0; i < n; ++i) {
		a[i] = (unsigned int) strtol(argv[1+i], NULL, 10);
		printf("%u, ", a[i]);
	}
	printf("\x0d");

	unsigned int i = 0;
	unsigned int len = 0;
	unsigned int sum;
	while ( i < n ) {
		sum = 0;
		for(int j = i; j < i + 0; ++j) {
			sum += a[j];
		}
	}
	return EXIT_SUCCESS;
}
