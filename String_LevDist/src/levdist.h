/*
 * levdist.h
 *
 *  Created on: 2016/12/12
 *      Author: sin
 */

#ifndef SRC_LEVDIST_H_
#define SRC_LEVDIST_H_

#define DEBUG_TABLE
#ifdef DEBUG_TABLE
extern long * debug_table;
#endif

#define min(x, y)   ((x) > (y)? (y) : (x))
#define max(x, y)   ((x) < (y)? (y) : (x))

long pow2(const long val);

long r_edist(char s[], int m, char t[], int n);
long dp_edist(long * table, char t[], long n, char p[], long m);
long wv_edist(long * frame, const char t[], const long n, const char p[], const long m);
void wv_setframe(long * frame, const char t[], const long n, const char p[], const long m);

#endif /* SRC_LEVDIST_H_ */