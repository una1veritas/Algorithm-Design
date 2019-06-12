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

typedef void* data;

int data_greaterThan(data * a, data * b);

void heapSort(data d[], long a[], long n);
void selectionSort(data d[], long a[], long n);
void selectionSort_range(data d[], long a[], long start, long end);

void quickSort(data d[], long a[], long n);
void quickSort_range(data d[], long array[], long start, long end);

void bubbleSort(data d[], long a[], long n);
void insertionSort(data d[],long a[], long n);
void mergeSort_recursive(data d[], long a[], long n);
void mergeSort(data d[], long a[], long n);


#endif /* SRC_SORTALGORITHMS_H_ */
