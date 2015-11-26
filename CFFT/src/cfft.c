/*
 ============================================================================
 Name        : cfft.c
 Author      : modified http://www.math.wustl.edu/~victor/mfmm/fourier/fft.c
 Version     :
 Copyright   : by Sin Shimozono
 Description : Factored discrete Fourier transform, or FFT, and its inverse iFFT
 ============================================================================
 */

/*
 * #include <assert.h>
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

/*
 * double PI;
 */
#ifdef M_PI
# define PI M_PI
#else
# define PI	3.14159265358979323846264338327950288
#endif

typedef double complex dcomplex;

/* Print a vector of complexes as ordered pairs. */
static void print_vector(const char *title, dcomplex *x, int n) {
	int i;
	printf("%s (dim=%d):\n", title, n);
	for (i = 0; i < n; i++)
		printf(" %5d ", i );
	putchar('\n');
	for (i = 0; i < n; i++)
		printf(" %5.2f \n", creal(x[i]) );
	putchar('\n');
	for (i = 0; i < n; i++)
		printf(" %5.2f \n", cimag(x[i]) );
	printf("\n\n");
	return;
}

/*
 fft(v,N):
 [0] If N==1 then return.
 [1] For k = 0 to N/2-1, let ve[k] = v[2*k]
 [2] Compute fft(ve, N/2);
 [3] For k = 0 to N/2-1, let vo[k] = v[2*k+1]
 [4] Compute fft(vo, N/2);
 [5] For m = 0 to N/2-1, do [6] through [9]
 [6]   Let w.re = cos(2*PI*m/N)
 [7]   Let w.im = -sin(2*PI*m/N)
 [8]   Let v[m] = ve[m] + w*vo[m]
 [9]   Let v[m+N/2] = ve[m] - w*vo[m]
 */

void fft(dcomplex *v, int n, dcomplex *tmp) {
	if ( n == 0 ) /* do nothing and return */
		return;

	// n > 1
	dcomplex *v1, *v0;
	v0 = tmp;
	v1 = tmp + n / 2;
	for (int i = 0; i < n / 2; i++) {
		v0[i] = v[2 * i];
		v1[i] = v[2 * i + 1];
	}
	fft(v0, n / 2, v); /* FFT on even-indexed elements of v[] */
	fft(v1, n / 2, v); /* FFT on odd-indexed elements of v[] */
	for (int i = 0; i < n / 2; i++) {
		dcomplex w = (cos(2 * PI * i / (double) n)) + (-sin(2 * PI * i / (double) n))*I;
		dcomplex z = w * v1[i];
		v[i] = v0[i] + z;
		v[i + n / 2] = v0[i] - z;
	}
	return;
}

/*
 ifft(v,N):
 [0] If N==1 then return.
 [1] For k = 0 to N/2-1, let ve[k] = v[2*k]
 [2] Compute ifft(ve, N/2);
 [3] For k = 0 to N/2-1, let vo[k] = v[2*k+1]
 [4] Compute ifft(vo, N/2);
 [5] For m = 0 to N/2-1, do [6] through [9]
 [6]   Let w.re = cos(2*PI*m/N)
 [7]   Let w.im = sin(2*PI*m/N)
 [8]   Let v[m] = ve[m] + w*vo[m]
 [9]   Let v[m+N/2] = ve[m] - w*vo[m]
 */

/*
	cplx out[n];
	for (int i = 0; i < n; i++) {
		out[i] = conj(buf[i]);
		buf[i] = out[i];
	}

	fft_dc(buf, out, n, 1);

	for (int i = 0; i < n; i++) {
		cplx t = conj(buf[i]);
		t = creal(t)/n + cimag(t)/n*I;
		buf[i] = t;
	}

 */
void ifft(dcomplex *v, int n, dcomplex *tmp) {

	for (int i = 0; i < n; i++) {
		v[i] = conj(v[i]);
	}

	fft(v, n, tmp);

	for (int i = 0; i < n; i++) {
		dcomplex t = conj(v[i]);
		t = creal(t)/((double)n) + (cimag(t)/((double)n))*I;
		v[i] = t;
	}

	return;
}

int get_values(int argc, char * argv[], int * n, dcomplex * v[]) {
	int t;
	double f;

	if ( argc < 2 )
		return 0;
	for ( t = 1; t < argc-1; t *= 2) {}
	*n = (int) t;
	*v = (dcomplex * )malloc(sizeof(dcomplex)*t);
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

int main(int argc, char * argv[]) {
	int N;
	dcomplex * v;

	/* Get N and fill v[] with program inputs. */
	if ( !get_values(argc, argv, &N, &v) )
		exit(EXIT_FAILURE);
	dcomplex scratch[N];

	/* FFT, iFFT of v[]: */
	print_vector("Orig", v, N);
	fft(v, N, scratch);
	print_vector(" FFT", v, N);
	ifft(v, N, scratch);
	print_vector("iFFT", v, N);

	free(v);

	exit(EXIT_SUCCESS);
}
