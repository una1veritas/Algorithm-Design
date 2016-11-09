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


int get_values(int argc, char * argv[], dcompvec * text1, dcompvec * text2);
void print_vector(const char *title, dcomplex *x, int n);


int main(int argc, char * argv[]) {
	dcompvec text1, text2;

	/* Get N and fill v[] with program inputs. */
	if ( !get_values(argc, argv, &text1, &text2) )
		exit(EXIT_FAILURE);

	/* FFT, iFFT of v[]: */
	print_vector("text1 ", text1.elem, text1.dimsize);
	print_vector("text2 ", text2.elem, text2.dimsize);

	dcomplex * tmp = (dcomplex *) malloc(sizeof(dcomplex) * text1.dimsize);

	cfft(text1.elem, text1.dimsize, tmp);
	print_vector("fft1 ", text1.elem, text1.dimsize);
	cfft(text2.elem, text2.dimsize, tmp);
	print_vector("fft2 ", text2.elem, text2.dimsize);

	dcompvec_mulinto(&text1, &text2);
	print_vector("prod ", text1.elem, text1.dimsize);

	ifft(text1.elem, text1.dimsize, tmp);
	print_vector("iFFT ", text1.elem, text1.dimsize);

	free(tmp);

	dcompvec_free(&text1);
	dcompvec_free(&text2);

	exit(EXIT_SUCCESS);
}


int get_values(int argc, char * argv[], dcompvec * text1, dcompvec * text2) {
	int slen, pow2len;
	char * str1, * str2;
	dcomplex * array;

	if ( argc <= 2 ) {
		fprintf(stdout, "No or an invalid number of inputs specified; quit.\n");
		return 0;
	} else if( argc == 3 ) {
		fprintf(stdout, "Take pattern and text from the command line arguments.\n");
		str1 = argv[1];
		str2 = argv[2];
		slen = max(strlen(str1), strlen(str2));
		for(pow2len = 1; pow2len < slen; pow2len <<= 1 ) {} //

		// the first as normal
		array = (dcomplex *) malloc(sizeof(dcomplex) * pow2len);
		slen = strlen(str1);
		for(int i = 0; i < pow2len; i++) {
			if ( i < slen )
				array[i] = cexp( 2*PI*I * (float)(str1[i]) /256.0f );  // by rotated unit vector
				// (*array)[i] = (float)(str[i]) / 128.0f  ;  // by char value
			else
				array[i] = 0;
		}
		text1->dimsize = pow2len;
		text1->elem = array;

		// the second as conjugated and reversed order
		slen = strlen(str2);
		array = (dcomplex *) malloc(sizeof(dcomplex) * pow2len);
		for(int i = 0; i < pow2len; i++) {
			if ( i < slen )
				//array[i] = cexp( -2*PI*I * (float)(str2[slen - i - 1]) /256.0f );  // by rotated unit vector
				array[pow2len - i - 1] = cexp( -2*PI*I * (float)(str2[i]) /256.0f );  // by rotated unit vector
				// (*array)[i] = (float)(str[i]) / 128.0f  ;  // by char value
			else
				array[pow2len - i - 1] = 0;
		}
		text2->dimsize = pow2len;
		text2->elem = array;

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
