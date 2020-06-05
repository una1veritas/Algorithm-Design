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

int unlhd(const void * d[], const int a, const int b);

int verify_sorted(const data d[], const int idx[], int n, int (*compare)(const data *, const int, const int));

void heapSort(const data d[], int a[], int n,
		int (*compare)(const data *, const int, const int));
void selectionSort(const data d[], int a[], int n,
		int (*compare)(const data *, const int, const int));
void selectionSort_range(const data d[], int a[], int start, int end);

void quickSort(const data d[], int a[], int n,
		int (*compare)(const data *, const int, const int));
void quickSort_range(const data d[], int array[], int start, int end,
		int (*compare)(const data *, const int, const int));

void bubbleSort(const data d[], int a[], int n, int (*compare)(const data *, const int, const int));
void insertionSort(const data d[], int a[], int n, int (*compare)(const data *, const int, const int));
void mergeSort_recursive(const data d[], int a[], int n, int (*compare)(const data *, const int, const int));
void mergeSort(const data d[], int a[], int n, int (*compare)(const data *, const int, const int));


#endif /* SRC_SORTALGORITHMS_H_ */
