/*
 ============================================================================
 Name        : BitComputing.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <inttypes.h>

typedef uint64_t uint64;
typedef int64_t int64;

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	int64 x = 24;

	printf("%lx\n", x & (-x));


	return EXIT_SUCCESS;
}
