#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "knapsack.h"

int main (int argc, const char * argv[]) {
	unsigned int budget;
	PriceList pricelist;
	unsigned int totalPrice;
	
	budget = atoi(argv[1]);
	pricelist.count = argc - 2;
	pricelist.price = (unsigned int *) malloc(sizeof(unsigned int)*pricelist.count);
	for (unsigned int i = 0; i < pricelist.count; i++) {
		pricelist.price[i] = atoi(argv[i+2]);
	}
	
	// Show our input.
	printf("%d yen, %d items.\n", budget, pricelist.count);
	for (unsigned int i = 0; i < pricelist.count; i++) {
		printf("%d, ", pricelist.price[i]);
	}
	printf("\n\n");
	
	unsigned char bestCart[bitstobytes(pricelist.count)];
	for(int i = 0; i < bitstobytes(pricelist.count); ++i)
		bestCart[i] = 0;

	clock_t swatch = clock();
	totalPrice = bestcart_recursive(pricelist, budget, 0, bestCart);
	swatch = clock() - swatch;
	printf("spent %g m sec.\n", swatch/(double)CLOCKS_PER_SEC * 1000);
	printf("buy items: ");
	int sum = 0;
	for (unsigned int i = 0; i < pricelist.count; i++) {
		if ( bitcheck(bestCart, i) )
			printf("%d (%d), ", i, pricelist.price[i]);
	}
	printf("\ntotally %d yen.\n", totalPrice);

	free(pricelist.price);
    return 0;
}
