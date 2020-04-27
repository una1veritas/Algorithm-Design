#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knapsack.h"
/*
int bestcart_enumerate(Knapsack * list, int budget, char cart[]) {
	int bestPrice = 0, sum;
	int n = list.number;
	char tempcart[n+1];
	memset(tempcart, 0, n+1);

	for (;;) {
		sum = 0;
		for(int i = 0; i < n; ++i) {
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
		for(int i = 0; i < n + 1; ++i) {
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

int bestcart_recursive(Knapsack * list, int fromindex, Knapsack * best) {
	int sum_skip, sum_buy;
	if ( fromindex == list->number ) {
		return 0;
	}
	char tcart_buy[list->number], tcart_dont[list->number];
	sum_skip = bestcart_recursive(remained, budget, tcart_dont);
	// default --- don't buy it
	*cart = 0;
	memcpy(cart+1, tcart_dont, remained.number);
	if ( *list.price > budget)
		return sum_skip;
	sum_buy = *list.price + bestcart_recursive(remained, budget - *list.price, tcart_buy);
	if (sum_buy > sum_skip) {
		*cart = 1; // buy it
		memcpy(cart+1, tcart_buy, remained.number);
		return sum_buy;
	}
	return sum_skip;
}
*/

int bestprice_recursive(Knapsack * inst, int fromIndex, int rbudget) {
	int sum_skip, sum_buy;
	if ( fromIndex >= inst->number ) {
		return inst->budget - rbudget;
	}
	sum_skip = bestprice_recursive(inst, fromIndex+1, rbudget);
	// default --- don't buy it
	if ( inst->price[fromIndex] > rbudget)
		return sum_skip;
	sum_buy = inst->price[fromIndex] + bestprice_recursive(inst, fromIndex + 1, rbudget - inst->price[fromIndex]);
	if (sum_buy > sum_skip)
		return sum_buy;
	return sum_skip;
}

/*
int bestcart_dp(Knapsack * list, char cart[]) {
	int best[list.number][budget+1];

	// filling the only-1st-item row.
	for (int b = 0; b <= budget; b++) {
		if (list.price[0] > b)
			best[0][b] = 0;
		else
			best[0][b] = list.price[0];
	}

	// filling rows from the 2nd-item to the last-item.
	for (int i = 1; i < list.number; i++) {
		for (int b = 0; b <= budget; b++) {
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
	int total = best[list.number-1][budget];
	for(int itemcount = list.number; itemcount > 1; --itemcount) {
		if ( best[itemcount - 1][total] == best[itemcount - 2][total] ) {
			cart[itemcount - 1] = 0;
		} else {
			total -= list.price[itemcount - 1];
			cart[itemcount - 1] = 1;
		}
	}
	cart[0] = ( best[0][total] == list.price[0] );

	return best[list.number-1][budget];
}
*/
