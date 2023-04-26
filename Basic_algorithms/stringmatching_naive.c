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
#define MAXPATLEN 7

int stringmatching_naive(char * text, char * pattern) {
	int txtlen = strlen(text), patlen = strlen(pattern);
	int checklen = MIN(patlen, MAXPATLEN);

	for(int i = 0; i < txtlen - checklen + 1; ++i) {
		int j;
		for(j = 0; j < checklen; ++j) {
			if ( text[i+j] != pattern[j] )
				break;
		}
		if (j == checklen ) {
			return i;
			break;
		}
	}
	return -1;
}

int main(int argc, char * argv[]) {
	if ( argc < 3 ) {
		fprintf(stderr, "two strings as text and pattern requested.\n");
		return EXIT_FAILURE;
	}

	char * text = argv[1], * pattern = argv[2];
	fprintf(stdout, "text = %s, pattern = %s\n", text, pattern);

	int pos = stringmatching_naive(text, pattern);
	if ( pos != -1 ) {
		fprintf(stdout, "pattern found in text at %d\n", pos);
	}
	return EXIT_SUCCESS;
}
