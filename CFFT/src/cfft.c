/*
 ============================================================================
 Name        : cfft.c
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
	if ( n <= 1 ) /* do nothing and return */
		return;
	// n > 1
	const int m = n >> 1;
	dcomplex *v1, *v0;
	v0 = tmp;
	v1 = tmp + m;
	for (int i = 0; i < n / 2; i++) {
		v0[i] = v[2 * i];
		v1[i] = v[2 * i + 1];
	}
	fft(v0, m, v); /* FFT on even-indexed elements of v[] */
	fft(v1, m, v); /* FFT on odd-indexed elements of v[] */
	for (int i = 0; i < m; i++) {
		// w = (cos(2 * PI * i / (double) n)) + (-sin(2 * PI * i / (double) n))*I;
		dcomplex w = cexp(- I * /* 2 * */ PI * i / (double) m /* n */);
		dcomplex z = w * v1[i];
		v[i] = v0[i] + z;
		v[i + m] = v0[i] - z;
	}
	return;
}


void fft_dp(dcomplex *vec, int n, dcomplex *scratch) {
	dcomplex *src, *dst, *tmp;
	src = vec;
	dst = scratch;
	// n > 1
	// do butterfly swap
	for(int m = (n>>1); m > 0; m >>= 1) {
		for(int head = 0; head < n; head += (m<<1) ) {
			for(int i = 0; i < m; i++) {
				dst[head+i] = src[head+2*i];
				dst[head+m+i] = src[head+2*i+1];
			}
		}
		tmp = src; src = dst; dst = tmp;
	}

	// divide-and-conqure, only by merging
	for(int m = 1; m < n; m = (m<<1) ) {
		for (int h = 0; h < n; h += (m<<1) ) {
			for(int i = 0; i < m; i++) {
				dcomplex w = cexp(- I * /* 2 * */ PI * i / ((double) m) /* n */);
				dcomplex z = w * src[h + m + i];
				dst[h + i] = src[h + i] + z;
				dst[h + m + i] = src[h + i] - z;
			}
		}
		tmp = src;
		src = dst;
		dst = tmp;
	}

	/*
	const double sqrt_N = sqrt( ((double) n) );
	for(int i = 0; i < n; i++) {
		vec[i] = src[i] / sqrt_N;
	}
	*/

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

	fft_dp(v, n, tmp);

	for (int i = 0; i < n; i++) {
		dcomplex t = conj(v[i]) / ((double) n);
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
static void print_vector(const char *title, dcomplex *x, int n) {
	int i;
	printf("%s (dim=%d):\n", title, n);
	for (i = 0; i < n; i++)
		printf(" %5d ", i );
	putchar('\n');
	for (i = 0; i < n; i++)
		printf(" %5.2f,", creal(x[i]) );
	putchar('\n');
	for (i = 0; i < n; i++)
		printf(" %5.2f,", cimag(x[i]) );
	putchar('\n');
	for (i = 0; i < n; i++)
		printf(" %5.2f,", cabs(x[i]) );
	printf("\n\n");
	return;
}

int main(int argc, char * argv[]) {
	int N;
	dcomplex * v;

	/* Get N and fill v[] with program inputs. */
	if ( !get_values(argc, argv, &N, &v) )
		exit(EXIT_FAILURE);

	//mini_test(N);

	/* FFT, iFFT of v[]: */
	print_vector("Orig", v, N);
	fft_dp(v, N, v+N);
	print_vector(" FFT", v, N);
	ifft(v, N, v+N);
	print_vector("iFFT", v, N);

	exit(EXIT_SUCCESS);
}
