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

#define MIN(x, y)   ((x) > (y)? (y) : (x))
#define MAC(x, y)   ((x) < (y)? (y) : (x))
#ifndef ABS
#define ABS(x)  ((x) < 0 ? -(x) : (x))
#endif //ABS

//long ceilpow2(const long val);

long r_edist(char s[], int m, char t[], int n);
long dp_edist(long * table, char t[], long n, char p[], long m);
long weaving_edist(long * frame, const char t[], const long n, const char p[], const long m);
void weaving_setframe(long * frame, const long n, const long m);

#endif /* SRC_LEVDIST_H_ */
