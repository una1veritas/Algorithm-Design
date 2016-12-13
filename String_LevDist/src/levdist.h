/*
 * levdist.h
 *
 *  Created on: 2016/12/12
 *      Author: sin
 */

#ifndef SRC_LEVDIST_H_
#define SRC_LEVDIST_H_

long r_edist(char s[], int m, char t[], int n);
long dp_edist(char t[], long n, char p[], long m);
long wv_edist(const long * inframe, long * outframe,
		const char t[], const long n, const char p[], const long m);


#endif /* SRC_LEVDIST_H_ */
