/*
 ============================================================================
 Name        : Fibonacci_sequence.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

long fibo(int n);

int main(int argc, char * argv[]) {
	int n;
	long f;

	if ( argc != 2 )
		goto error;

	n = atoi(argv[1]);

	printf("fibonacci sequence:\n");
	setbuf(stdout, NULL);
	for(int i = 0; i <= n; i++) {
		f = fibo(i);
		printf("%ld, ",f);
	}
	printf("\n\n");

	return EXIT_SUCCESS;

error:
	printf("wrong argument(s).\n\n");
	return EXIT_FAILURE;
}

long fibo(n) {
	if ( n == 0 || n == 1 )
		return 1;
	return fibo(n-1) + fibo(n-2);
}
