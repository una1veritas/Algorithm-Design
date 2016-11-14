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

void rfft(float complex *v, int n, float complex *tmp);
void cfft(float complex *vec, int n, float complex *scratch);
void ifft(float complex *v, int n, float complex *tmp);



#endif /* SRC_CFFT_H_ */
