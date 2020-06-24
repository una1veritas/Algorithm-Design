/*
 * sort_algorithm.h
 *
 *  Created on: 2020/06/19
 *      Author: sin
 */

#ifndef SRC_SORT_ALGORITHM_H_
#define SRC_SORT_ALGORITHM_H_

#include "datadef.h"

void insertion_sort(const data d[], long a[],  long n);
void heap_sort(const data d[], long a[], long n);
void selection_sort(const data d[], long a[], long n);

void counting_sort(data d[], long idx[], long n, long range, long (*keycode)(const data *) );

#endif /* SRC_SORT_ALGORITHM_H_ */
