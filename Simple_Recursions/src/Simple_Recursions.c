/*
 ============================================================================
 Name        : Simple_Recursions.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

volatile long counter;

long F(n) {
	counter++;
	if ( n == 0 )
		return 0;
	if ( n == 1 )
		return 1;
	return F(n-1) + F(n-2);
}

long H(n) {
	counter++;
	if ( n == 0 )
		return 0;
	if ( n == 1 )
		return 1;
	return H(n-1) + 1 + H(n-1);
}

int main(int argc, char * argv[]) {
	int n;
	long f;

	if ( !(argc > 1) ) {
		printf("wrong argument(s).\n\n");
		return EXIT_FAILURE;
	}

	printf("Sequence:\n");
	for(int i = 1; i < argc; i++) {
		n = atoi(argv[i]);
		counter = 0;
		f = F(n);
		printf("%ld (%ld), ", f, counter);
		fflush(stdout);
	}
	printf("\n\n");

	return EXIT_SUCCESS;
}

