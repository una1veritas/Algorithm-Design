/*
 * sort_algorithm.h
 *
 *  Created on: 2020/06/19
 *      Author: sin
 */

#ifndef SRC_SORT_ALGORITHMS_H_
#define SRC_SORT_ALGORITHMS_H_

#include "datadef.h"
#include "llist.h"

void insertion_sort(data * a[],  long n);
void heap_sort(data * a[], long n);
void selection_sort(data * a[], long n);
void selection_sort_reverse(data * a[], long n);
void merge_sort_recursive(data * a[], long n);
void merge_sort_doubles(data * a[], long n);
void merge_sort_llist(LList * a);

void bucket_sort(data * a[], long n, long range_origin, long range_width, long (*keyval)(const data * d));
void bucket_sort_fixed(data * a[], long n, long range_origin, long range_width, long (*keyval)(const data * d));
void counting_sort(data * a[], long n, long range_origin, long range_width, long (*keyval)(const data * d));

#endif /* SRC_SORT_ALGORITHMS_H_ */
