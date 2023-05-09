/*
 * sort_algorithm.h
 *
 *  Created on: 2020/06/19
 *      Author: sin
 */

#ifndef SRC_SORT_ALGORITHM_H_
#define SRC_SORT_ALGORITHM_H_

#include "datadef.h"

void insertion_sort(data * a[],  long n);
void heap_sort(data * a[], long n);
void selection_sort(data * a[], long n);
void selection_sort_reverse(data * a[], long n);
void merge_sort(data * a[], long n);

void counting_sort(data * a[], long n, long range, long (*keycode)(const data *) );

#endif /* SRC_SORT_ALGORITHM_H_ */
