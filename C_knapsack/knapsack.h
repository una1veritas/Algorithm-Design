/*
 * knapsack.h
 *
 *  Created on: 2019/04/22
 *      Author: sin
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

typedef struct {
	int * prices;
	int   number;
} PriceList;

/*

int best_recursive(Knapsack * list, int fromIndex, Knapsack * best);
*/
int best_recursive(PriceList * list, int start, int budget);
int best_enumerate(PriceList * list, int number, int budget);
/*
int best_dp(PriceList list, int budget, char cart[]);
*/
#endif /* KNAPSACK_H_ */
