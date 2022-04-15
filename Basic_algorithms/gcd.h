/*
 * gcd.h
 *
 *  Created on: 2022/04/15
 *      Author: Sin Shimozono
 */

#ifndef GCD_H_
#define GCD_H_

typedef unsigned long long ullong;

extern ullong counter;

ullong gcd_euclidean(ullong a, ullong b);
ullong gcd_naive(ullong a, ullong b);

#endif /* GCD_H_ */
