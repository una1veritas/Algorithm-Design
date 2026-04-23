/*
 * knapsack.h
 *
 *  Created on: 2019/04/22
 *      Author: sin
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

#include <stdbool.h>


int best_pruning(const int list[], const int budget, bool cart[]);
int best_enumeration(const int list[], const int budget, bool cart[]);
int best_dp(const int prices[], const int budget, bool buyornot[]);

#endif /* KNAPSACK_H_ */
