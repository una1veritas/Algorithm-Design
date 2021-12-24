/*
 * cfft.h
 *
 *  Created on: 2016/11/06
 *      Author: sin
 */

#ifndef SRC_CFFT_H_
#define SRC_CFFT_H_

#include <math.h>
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

void rfft(dcomplex *v, int n, dcomplex *tmp);
void cfft(dcomplex *vec, int n, dcomplex *scratch);
void ifft(dcomplex *v, int n, dcomplex *tmp);



#endif /* SRC_CFFT_H_ */
