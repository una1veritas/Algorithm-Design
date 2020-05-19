/*
 * knapsack.h
 *
 *  Created on: 2019/04/22
 *      Author: sin
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

typedef struct {
	int * price;
	int number;
	int budget;
} Knapsack;

/*

int bestcart_recursive(Knapsack * list, int fromIndex, Knapsack * best);
*/
int bestprice_recursive(Knapsack * instance, int startIndex, int rembudget);
int bestprice_enumerate(int pricelist[], int number, int budget);
/*
int bestcart_dp(PriceList list, int budget, char cart[]);
*/
#endif /* KNAPSACK_H_ */
