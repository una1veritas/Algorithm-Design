#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "knapsack.h"

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

int main (int argc, const char * argv[]) {
	int budget;
	int itemCount;
	int i, s, totalPrice;
	
	budget = atoi(argv[1]);
	itemCount = argc - 2;
	int priceList[itemCount + 1];
	for (i = 0, s = 2; i < itemCount; i++, s++) {
		priceList[i] = atoi(argv[s]);
	}
	priceList[i] = 0; // the end mark.
	
	// Show our input.
	printf("%d yen for %d items.\n", budget, itemCount);
	for (i = 0; priceList[i] != 0; i++) {
		printf("%d, ", priceList[i]);
	}
	printf("\n");
	
	int bestCart[itemCount + 1];
	totalPrice = try_all_subsets(priceList, budget, bestCart);
	printf("buy items: ");
	int sum = 0;
	for (i = 0; priceList[i]; i++) {
		if ( bestCart[i] )
			printf("%d (%d), ", i, priceList[i]);
	}
	printf("\ntotally %d yen.\n", totalPrice);

    return 0;
}
