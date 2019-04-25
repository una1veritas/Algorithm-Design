/*
 * sort_algorithms.h
 *
 *  Created on: Apr 24, 2019
 *      Author: sin
 */

#ifndef SORT_ALGORITHMS_H_
#define SORT_ALGORITHMS_H_

typedef int data;
unsigned int lessthan(data x, data y);
unsigned int lessthan_or_equal(data x, data y);

unsigned int insertionSort(data a[], unsigned int n);
unsigned int selectionSort(data a[], unsigned int n);

#endif /* SORT_ALGORITHMS_H_ */
