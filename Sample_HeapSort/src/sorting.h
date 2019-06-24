/*
 * sorting.h
 *
 *  Created on: 2019/06/23
 *      Author: Sin Shimozono
 */

#ifndef SRC_SORTING_H_
#define SRC_SORTING_H_


typedef void * data;

/* sort alrotihms */
void stdlib_qsort(data a[], unsigned int n, int (*compare)(const void *, const void *) );
void selectionSort(data a[], unsigned int n, int (*compare)(const void *, const void *) );
void heapSort(data a[], unsigned int n, int (*compare)(const void *, const void *) );

/* subroutines of the heap sort algorithm */
void down_to_leaf(data a[], unsigned int i, unsigned int n, int (*compare)(const void *, const void *));
void make_heap(data a[], unsigned int n, int (*compare)(const void *, const void *) );


#endif /* SRC_SORTING_H_ */
