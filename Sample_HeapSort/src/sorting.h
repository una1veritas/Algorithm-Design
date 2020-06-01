/*
 * sorting.h
 *
 *  Created on: 2019/06/23
 *      Author: Sin Shimozono
 */

#ifndef SRC_SORTING_H_
#define SRC_SORTING_H_


typedef void * int;

/* sort alrotihms */
void stdlib_qsort(int a[], unsigned int n, int (*compare)(const void *, const void *) );
void selectionSort(int a[], unsigned int n, int (*compare)(const void *, const void *) );
void heapSort(int a[], unsigned int n, int (*compare)(const void *, const void *) );

/* subroutines of the heap sort algorithm */
void down_to_leaf(int a[], unsigned int i, unsigned int n, int (*compare)(const void *, const void *));
void make_heap(int a[], unsigned int n, int (*compare)(const void *, const void *) );


#endif /* SRC_SORTING_H_ */
