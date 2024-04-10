/*
 * gcd.h
 *
 *  Created on: 2022/04/15
 *      Author: Sin Shimozono
 */

#ifndef GCD_H_
#define GCD_H_

extern unsigned long long counter;

unsigned long long gcd_euclidean(unsigned long long a, unsigned long long b);
unsigned long long gcd_euclidean_do(unsigned long long a, unsigned long long b);
unsigned long long gcd_naive(unsigned long long a, unsigned long long b);

#endif /* GCD_H_ */
