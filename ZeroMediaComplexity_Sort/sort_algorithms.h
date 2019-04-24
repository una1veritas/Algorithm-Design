/*
 * sort_algorithms.h
 *
 *  Created on: Apr 24, 2019
 *      Author: sin
 */

#ifndef SORT_ALGORITHMS_H_
#define SORT_ALGORITHMS_H_

typedef int data;
int lessthan(data x, data y);

unsigned int insertionSort(data a[], unsigned int n);

/* counters by global variables */
unsigned long passcount[2];

#endif /* SORT_ALGORITHMS_H_ */
