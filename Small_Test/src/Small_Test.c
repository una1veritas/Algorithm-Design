/*
 ============================================================================
 Name        : Small_Test.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	long q, r;
} QuoRem;

QuoRem divmod(long x, long y) {
	QuoRem r;
	r.q = x / y;
	r.r = x % y;
	return r;
}

int main(int argc, char * argv[]) {
	long x, y;
	QuoRem res;

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	x = atol(argv[1]);
	y = atol(argv[2]);

	res = divmod(x, y);

	printf("quotient = %ld, reminder = %ld\n", res.q, res.r);
	return EXIT_SUCCESS;
}
