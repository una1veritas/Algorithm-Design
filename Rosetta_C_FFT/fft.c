/*
 * fft.c
 *
 *  Created on: 2015/11/21
 *      Author: sin
 */


#include <stdio.h>
#include <math.h>
#include <complex.h>

double PI;
typedef double complex cplx;

void fft_dc(cplx buf[], cplx out[], int n, int step)
{
	if (step < n) {
		fft_dc(out, buf, n, step * 2);
		fft_dc(out + step, buf + step, n, step * 2);

		for (int i = 0; i < n; i += 2 * step) {
			cplx t = cexp(-I * PI * i / n) * out[i + step];
			buf[i / 2]     = out[i] + t;
			buf[(i + n)/2] = out[i] - t;
		}
	}
}

void fft(cplx buf[], int n)
{
	cplx out[n];
	for (int i = 0; i < n; i++)
		out[i] = buf[i];

	fft_dc(buf, out, n, 1);
}

void ifft(cplx buf[], int n)
{
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


}


void show(const char * s, cplx buf[]) {
	printf("%s", s);
	for (int i = 0; i < 8; i++)
		if (!cimag(buf[i]))
			printf("%g ", creal(buf[i]));
		else
			printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
}

int main()
{
	PI = atan2(1, 1) * 4;
	cplx buf[] = {1, 1, 1, 1, 0, 0, 0, 0};

	show("Data: ", buf);
	fft(buf, 8);
	show("\nFFT : ", buf);
	ifft(buf, 8);
	show("\nIFFT : ", buf);

	return 0;
}

