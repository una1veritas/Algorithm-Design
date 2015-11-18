/*
 ============================================================================
 Name        : Hanoi_moves.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

long Hanoi(int n);

int main(int argc, char * argv[]) {
	int n;
	long moves;

	if ( argc != 2 )
		goto error;

	n = atoi(argv[1]);

	printf("How many moves does %d-disk tower need?\n", n);
	moves = Hanoi(n);
	printf("%ld, ",moves);
	printf("\n\n");

	return EXIT_SUCCESS;

error:
	printf("wrong argument(s).\n\n");
	return EXIT_FAILURE;
}

long Hanoi(n) {
	if ( n == 0 )
		return 0;
	if ( n == 1 )
		return 1;
	return Hanoi(n-1) + 1 + Hanoi(n-1);
}
