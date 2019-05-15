#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knapsack.h"

unsigned int try_all_subsets(PriceList list, unsigned int budget, unsigned char cart[]) {
	unsigned int n, i;
	unsigned int bestPrice = 0, sum;
	// count the number
	for(n = 0; list.price[n]; ++n) {}
	unsigned char tempcart[n+1];
	memset(tempcart, 0, n+1);
	// try all combinations
	for (;;) {
		sum = 0;
		for(i = 0; i < n; ++i) {
			if ( tempcart[i] )
				sum += list.price[i];
#ifdef STATUS_PRINT_STDOUT
			printf("%d, ", tempcart[i]);
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
		if ( tempcart[n] )
			break;
		for(i = 0; i < n + 1; ++i) {
			if ( tempcart[i] ) {
				tempcart[i] = 0;
				continue;
			} else {
				tempcart[i] = 1;
				break;
			}
		}
	}
	return bestPrice;
}

unsigned int bestPrice_recursive(PriceList list, unsigned int budget, unsigned int item, unsigned char cart[]) {
	unsigned int sum_skip, sum_buy;
	unsigned char tcart1[list.count], tcart2[list.count];
	if ( item >= list.count )
		return 0;
	for(int i = 0; i < list.count; ++i) {
		tcart1[i] = cart[i];
		tcart2[i] = cart[i];
	}
	sum_skip = bestPrice_recursive(list, budget, item+1, tcart1);
	if ( list.price[item] > budget) {
		for(int i = 0; i < list.count; ++i)
			cart[i] = tcart1[i];
		return sum_skip;
	}
	sum_buy = list.price[item] + bestPrice_recursive(list, budget - list.price[item], item+1, tcart2);
	if (sum_buy > sum_skip) {
		for(int i = 0; i < list.count; ++i)
			cart[i] = tcart2[i];
		cart[item] = 1;
		return sum_buy;
	}
	for(int i = 0; i < list.count; ++i)
		cart[i] = tcart1[i];
	return sum_skip;
}

unsigned int bestPrice_dp(PriceList list, unsigned int budget, unsigned char cart[]) {
	unsigned int i, b;
	
	unsigned int best[list.count][budget+1];

	for (b = 0; b <= budget; b++) {
		if (list.price[0] > b) {
			best[0][b] = 0;
		} else {
			best[0][b] = list.price[0];
		}
	}

	for (i = 1; i < list.count; i++) {
		for (b = 0; b <= budget; b++) {
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
	
	return best[list.count][budget];
}

