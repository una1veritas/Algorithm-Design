#include <stdio.h>
#include <stdlib.h>

int knapsack_allsubset(const int prices[], int nsize, const int budget, char cart[]) {
	int sum, best;
	int item;

	char subset[nsize+1];
	for(int i = 0; i < nsize+1; ++i)
		subset[i] = 0;

	best = 0;
	for(; subset[nsize] == 0 ;) {
		sum = 0;
		for(item = 0; item < nsize && sum <= budget; ++item) {
			if (subset[item] != 0 )
				sum += prices[item];
		}
		if (best < sum && sum <= budget ) {
			//fprintf(stderr,"updated\n");
			best = sum;
			for(int i = 0; i < nsize; ++i)
				cart[i] = subset[i];
			cart[nsize] = 0;
		}
		// increment subset
		for(item = 0; item < nsize + 1; ++item) {
			if ( subset[item] == 0 ) {
					subset[item] = 1;
					break;
			}
			subset[item] = 0;
		}
	}

	return best;
}
