/*
 * cfft.c
 *
 *  Created on: 2016/11/06
 *      Author: sin
 */

#include <stdio.h>

#include <math.h>
#include <complex.h>

#include "cfft.h"

/*
 *  Explicit divide-and-conqure FFT by recursion
 */
void rfft(float complex *v, int n, float complex *tmp) {
	if ( n <= 1 ) /* do nothing and return */
		return;
	// n > 1
	const int m = n >> 1;
	float complex *v1, *v0;
	v0 = tmp;
	v1 = tmp + m;
	for (int i = 0; i < n / 2; i++) {
		v0[i] = v[2 * i];
		v1[i] = v[2 * i + 1];
	}
	rfft(v0, m, v); /* FFT on even-indexed elements of v[] */
	rfft(v1, m, v); /* FFT on odd-indexed elements of v[] */
	for (int i = 0; i < m; i++) {
		// w = (cos(2 * PI * i / (double) n)) + (-sin(2 * PI * i / (double) n))*I;
		float complex w = cexpf(- I * /* 2 * */ PI * i / (double) m /* n */);
		float complex z = w * v1[i];
		v[i] = v0[i] + z;
		v[i + m] = v0[i] - z;
	}
	return;
}


/*
 * FFT by butterfly changes in advance forcing divide-and-conqure
 */
void cfft(float complex *vec, int n, float complex *scratch) {
	float complex *src, *dst, *tmp;
	src = vec;
	dst = scratch;
	// n > 1
	// do butterfly swap
	// fprintf(stdout, "swap: ");
	for(int m = (n>>1); m > 0; m >>= 1) {
		for(int head = 0; head < n; head += (m<<1) ) {
			for(int i = 0; i < m; i++) {
				// fprintf(stdout, "(%d : %d, %d) ", head, head+m, i);
				dst[head+i] = src[head+2*i];
				dst[head+m+i] = src[head+2*i+1];
			}
		}
		// fprintf(stdout, "\n");
		tmp = src; src = dst; dst = tmp;
	}

	// fprintf(stdout, "merge: ");
	// divide-and-conqure, only by merging
	for(int m = 1; m < n; m = (m<<1) ) {
		for (int h = 0; h < n; h += (m<<1) ) {
			for(int i = 0; i < m; i++) {
				// fprintf(stdout, "(%d : %d, %d) ", h, h+m, i);
				float complex w = cexpf(- I * /* 2 * */ PI * i / ((double) m) /* n */);
				float complex z = w * src[h + m + i];
				dst[h + i] = src[h + i] + z;
				dst[h + m + i] = src[h + i] - z;
			}
		}
		// fprintf(stdout, "\n");
		tmp = src;
		src = dst;
		dst = tmp;
	}

	return;
}



void ifft(float complex *v, int n, float complex *tmp) {

	for (int i = 0; i < n; i++) {
		v[i] = conjf(v[i]);
	}

	cfft(v, n, tmp);

	for (int i = 0; i < n; i++) {
		float complex t = conjf(v[i]) / ((double) n);
		v[i] = t;
	}
	return;
}
