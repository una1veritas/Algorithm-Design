/*
 * sortalgorithms.h
 *
 *  Created on: 2016/12/15
 *      Author: sin
 */

#ifndef SRC_SORTALGORITHMS_H_
#define SRC_SORTALGORITHMS_H_

#define MIN(a,b) ((a) < (b)? (a) : (b))
#define SWAP(a, b, t) 	{ (t) = (a); (a) = (b); (b) = (t); }

typedef long data;
typedef unsigned long index;
int data_greaterThan(data * a, data * b);

void heapSort(data d[], index a[], index n);
void selectionSort(data d[], index a[], index n);
void selectionSort_range(data d[], index a[], index start, index end);

void quickSort(data d[], index a[], index n);
void quickSort_range(data d[], index array[], index start, index end);

void bubbleSort(data d[], index a[], index n);
void insertionSort(data d[],index a[], index n);
void mergeSort_recursive(data d[], index a[], index n);
void mergeSort(data d[], index a[], index n);


#endif /* SRC_SORTALGORITHMS_H_ */
