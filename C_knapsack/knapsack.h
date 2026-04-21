/*
 * knapsack.h
 *
 *  Created on: 2019/04/22
 *      Author: sin
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

#include <stdbool.h>

/*

int best_recursive(Knapsack * list, int fromIndex, Knapsack * best);
*/
int best_recursive(int list[], int num, int spot, int budget, bool cart[]);
int best_enumerate(int list[], int num, int budget);
/*
int best_dp(PriceList list, int budget, char cart[]);
*/
#endif /* KNAPSACK_H_ */
