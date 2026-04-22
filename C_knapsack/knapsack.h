/*
 * knapsack.h
 *
 *  Created on: 2019/04/22
 *      Author: sin
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

#include <stdbool.h>


int best_pruning(int list[], int budget, bool cart[]);
int best_enumeration(int list[], int budget, bool cart[]);
/*
int best_dp(PriceList list, int budget, char cart[]);
*/
#endif /* KNAPSACK_H_ */
