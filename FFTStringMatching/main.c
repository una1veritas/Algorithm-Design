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

/* array of double-complex */
struct dcompvec {
	dcomplex * elem;
	int dimsize;
};
typedef struct dcompvec dcompvec;

/* constant for flag */
const int CONJ_REVERSE = 1;

/* char array with size info */
struct text {
	char * str;
	int length;
};
typedef struct text text;

/* make inner product in the first vector */
void dcompvec_mulinto(dcompvec * x, const dcompvec * y);

/* ceiling of log 2 */
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

/* make dcompvec from string */
int make_signal(text * text1, int dimsize, dcompvec * vec, const int flag);

int get_args(int argc, const char * argv[], text * text1, text * text2);
void print_vector(const char *title, dcomplex *x, int n);


int main(int argc, const char * argv[]) {
	text text1, text2;
	dcompvec vec1, vec2;

	/* Get N and fill v[] with program inputs. */
	if ( !get_args(argc, argv, &text1, &text2) )
		exit(EXIT_FAILURE);

	printf("inputs: \"%s\", \"%s\" \n", text1.str, text2.str);
	int pow2len = smallestpow2(max(text1.length, text2.length));
	int pattlen = min(text1.length, text2.length);

	make_signal(&text1, pow2len, &vec1, !CONJ_REVERSE);
	make_signal(&text2, pow2len, &vec2, CONJ_REVERSE);
	/* FFT, iFFT of v[]: */
	print_vector("text1 ", vec1.elem, vec1.dimsize);
	print_vector("text2 ", vec2.elem, vec2.dimsize);

	dcomplex * scratch = (dcomplex *) malloc(sizeof(dcomplex) * vec1.dimsize);

	cfft(vec1.elem, vec1.dimsize, scratch);
//	print_vector("fft1 ", text1.elem, text1.dimsize);
	cfft(vec2.elem, vec2.dimsize, scratch);
//	print_vector("fft2 ", text2.elem, text2.dimsize);

	dcompvec_mulinto(&vec1, &vec2);
//	print_vector("prod ", text1.elem, text1.dimsize);

	ifft(vec1.elem, vec1.dimsize, scratch);

	print_vector("iFFT ", vec1.elem, vec1.dimsize);

	printf("Occurring positions: ");
	for(int i = 0; i < vec1.dimsize; i++) {
		if ( abs(creal(vec1.elem[(vec1.dimsize - pattlen + i) % vec1.dimsize]) - (double) pattlen) < 0.0001220703125 )
			printf("%d, ", i - pattlen + 1);
	}
	printf(".\n");

	free(scratch);
	free(vec1.elem);
	free(vec2.elem);

	free(text1.str);
	free(text2.str);
	exit(EXIT_SUCCESS);
}

int get_args(int argc, const char * argv[], text * text1, text * text2) {
	if ( argc <= 2 ) {
		fprintf(stdout, "No or an invalid number of inputs specified; quit.\n");
		return 0;
	} else if( argc == 3 ) {
		fprintf(stdout, "Take pattern and text from the command line arguments.\n");
		if ( strlen(argv[1]) > strlen(argv[2]) ) {
			text1->length = strlen(argv[1]);
			text1->str = (char *) malloc(sizeof(char) * text1->length);
			strcpy(text1->str, argv[1]);
			text2->length = strlen(argv[2]);
			text2->str = (char *) malloc(sizeof(char) * text2->length);
			strcpy(text2->str, argv[2]);
		} else {
			text1->length = strlen(argv[2]);
			text1->str = (char *) malloc(sizeof(char) * text1->length);
			strcpy(text1->str, argv[2]);
			text2->length = strlen(argv[1]);
			text2->str = (char *) malloc(sizeof(char) * text2->length);
			strcpy(text2->str, argv[1]);
		}
	}
	return 1;
}

int make_signal(text * str, const int dimsize, dcompvec * vec, const int flag) {
	int len;
	int dst;
	dcomplex factor;

	// the first as normal
	vec->dimsize = dimsize;
	vec->elem = (dcomplex*) malloc(sizeof(dcomplex)*dimsize);
	len = str->length;
	for(int i = 0; i < vec->dimsize; ++i) {
		if ( !flag ) {
			dst = i;
			factor = 2*PI*I;
		} else {
			dst = vec->dimsize - i - 1;
			factor = -2*PI*I;
		}
		if ( i < len )
			vec->elem[dst] = cexp( factor * (float)(str->str[i] ) /128.0f );
			/* express by rotated unit vector, assuming ascii char (up to 127) */
		else
			vec->elem[dst] = 0;
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

/* function computing the operation *= for two vectors of the same length */
void dcompvec_mulinto(dcompvec * x, const dcompvec * y) {
	/* assume x and y are the same length */
	for(int i = 0; i < x->dimsize; i++) {
		x->elem[i] *= y->elem[i];
	}
}
