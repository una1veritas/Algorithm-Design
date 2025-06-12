/*
 ============================================================================
 Name        : modulo_for_negativeval.c
 Author      : Sin Shimozono
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int abs(int x) {
	if (x < 0)
		return -x;
	return x;
}

int mod(int a, int b) {
	if (a >= 0)
		return a % b;
	else
		return mod(b - mod(abs(a),b),b);
}

int main(const int argc, const char * argv[]) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	if (argc < 3)
		return EXIT_FAILURE;

	int a = atoi(argv[1]);
	int b = (int) atoi(argv[2]);

	if (b <= 0)
		fprintf(stdout, "warnning: negative divisor %d\n", b);
	for(int i = -12; i <= 12; ++i) {
		a = i;
		fprintf(stdout, "%d mod %d = %d\n", a, b, mod(a, b));
	}
	return EXIT_SUCCESS;
}
