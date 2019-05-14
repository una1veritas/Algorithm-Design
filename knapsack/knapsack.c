#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knapsack.h"

price try_all_subsets(price list[], price budget, mybool cart[]) {
	int n, i;
	price bestPrice = 0, sum;
	// count the number
	for(n = 0; list[n]; ++n) {}
	int subset[n+1];
	// initialize subset: cart is "valid" while subset[n] == 0.
	for(i = 0; i < n + 1; ++i)
		subset[i] = 0;
	// try all combinations
	while ( subset[n] == 0 ) {
		sum = 0;
		for(i = 0; i < n; ++i) {
			if ( subset[i] )
				sum += list[i];
#ifdef STATUS_PRINT_STDOUT
			printf("%d, ", subset[i]);
#endif
		}
		if ( sum <= budget && sum > bestPrice ) {
			bestPrice = sum;
			memcpy(cart, subset, n);
		}
#ifdef STATUS_PRINT_STDOUT
		printf(": %d\n", sum);
#endif
		/* make the next combination */
		for(i = 0; i < n + 1; ++i) {
			if ( subset[i] ) {
				subset[i] = 0;
				continue;
			} else {
				subset[i] = 1;
				break;
			}
		}
	}
	return bestPrice;
}

price bestPrice_recursive(price list[], price budget) {
	price sum_skip, sum_buy;
	
	if ( *list == 0 ) 
		return 0;
	sum_skip = bestPrice_recursive(list+1, budget);
	if ( *list > budget) 
		return sum_skip;
	sum_buy = *list + bestPrice_recursive(list+1, budget - *list);
	if (sum_buy > sum_skip)
		return sum_buy;
	return sum_skip;
}

price bestPrice_dp(price list[], price budget) {
	int i, n;
	price b;
	
	for (n = 1; list[n] != 0; n++);
	int best[n][budget+1];

	for (b = 0; b <= budget; b++) {
		if (list[0] > b) {
			best[0][b] = 0;
		} else {
			best[0][b] = list[0];
		}
	}

	for (i = 1; i < n; i++) {
		for (b = 0; b <= budget; b++) {
			if (list[i] > b) {
				best[i][b] = best[i-1][b];
				continue;
			}
			if ( best[i-1][b] > list[i] + best[i-1][b-list[i]] ) {
				best[i][b] = best[i-1][b];
			} else {
				best[i][b] = list[i] + best[i-1][b-list[i]];
			}
		}
	}
	
	return best[n-1][budget];
}

