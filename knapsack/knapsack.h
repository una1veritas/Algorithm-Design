/*
 * knapsack.h
 *
 *  Created on: 2019/04/22
 *      Author: sin
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

typedef unsigned int price;
typedef unsigned char mybool;

price bestPrice_recursive(price list[], price budget);
price bestPrice_dp(price list[], price budget);

price try_all_subsets(price list[], price budget, mybool cart[]);

#endif /* KNAPSACK_H_ */
