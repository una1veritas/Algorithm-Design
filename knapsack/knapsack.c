#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knapsack.h"

unsigned int bestcart_enumerate(PriceList list, unsigned int budget, unsigned char cart[]) {
	unsigned int bestPrice = 0, sum;
	unsigned int n = list.count;
	unsigned char tempcart[n+1];
	memset(tempcart, 0, n+1);

	for (;;) {
		sum = 0;
		for(unsigned int i = 0; i < n; ++i) {
			if ( tempcart[i] )
				sum += list.price[i];
#ifdef STATUS_PRINT_STDOUT
			printf("%d, ", tempcart[i] );
#endif
		}
		if ( sum <= budget && sum > bestPrice ) {
			bestPrice = sum;
			memcpy(cart, tempcart, n);
		}
#ifdef STATUS_PRINT_STDOUT
		printf(": %d\n", sum);
#endif
		if ( tempcart[n] ) // check (n+1)th digit
			break;
		for(unsigned int i = 0; i < n + 1; ++i) {
			if ( tempcart[i] == 0 ) {
				tempcart[i] = 1;
				break;
			}
			tempcart[i] = 0;
			continue;
		}
	}
	return bestPrice;
}

unsigned int bestcart_recursive(PriceList list, unsigned int budget, unsigned char cart[]) {
	unsigned int sum_skip, sum_buy;
	if ( list.count == 0 )
		return 0;
	unsigned char tcart_buy[list.count], tcart_dont[list.count];
	PriceList remained = { list.count - 1, list.price + 1};
	sum_skip = bestcart_recursive(remained, budget, tcart_dont);
	// default --- don't buy it
	*cart = 0;
	memcpy(cart+1, tcart_dont, remained.count);
	if ( *list.price > budget)
		return sum_skip;
	sum_buy = *list.price + bestcart_recursive(remained, budget - *list.price, tcart_buy);
	if (sum_buy > sum_skip) {
		*cart = 1; // buy it
		memcpy(cart+1, tcart_buy, remained.count);
		return sum_buy;
	}
	return sum_skip;
}

unsigned int bestprice_recursive(PriceList list, unsigned int budget) {
	unsigned int sum_skip, sum_buy;
	if ( list.count == 0 )
		return 0;
	PriceList remained = { list.count - 1, list.price+1 };
	sum_skip = bestprice_recursive(remained, budget);
	// default --- don't buy it
	if ( *list.price > budget)
		return sum_skip;
	sum_buy = *list.price + bestprice_recursive(remained, budget - *list.price);
	if (sum_buy > sum_skip)
		return sum_buy;
	return sum_skip;
}

unsigned int bestcart_dp(PriceList list, unsigned int budget, unsigned char cart[]) {
	unsigned int best[list.count][budget+1];

	// filling the only-1st-item row.
	for (unsigned int b = 0; b <= budget; b++) {
		if (list.price[0] > b)
			best[0][b] = 0;
		else
			best[0][b] = list.price[0];
	}

	// filling rows from the 2nd-item to the last-item.
	for (unsigned int i = 1; i < list.count; i++) {
		for (unsigned int b = 0; b <= budget; b++) {
			if (list.price[i] > b) {
				best[i][b] = best[i-1][b];
				continue;
			}
			if ( best[i-1][b] > list.price[i] + best[i-1][b-list.price[i]] )
				best[i][b] = best[i-1][b];
			else
				best[i][b] = list.price[i] + best[i-1][b-list.price[i]];
		}
	}
	
	// back tracking on the dp table.
	unsigned int total = best[list.count-1][budget];
	for(unsigned int itemcount = list.count; itemcount > 1; --itemcount) {
		if ( best[itemcount - 1][total] == best[itemcount - 2][total] ) {
			cart[itemcount - 1] = 0;
		} else {
			total -= list.price[itemcount - 1];
			cart[itemcount - 1] = 1;
		}
	}
	cart[0] = ( best[0][total] == list.price[0] );

	return best[list.count-1][budget];
}

