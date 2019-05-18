#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knapsack.h"

unsigned int bestcart_enumerate(PriceList list, unsigned int budget, unsigned char cart[]) {
	unsigned int n, i;
	unsigned int bestPrice = 0, sum;
	// count the number
	for(n = 0; list.price[n]; ++n) {}
	unsigned char tempcart[bitstobytes(n+1)];
	memset(tempcart, 0, bitstobytes(n+1));
	// try all combinations
	for (;;) {
		sum = 0;
		for(i = 0; i < n; ++i) {
			if ( bitcheck(tempcart, i) )
				sum += list.price[i];
#ifdef STATUS_PRINT_STDOUT
			printf("%d, ", bitcheck(tempcart, i) );
#endif
		}
		if ( sum <= budget && sum > bestPrice ) {
			bestPrice = sum;
			memcpy(cart, tempcart, n);
		}
#ifdef STATUS_PRINT_STDOUT
		printf(": %d\n", sum);
#endif
		/* make the next combination */
		if ( bitcheck(tempcart, n) )
			break;
		for(i = 0; i < n + 1; ++i) {
			if ( bitcheck(tempcart, i) ) {
				bitclear(tempcart, i);
				continue;
			} else {
				bitset(tempcart, i);
				break;
			}
		}
	}
	return bestPrice;
}

unsigned int bestcart_recursive(PriceList list, unsigned int budget, unsigned int item, unsigned char cart[]) {
	unsigned int sum_skip, sum_buy;
	unsigned char tcart_buy[bitstobytes(list.count)], tcart_dont[bitstobytes(list.count)];
	if ( item >= list.count )
		return 0;
	sum_skip = bestcart_recursive(list, budget, item+1, tcart_dont);
	// default --- don't buy it
	bitclear(cart, item);
	for(unsigned int i = item+1; i < list.count; ++i)
		if ( bitcheck(tcart_dont, i) )
			bitset(cart, item);
		else
			bitclear(cart, item);
	if ( list.price[item] > budget)
		return sum_skip;
	sum_buy = list.price[item] + bestcart_recursive(list, budget - list.price[item], item+1, tcart_buy);
	if (sum_buy > sum_skip) {
		bitset(cart, item); // = 1; // buy it
		for(unsigned int i = item+1; i < list.count; ++i)
			if ( bitcheck(tcart_buy, i) )
				bitset(cart, item);
			else
				bitclear(cart, item);
		return sum_buy;
	}
	return sum_skip;
}

unsigned int bestprice_recursive(PriceList list, unsigned int budget, unsigned int item) {
	unsigned int sum_skip, sum_buy;
	if ( item >= list.count )
		return 0;
	sum_skip = bestprice_recursive(list, budget, item+1);
	// default --- don't buy it
	if ( list.price[item] > budget)
		return sum_skip;
	sum_buy = list.price[item] + bestprice_recursive(list, budget - list.price[item], item+1);
	if (sum_buy > sum_skip)
		return sum_buy;
	return sum_skip;
}

unsigned int bestcart_dp(PriceList list, unsigned int budget, unsigned char cart[]) {
	unsigned int best[list.count][budget+1];

	// filling the top row.
	for (unsigned int b = 0; b <= budget; b++) {
		if (list.price[0] > b) {
			best[0][b] = 0;
		} else {
			best[0][b] = list.price[0];
		}
	}

	// filling the rows from the 2nd to nth.
	for (unsigned int i = 1; i < list.count; i++) {
		for (unsigned int b = 0; b <= budget; b++) {
			if (list.price[i] > b) {
				best[i][b] = best[i-1][b];
				continue;
			}
			if ( best[i-1][b] > list.price[i] + best[i-1][b-list.price[i]] ) {
				best[i][b] = best[i-1][b];
			} else {
				best[i][b] = list.price[i] + best[i-1][b-list.price[i]];
			}
		}
	}
	
	// back tracking on the dp table.
	unsigned int total = best[list.count-1][budget];
	for(unsigned int itemcount = list.count; itemcount > 1; --itemcount) {
		if ( best[itemcount - 1][total] == best[itemcount - 2][total] ) {
			bitclear(cart, itemcount - 1); //cart[itemcount - 1] = 0;
		} else {
			total -= list.price[itemcount - 1];
			bitset(cart, itemcount - 1);
			//cart[itemcount - 1] = 1;
		}
	}
	if ( best[0][total] == list.price[0] )
		bitset(cart, 0);
	else
		bitclear(cart, 0);
	//cart[0] = ( best[0][total] == list.price[0] );

	return best[list.count-1][budget];
}

