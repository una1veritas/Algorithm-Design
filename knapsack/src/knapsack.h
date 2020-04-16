/*
 * knapsack.h
 *
 *  Created on: 2019/04/22
 *      Author: sin
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

typedef struct {
	int number;
	int * price;
} PriceList;

int bestcart_recursive(PriceList list, int budget, char cart[]);
int bestprice_recursive(PriceList list, int budget);
int bestcart_dp(PriceList list, int budget, char cart[]);
int bestcart_enumerate(PriceList list, int budget, char cart[] );

#endif /* KNAPSACK_H_ */
