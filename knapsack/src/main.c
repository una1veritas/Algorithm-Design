#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "knapsack.h"

int main (int argc, const char * argv[]) {
	int budget;
	int totalPrice;
	
	budget = atoi(argv[1]);
	PriceList plist = { argc - 2, NULL };
	plist.price = (int *) malloc(sizeof(int)*plist.number);
	for (int i = 0; i < plist.number; i++) {
		plist.price[i] = atoi(argv[i+2]);
	}
	
	// Show our input.
	printf("%d yen, %d items.\n", budget, plist.number);
	for (int i = 0; i < plist.number; i++) {
		printf("%d, ", plist.price[i]);
	}
	printf("\n\n");
	
	char bestCart[plist.number];
	for(int i = 0; i < plist.number; ++i)
		bestCart[i] = 0;

	clock_t swatch = clock();
	totalPrice = bestcart_recursive(plist, budget, bestCart);
	swatch = clock() - swatch;
	printf("spent %g ms.\n", swatch/(double)CLOCKS_PER_SEC * 1000);
	printf("buy items: ");
	int sum = 0;
	for (int i = 0; i < plist.number; i++) {
		if ( bestCart[i] ) {
			sum += plist.price[i];
			printf("%d (%d), ", i, plist.price[i]);
		}
	}
	if (sum != totalPrice)
		printf("Error: totalPrice and sum %d do not agree with.", sum);
	printf("\ntotally %d yen.\n", totalPrice);

	free(plist.price);
    return 0;
}
