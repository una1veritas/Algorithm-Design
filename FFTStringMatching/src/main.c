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
void dcompvec_mulinto(dcompvec * x, const dcompvec * y);

#define min(x,y)  ( ((x) < (y) ? (x) : (y)) )
#define max(x,y)  ( ((x) < (y) ? (y) : (x)) )

int get_values(int argc, char * argv[], dcompvec * patt, dcompvec * text);
void print_vector(const char *title, dcomplex *x, int n);

int main(int argc, char * argv[]) {
	dcompvec patt, text;

	/* Get N and fill v[] with program inputs. */
	if ( !get_values(argc, argv, &patt, &text) )
		exit(EXIT_FAILURE);

	/* FFT, iFFT of v[]: */
	print_vector("Text ", text.elem, text.dimsize);
	print_vector("Patt ", patt.elem, patt.dimsize);

	dcomplex * tmp = (dcomplex *) malloc(sizeof(dcomplex) * text.dimsize);

	cfft(text.elem, text.dimsize, tmp);
	print_vector(" FFT ", text.elem, text.dimsize);
	cfft(patt.elem, patt.dimsize, tmp);
	print_vector(" FFT ", patt.elem, patt.dimsize);

	dcompvec_mulinto(&text, &patt);
	print_vector("prod ", text.elem, text.dimsize);

	ifft(text.elem, text.dimsize, tmp);
	print_vector("iFFT ", text.elem, text.dimsize);

	free(tmp);

	dcompvec_free(&patt);
	dcompvec_free(&text);

	exit(EXIT_SUCCESS);
}


int get_values(int argc, char * argv[], dcompvec * patt, dcompvec * text) {
	int len;
	int dsize;
	char * p, * t, *s;
	dcomplex * array;

	if ( argc <= 2 ) {
		fprintf(stdout, "No or an invalid number of inputs specified; quit.\n");
		return 0;
	} else if( argc == 3 ) {
		fprintf(stdout, "Take pattern and text from the command line arguments.\n");
		p = argv[1];
		t = argv[2];
		if ( strlen(p) > strlen(t) ) {
			s = t;
			t = p;
			p = s;
		}
		len = strlen(t);
		for(dsize = 1; dsize < len; dsize <<= 1 ) {}

		// the shorter is the pattern
		array = (dcomplex *) malloc(sizeof(dcomplex) * dsize);
		len = strlen(p);
		for(int i = 0; i < dsize; i++) {
			if ( i < len )
				array[i] = cexp( 2*PI*I * (float)(p[i]) /256.0f );  // by rotated unit vector
				// (*array)[i] = (float)(str[i]) / 128.0f  ;  // by char value
			else
				array[i] = 0;
		}
		patt->dimsize = dsize;
		patt->elem = array;

		// the longer is the text
		len = strlen(t);
		array = (dcomplex *) malloc(sizeof(dcomplex) * dsize);
		for(int i = 0; i < dsize; i++) {
			if ( i < len )
				array[i] = cexp(  2*PI*I * (float)(t[i]) /256.0f );  // by rotated unit vector
				// (*array)[i] = (float)(str[i]) / 128.0f  ;  // by char value
			else
				array[i] = 0;
		}
		text->dimsize = dsize;
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

void dcompvec_mulinto(dcompvec * x, const dcompvec * y) {
	for(int i = 0; i < x->dimsize; i++) {
		x->elem[i] = x->elem[i] * y->elem[i];
	}
}
