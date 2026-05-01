/*
 * sort_algorithm.h
 *
 *  Created on: 2020/06/19
 *      Author: sin
 */

#ifndef SRC_SORT_ALGORITHMS_H_
#define SRC_SORT_ALGORITHMS_H_

#include "datadef.h"
#include "ldeque.h"

void insertion_sort(data * a[], long n, compfunc less);
void heap_sort(data * a[], long n, compfunc less);
void selection_sort(data * a[], long n, compfunc less);
void selection_sort_reverse(data * a[], long n, compfunc less);
void merge_sort_recursive(data * a[], long n, compfunc less);
void merge_sort_doubles(data * a[], long n, compfunc less);
void merge_sort_ldeque(LinkedDeque * a, compfunc less);
void bubble_sort(data * a[], long n, compfunc less);

void bucket_sort(data * a[], long n, long range_origin, long range_width, hashfunc keyval);
void bucket_sort_fixed(data * a[], long n, long range_origin, long range_width, hashfunc keyval);
void counting_sort(data * a[], long n, long range_origin, long range_width, hashfunc keyval);

#endif /* SRC_SORT_ALGORITHMS_H_ */
