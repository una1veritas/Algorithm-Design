/*
 * knapsack.h
 *
 *  Created on: 2019/04/22
 *      Author: sin
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

typedef struct {
	unsigned int count;
	unsigned int * price;
} PriceList;

unsigned int bestcart_recursive(PriceList list, unsigned int budget, unsigned int item, unsigned char cart[]);
unsigned int bestcart_dp(PriceList list, unsigned int budget, unsigned char cart[]);

unsigned int bestcart_enumerate(PriceList list, unsigned int budget, unsigned char cart[] );

#endif /* KNAPSACK_H_ */
