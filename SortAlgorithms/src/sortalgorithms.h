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

typedef void * int;
int data_greaterThan(const int * a, const int * b);

int verify_sorted(const int *d, const unsigned ix[], const unsigned int n);

void heapSort(const int d[], unsigned int a[], unsigned int n);
void selectionSort(const int d[], unsigned int a[], unsigned int n);
void selectionSort_range(const int d[], unsigned int a[], unsigned int start, unsigned int end);

void quickSort(const int d[], unsigned int a[], unsigned int n);
void quickSort_range(const int d[], unsigned int array[], unsigned int start, unsigned int end);

void bubbleSort(const int d[], unsigned int a[], unsigned int n);
void insertionSort(const int d[],unsigned int a[], unsigned int n);
void mergeSort_recursive(const int d[], unsigned int a[], unsigned int n);
void mergeSort(const int d[], unsigned int a[], unsigned int n);


#endif /* SRC_SORTALGORITHMS_H_ */
