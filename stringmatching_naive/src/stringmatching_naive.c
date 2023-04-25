/*
 ============================================================================
 Name        : stringmatching_naive.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x, y) ((x) <= (y) ? (x) : (y))
#define MAXCHECKLEN 7

int main(int argc, char * argv[]) {
	if ( argc < 3 ) {
		fprintf(stderr, "two strings as text and pattern requested.\n");
		return EXIT_FAILURE;
	}

	char * text = argv[1], * pattern = argv[2];
	int txtlen = strlen(text), patlen = strlen(pattern);
	fprintf(stdout, "text = %s, pattern = %s\n", text, pattern);

	for(int i = 0; i < txtlen - patlen + 1; ++i) {
		int j;
		int checklen = MIN(patlen, MAXCHECKLEN);
		for(j = 0; j < checklen; ++j) {
			if ( text[i+j] != pattern[j] )
				break;
		}
		if (j == checklen ) {
			fprintf(stdout, "pattern found in text at %d\n", i);
			break;
		}
	}
	return EXIT_SUCCESS;
}
