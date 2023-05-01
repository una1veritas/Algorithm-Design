#include <stdio.h>
#include <stdlib.h>

int knapsack_allsubset(const int prices[], const int budget, char cart[]) {
	int sum, best;
	int item, n;

	for(n = 0; prices[n] != 0; ++n) ;

	char subset[n+1];
	for(int i = 0; i < n+1; ++i)
		subset[i] = 0;

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
			for(int i = 0; i < n; ++i)
				cart[i] = subset[i];
			cart[n] = 0;
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
