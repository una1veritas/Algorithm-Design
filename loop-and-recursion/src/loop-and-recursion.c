/*
 ============================================================================
 Name        : loop-and-recursion.c
 Author      : Sin Shimozono
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int find_r(char * a, char k) {
	if ( *a == '\0' )
		return 0;
	if ( *a == k )
		return 1;
	return find_r(a+1, k);
}

int find_l(char * a, char k) {
	while ( *a != '\0' ) {
		if ( *a == k )
			return 1;
	}
	return 0;
}

int main(int argc, char * argv[]) {
	if ( argc < 3 )
		return EXIT_FAILURE;
	printf("search %c in %s\n", argv[1][0], argv[2]);
	printf("result = %d\n", find_r(argv[2], argv[1][0]));
	return EXIT_SUCCESS;
}
