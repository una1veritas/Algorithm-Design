#include <stdio.h>
#include <stdlib.h>

int knapsack_allsubset(const int prices[], const int n, const int budget, char cart[]) {
	int sum, best;
	int item;
	char subset[n+1];
	memset(subset, 0, n+1);

	best = 0;
	for(; subset[n] == 0 ;) {
		sum = 0;
		for(item = 0; item < n && sum <= budget; ++item) {
			if (subset[item] != 0 )
				sum += prices[item];
		}
		if (best < sum && sum <= budget ) {
			//fprintf(stderr,"updated\n");
			best = sum;
			memcpy(cart, subset, n); // copy from subset to cart
		}
		// increment subset
		for(item = 0; item < n+1; ++item) {
			if ( subset[item] == 0 ) {
					subset[item] = 1;
					break;
			}
			subset[item] = 0;
		}
	}

	return best;
}
