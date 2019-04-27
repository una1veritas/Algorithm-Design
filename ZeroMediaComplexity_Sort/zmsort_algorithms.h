/*
 * sort_algorithms.h
 *
 *  Created on: Apr 24, 2019
 *      Author: sin
 */

#ifndef ZMSORT_ALGORITHMS_H_
#define ZMSORT_ALGORITHMS_H_

typedef int data;
#define lessthan(x, y)  	((x) < (y))
#define greaterthan(x, y) 	((x) > (y))
#define lessthan_or_equal(x, y) 	(! greaterthan(x, y))
#define min(x, y) 			((x) > (y)? (y) : (x))

unsigned int insertionSort(data a[], unsigned int n);
unsigned int selectionSort(data a[], unsigned int n);
unsigned int mergeSort(data a[], unsigned int n);

#endif /* ZMSORT_ALGORITHMS_H_ */
