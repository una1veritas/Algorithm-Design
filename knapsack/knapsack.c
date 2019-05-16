#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knapsack.h"

unsigned int best_enumerate(PriceList list, unsigned int budget, unsigned char cart[]) {
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

unsigned int best_recursive(PriceList list, unsigned int budget, unsigned int item, unsigned char cart[]) {
	unsigned int sum_skip, sum_buy;
	unsigned char tcart_buy[list.count], tcart_dont[list.count];
	if ( item >= list.count )
		return 0;
	sum_skip = best_recursive(list, budget, item+1, tcart_dont);
	// default --- don't buy it
	cart[item] = 0;
	for(int i = item + 1; i < list.count; ++i)
		cart[i] = tcart_dont[i];
	if ( list.price[item] > budget)
		return sum_skip;
	sum_buy = list.price[item] + best_recursive(list, budget - list.price[item], item+1, tcart_buy);
	if (sum_buy > sum_skip) {
		cart[item] = 1; // buy it
		for(int i = item+1; i < list.count; ++i)
			cart[i] = tcart_buy[i];
		return sum_buy;
	}
	return sum_skip;
}

unsigned int best_dp(PriceList list, unsigned int budget, unsigned char cart[]) {
	unsigned int best[list.count][budget+1];

	for (unsigned int b = 0; b <= budget; b++) {
		if (list.price[0] > b) {
			best[0][b] = 0;
		} else {
			best[0][b] = list.price[0];
		}
	}

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
	

#ifdef STATUS_PRINT_STDOUT
	for(int i = 0; i < list.count; ++i) {
		for(int p = 0; p <= budget; ++p) {
			printf("%3d ", best[i][p]);
		}
		printf("\n");
	}
#endif

	unsigned int total = best[list.count-1][budget];

	unsigned int itemcount = list.count;
	while (total > 0) {
		if ( itemcount == 1 ) {
			if ( best[0][total] == list.price[0] )
				cart[0] = 1;
			else
				cart[0] = 0;
			break;
		}
		if ( best[itemcount - 1][total] == best[itemcount - 2][total] ) {
			cart[itemcount - 1] = 0;
		} else {
			total -= list.price[itemcount - 1];
			cart[itemcount - 1] = 1;
		}
		--itemcount;
	}

	return best[list.count-1][budget];
}

