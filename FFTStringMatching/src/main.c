/*
 ============================================================================
 Name        : fft_main.c
 Author      : Sin Shimozono
 Version     :
 Copyright   : reserved.
 Description : Factored discrete Fourier transform, or FFT, and its inverse iFFT
 ============================================================================
 * Reference:
 * http://www.math.wustl.edu/~victor/mfmm/fourier/fft.c
 * http://rosettacode.org/wiki/Fast_Fourier_transform
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "cfft.h"

struct dcompvec {
	dcomplex * elem;
	int dimsize;
};
typedef struct dcompvec dcompvec;

void dcompvec_free(dcompvec * vec) {
	free(vec->elem);
}

int get_values(int argc, char * argv[], dcompvec * patt, dcompvec * text);
void print_vector(const char *title, dcomplex *x, int n);

int main(int argc, char * argv[]) {
	dcompvec pattern, text;
	dcomplex * v = NULL;

	/* Get N and fill v[] with program inputs. */
	if ( !get_values(argc, argv, &pattern, &text) )
		exit(EXIT_FAILURE);

	/* FFT, iFFT of v[]: */
	print_vector("Orig", text.elem, text.dimsize);
	/*
	cfft(v, N, v+N);
	print_vector(" FFT", v, N);
	ifft(v, N, v+N);
	print_vector("iFFT", v, N);
*/
	dcompvec_free(&pattern);
	dcompvec_free(&text);

	exit(EXIT_SUCCESS);
}


int get_values(int argc, char * argv[], dcompvec * patt, dcompvec * text) {
	int slen;
	int num;
	char * str;
	dcomplex * array;

	if ( argc <= 2 ) {
		fprintf(stdout, "No or an invalid number of inputs specified; quit.\n");
		return 0;
	} else if( argc == 3 ) {
		fprintf(stdout, "Take pattern and text from the command line arguments.\n");

		// the first is pattern
		str = argv[1];
		slen = strlen(str);
		for(num = 1; num < slen; num <<= 1 ) {}
				array = (dcomplex *) malloc(sizeof(dcomplex) * num);
		for(int i = 0; i < num; i++) {
			if ( i < slen )
				array[i] = cexp( I * (float)(str[i]) /256.0f );  // by rotated unit vector
				// (*array)[i] = (float)(str[i]) / 128.0f  ;  // by char value
			else
				array[i] = 0;
		}
		patt->dimsize = num;
		patt->elem = array;

		// the second is text
		str = argv[2];
		slen = strlen(str);
		for(num = 1; num < slen; num <<= 1 ) {}
		array = (dcomplex *) malloc(sizeof(dcomplex) * num);
		for(int i = 0; i < num; i++) {
			if ( i < slen )
				array[i] = cexp( I * (float)(str[i]) /256.0f );  // by rotated unit vector
				// (*array)[i] = (float)(str[i]) / 128.0f  ;  // by char value
			else
				array[i] = 0;
		}
		text->dimsize = num;
		text->elem = array;

	}

	return 1;
}

/* Print a vector of complexes as ordered pairs. */
void print_vector(const char *title, dcomplex *x, int n) {
	int i;
	printf("%s (dim=%d):\n", title, n);
	for (i = 0; i < n; i++)
		printf("%5d    ", i );
	putchar('\n');
	for (i = 0; i < n; i++)
		printf(" %7.3f,", creal(x[i]) );
	putchar('\n');
	for (i = 0; i < n; i++)
		printf(" %7.3f,", cimag(x[i]) );
	putchar('\n');
	for (i = 0; i < n; i++)
		printf(" %7.3f,", cabs(x[i]) );
	printf("\n\n");
	return;
}
