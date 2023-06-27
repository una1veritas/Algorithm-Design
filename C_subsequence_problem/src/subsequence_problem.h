/*
 * subsequence_problem.h
 *
 *  Created on: 2023/06/23
 *      Author: Sin Shimozono
 */

#ifndef SRC_SUBSEQUENCE_PROBLEM_H_
#define SRC_SUBSEQUENCE_PROBLEM_H_

typedef struct {
	union {
		int start;
		int first;
	};
	union {
		int length;
		int second;
	};
	int sum;
} tuple;

tuple longest_increasing_seq(const int a[], const int n);
tuple largest_contiguous_sum(const int a[], const int n);

#endif /* SRC_SUBSEQUENCE_PROBLEM_H_ */
