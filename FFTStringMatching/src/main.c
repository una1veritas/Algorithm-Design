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

struct compvect {
	float complex * elem;
	int dim;
};
typedef struct compvect compvect;
const int CONJ_REVERSE = 1;

struct text {
	char * str;
	int maxsize;
	int length;
};
typedef struct text text;

void compvect_mulinto(compvect * x, const compvect * y);
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

int make_signal(const text * text1, const int dimsize, compvect * vec, const int flag);
int get_values(int argc, const char * argv[], text * text1, text * text2);
void print_vector(const char *title, compvect *x);
void findOccurrences(compvect * vec, int pattlen, int * results, int upto);

int main(int argc, const char * argv[]) {
	text text1, text2;
	compvect vec1, vec2;

	text1.maxsize = 512;
	text1.str = (char *) malloc(sizeof(char)*text1.maxsize);
	text2.maxsize = 512;
	text2.str = (char *) malloc(sizeof(char)*text2.maxsize);
	/* Get N and fill v[] with program inputs. */
	if ( !get_values(argc, argv, &text1, &text2) )
		exit(EXIT_FAILURE);

	printf("inputs: \"%s\" (%d), \"%s\" (%d) \n", text1.str, text1.length, text2.str, text2.length);
	int pow2len = smallestpow2(max(text1.length, text2.length));
	int pattlen = min(text1.length, text2.length);
	printf("pow2len = %d, pattlen = %d\n", pow2len, pattlen);

	make_signal(&text1, pow2len, &vec1, !CONJ_REVERSE);
	print_vector("text1 ", &vec1);
	make_signal(&text2, pow2len, &vec2, CONJ_REVERSE);
	print_vector("text2 ", &vec2);
	/* FFT, iFFT of v[]: */

	float complex * scratch = (float complex *) malloc(sizeof(float complex) * vec1.dim);

	cfft(vec1.elem, vec1.dim, scratch);
//	print_vector("fft1 ", text1.elem, text1.dimsize);
	cfft(vec2.elem, vec2.dim, scratch);
//	print_vector("fft2 ", text2.elem, text2.dimsize);

	compvect_mulinto(&vec1, &vec2);
//	print_vector("prod ", text1.elem, text1.dimsize);

	ifft(vec1.elem, vec1.dim, scratch);

	print_vector("iFFT ", &vec1);

	int results[8];
	findOccurrences(&vec1, pattlen, results, 8);
	printf("Occurring positions: ");
	for(int i = 0; i < 8; i++) {
		if ( results[i] < vec1.dim)
			printf("%d, ", results[i] - pattlen + 1);
	}
	printf(".\n");

	free(scratch);
	free(vec1.elem);
	free(vec2.elem);

	free(text1.str);
	free(text2.str);
	exit(EXIT_SUCCESS);
}

int get_values(int argc, const char * argv[], text * text1, text * text2) {
	int len1, len2;

	if ( argc <= 2 ) {
		fprintf(stdout, "No or an invalid number of inputs specified; quit.\n");
		return 0;
	} else if( argc == 3 ) {
		fprintf(stdout, "Take pattern and text from the command line arguments.\n");
		len1 = strlen(argv[1]);
		len2 = strlen(argv[2]);
		if ( len1 >= len2 ) {
			strncpy(text1->str, argv[1], min(text1->maxsize, len1+1));
			text1->length = len1;
			strncpy(text2->str, argv[2], min(text2->maxsize, len2+1));
			text2->length = len2;
		} else {
			strncpy(text1->str, argv[2], min(text1->maxsize, len2+1));
			text1->length = len2;
			strncpy(text2->str, argv[1], min(text2->maxsize, len1+1));
			text2->length = len1;
		}
	}
	return 1;
}

int make_signal(const text * str, const int dimsize, compvect * vec, const int flag) {
	int dst;
	float complex factor;

	// the first as normal
	vec->dim = dimsize;
	vec->elem = (float complex*) malloc(sizeof(float complex)*dimsize);
	for(int i = 0; i < vec->dim; ++i) {
		if ( !flag ) {
			dst = i;
			factor = 2*PI*I;
		} else {
			dst = vec->dim - i - 1;
			factor = -2*PI*I;
		}
		if ( i < str->length ) {
			vec->elem[dst] = cexpf( factor * (float)(str->str[i]) /256.0f );  // by rotated unit vector
			// (*array)[i] = (float)(str[i]) / 128.0f  ;  // by char value
		} else {
			vec->elem[dst] = 0;
		}
	}
	printf("\n");
	return 1;
}

/* Print a vector of complexes as ordered pairs. */
void print_vector(const char *title, compvect *x) {
	int i;
	printf("%s (dim=%d):\n", title, x->dim);
	for (i = 0; i < x->dim; i++)
		printf("%5d    ", i );
	putchar('\n');
	for (i = 0; i <  x->dim; i++)
		printf(" %7.3f,", crealf(x->elem[i]) );
	putchar('\n');
	for (i = 0; i <  x->dim; i++)
		printf(" %7.3f,", cimagf(x->elem[i]) );
	putchar('\n');
	for (i = 0; i <  x->dim; i++)
		printf(" %7.3f,", cabsf(x->elem[i]) );
	printf("\n\n");
	return;
}

void compvect_mulinto(compvect * x, const compvect * y) {
	for(int i = 0; i < x->dim; i++) {
		x->elem[i] = x->elem[i] * y->elem[i];
	}
}

void findOccurrences(compvect * vec, int pattlen, int * results, int upto) {
	int reslast = 0;
	for(int i = 0; i < vec->dim; ++i) {
		if ( abs(crealf(vec->elem[i]) - (double) pattlen) < 0.0001220703125 ) {
			printf("%d, ", i);
			if ( reslast < upto ) {
				results[reslast] = (i + pattlen) % vec->dim;
				++reslast;
			}
		}
	}
	printf("\n");
	for( ; reslast < upto; ++reslast)
		results[reslast] = vec->dim;
}
