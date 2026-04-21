/*
 * knapsack.h
 *
 *  Created on: 2023/05/01
 *      Author: sin
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_


int knapsack_enumerate(const int prices[], const int budget, bool cart[]);

int knapsack_recursive(const int prices[], const int budget, bool cart[]);
int knapsack_dp(const int prices[], const int budget, bool cart[]);

#endif /* KNAPSACK_H_ */
