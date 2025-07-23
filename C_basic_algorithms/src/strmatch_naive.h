/*
 * strmatch_naive.h
 *
 *  Created on: 2025/07/22
 *      Author: sin
 */

#ifndef STRMATCH_NAIVE_H_
#define STRMATCH_NAIVE_H_

/* returns the index of the first occurrence from the start index;
 * or -1 if no such pattern found.
 * */
int strmatch_naive(const char * text, const char * pat, const int start) ;

#endif /* STRMATCH_NAIVE_H_ */
