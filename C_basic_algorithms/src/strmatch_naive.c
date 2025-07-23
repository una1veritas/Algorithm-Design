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

int strmatch_naive(const char * text, const char * pat, const int start) {
	for(int ix = start; text[ix] != '\0'; ++ix) {
		int iy;
		for(iy = 0; pat[iy] != '\0'; ++iy) {
			if (text[ix+iy] != pat[iy])
				break;
		}
		if (pat[iy] == '\0')
			return ix;
	}
	return -1;
}

/*
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
*/
