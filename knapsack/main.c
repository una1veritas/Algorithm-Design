#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "knapsack.h"

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
	printf("%d yen, %d items.\n", budget, itemCount);
	for (i = 0; priceList[i] != 0; i++) {
		printf("%d, ", priceList[i]);
	}
	printf("\n\n");
	
	unsigned char bestCart[itemCount + 1];
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
