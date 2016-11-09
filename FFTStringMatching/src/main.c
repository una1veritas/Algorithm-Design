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

void dcompvec_mulinto(dcompvec * x, const dcompvec * y);
long smallestpow2(const long n) {
	long t = 1;
	while ( t < n ) {
		t <<= 1;
	}
	return t;
}

#define min(x,y)  ( ((x) < (y) ? (x) : (y)) )
#define max(x,y)  ( ((x) < (y) ? (y) : (x)) )
#define abs(x)  ( (x) < 0 ? (-(x)) : (x) )


int get_values(int argc, const char * argv[], dcompvec * text1, dcompvec * text2);
void print_vector(const char *title, dcomplex *x, int n);


int main(int argc, const char * argv[]) {
	dcompvec text1, text2;
	int pattlen = min(strlen(argv[1]), strlen(argv[2]));
	/* Get N and fill v[] with program inputs. */
	if ( !get_values(argc, argv, &text1, &text2) )
		exit(EXIT_FAILURE);

	printf("%d %d\n", sizeof(dcomplex), sizeof(_Complex_I) );
	/* FFT, iFFT of v[]: */
	print_vector("text1 ", text1.elem, text1.dimsize);
	print_vector("text2 ", text2.elem, text2.dimsize);

	dcomplex * scratch = (dcomplex *) malloc(sizeof(dcomplex) * text1.dimsize);

	cfft(text1.elem, text1.dimsize, scratch);
//	print_vector("fft1 ", text1.elem, text1.dimsize);
	cfft(text2.elem, text2.dimsize, scratch);
//	print_vector("fft2 ", text2.elem, text2.dimsize);

	dcompvec_mulinto(&text1, &text2);
//	print_vector("prod ", text1.elem, text1.dimsize);

	ifft(text1.elem, text1.dimsize, scratch);
	print_vector("iFFT ", text1.elem, text1.dimsize);

	printf("Occurring positions: ");
	for(int i = 0; i < text1.dimsize; i++) {
		if ( abs(creal(text1.elem[(text1.dimsize - pattlen + i) % text1.dimsize]) - (double) pattlen) < 0.0001220703125 )
			printf("%d, ", i - pattlen + 1);
	}
	printf(".\n");

	free(scratch);
	free(text1.elem);
	free(text2.elem);

	exit(EXIT_SUCCESS);
}


int get_values(int argc, const char * argv[], dcompvec * text1, dcompvec * text2) {
	const char * str1 = argv[1];
	const char * str2 = argv[2];
	int maxlen, len;

	if ( argc <= 2 ) {
		fprintf(stdout, "No or an invalid number of inputs specified; quit.\n");
		return 0;
	} else if( argc == 3 ) {
		fprintf(stdout, "Take pattern and text from the command line arguments.\n");
		maxlen = smallestpow2(max(strlen(str1), strlen(str2)));

		// the first as normal
		text1->dimsize = maxlen;
		text1->elem = (dcomplex*) malloc(sizeof(dcomplex)*maxlen);
		len = strlen(str1);
		for(int i = 0; i < text1->dimsize; ++i) {
			if ( i < len )
				text1->elem[i] = cexp( 2*PI*I * (float)(str1[i]) /256.0f );  // by rotated unit vector
				// (*array)[i] = (float)(str[i]) / 128.0f  ;  // by char value
			else
				text1->elem[i] = 0;
		}

		// the second as conjugated and reversed order
		text2->dimsize = maxlen;
		text2->elem = (dcomplex*) malloc(sizeof(dcomplex)*maxlen);
		len = strlen(str2);
		for(int i = 0; i < text2->dimsize; ++i) {
			if ( i < len )
				//array[i] = cexp( -2*PI*I * (float)(str2[slen - i - 1]) /256.0f );  // by rotated unit vector
				text2->elem[text2->dimsize - i - 1] = cexp( -2*PI*I * (float)(str2[i]) /256.0f );  // by rotated unit vector
				// (*array)[i] = (float)(str[i]) / 128.0f  ;  // by char value
			else
				text2->elem[text2->dimsize - i - 1] = 0;
		}

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
