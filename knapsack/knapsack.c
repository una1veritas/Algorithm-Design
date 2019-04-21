#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "knapsack.h"

#undef PRINT_COMBINATION

int bestPrice_recursive(int list[], int budget) {
	int s, ss;
	
	if ( *list == 0 ) 
		return 0;
	s = bestPrice_recursive(list+1, budget);
	if ( *list > budget) 
		return s;
	ss = *list + bestPrice_recursive(list+1, budget - *list);
	if (ss > s) 
		return ss;
	return s;
}

int bestPrice_dp(int list[], int budget) {
	int i, n;
	int b;
	
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


int try_all_subsets(int list[], int budget, int cart[]) {
	int n, i;
	int bestPrice = 0, sum;
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
#ifdef PRINT_COMBINATION
			printf("%d, ", subset[i]);
#endif
		}
		if ( sum <= budget && sum > bestPrice ) {
			bestPrice = sum;
			for(i = 0; i < n+1; ++i)
				cart[i] = subset[i];
		}
#ifdef PRINT_COMBINATION
		printf(": %d\n", sum);
#endif
		/* make next combination */
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
