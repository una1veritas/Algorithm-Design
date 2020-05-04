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

typedef void * data;
int data_greaterThan(const data * a, const data * b);

int verify_sorted(const data *d, const unsigned ix[], const unsigned int n);

void heapSort(const data d[], unsigned int a[], unsigned int n);
void selectionSort(const data d[], unsigned int a[], unsigned int n);
void selectionSort_range(const data d[], unsigned int a[], unsigned int start, unsigned int end);

void quickSort(const data d[], unsigned int a[], unsigned int n);
void quickSort_range(const data d[], unsigned int array[], unsigned int start, unsigned int end);

void bubbleSort(const data d[], unsigned int a[], unsigned int n);
void insertionSort(const data d[],unsigned int a[], unsigned int n);
void mergeSort_recursive(const data d[], unsigned int a[], unsigned int n);
void mergeSort(const data d[], unsigned int a[], unsigned int n);


#endif /* SRC_SORTALGORITHMS_H_ */
