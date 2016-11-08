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


int get_values(int argc, char * argv[], int * n, dcomplex * v[]);
void print_vector(const char *title, dcomplex *x, int n);

int main(int argc, char * argv[]) {
	int N;
	dcomplex * v;

	/* Get N and fill v[] with program inputs. */
	if ( !get_values(argc, argv, &N, &v) )
		exit(EXIT_FAILURE);

	//mini_test(N);

	/* FFT, iFFT of v[]: */
	print_vector("Orig", v, N);
	cfft(v, N, v+N);
	print_vector(" FFT", v, N);
	ifft(v, N, v+N);
	print_vector("iFFT", v, N);

	free(v);

	exit(EXIT_SUCCESS);
}


int get_values(int argc, char * argv[], int * n, dcomplex * v[]) {
	double f;
	int mode = 0;

	if ( argc < 2 )
		return 0;

	int t = 1;
	int pos;
	int count = 0;
	for(pos = 1; pos < argc; pos++) {
		f = atof( argv[pos]);
		if ( f == 0 && argv[pos][0] == '-' ) {
			/* - switch */
			if ( strcmp("-c", argv[pos]) == 0 )
				mode = 1; /* complex mode */
		} else {
			count++;
			if ( !(count <= t) )
				t *= 2;
		}
	}
	if ( mode == 1 )
		printf("complex mode: ");
	else
		printf("real only mode: ");
	printf("t %d\n", t);

	*n = (int) t;
	*v = (dcomplex * )malloc(sizeof(dcomplex)* 2* t);
	for(int i = 0; i < t; ++i) {
		if ( i < argc - 1 ) {
			f = atof(argv[i+1]);
		} else {
			f = 0.0;
		}
		(*v)[i] = f;
	}
	return 1;
}

/* Print a vector of complexes as ordered pairs. */
void print_vector(const char *title, dcomplex *x, int n) {
	int i;
	printf("%s (dim=%d):\n", title, n);
	for (i = 0; i < n; i++)
		printf(" %6d ", i );
	putchar('\n');
	for (i = 0; i < n; i++)
		printf(" %6.3f,", creal(x[i]) );
	putchar('\n');
	for (i = 0; i < n; i++)
		printf(" %6.3f,", cimag(x[i]) );
	putchar('\n');
	for (i = 0; i < n; i++)
		printf(" %6.3f,", cabs(x[i]) );
	printf("\n\n");
	return;
}
