/*
 ============================================================================
 Name        : C_basic_algorithms.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "strmatch_naive.h"

int main(const int argc, const char * argv[]) {
	if ( argc < 3 ) {
		fprintf(stderr, "two strings, text and pattern, requested.\n");
		return EXIT_FAILURE;
	}

	const char * text = argv[1], * pattern = argv[2];
	fprintf(stdout, "text = %s, pattern = %s\n", text, pattern);

	int pos = 0;
	while ( (pos = strmatch_naive(text, pattern, pos)) != -1) {
		fprintf(stdout, "pattern found in text at %d\n", pos);
		pos += 1;
	}
	return EXIT_SUCCESS;
}
