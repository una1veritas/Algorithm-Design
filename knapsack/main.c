#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "knapsack.h"

int main (int argc, const char * argv[]) {
	unsigned int budget;
	unsigned int totalPrice;
	
	budget = atoi(argv[1]);
	PriceList pricelist = { argc - 2, NULL };
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
	fflush(stdout);
	
	unsigned char bestCart[pricelist.count];
	for(int i = 0; i < pricelist.count; ++i)
		bestCart[i] = 0;

	clock_t swatch = clock();
	totalPrice = bestcart_recursive(pricelist, budget, bestCart);
	swatch = clock() - swatch;
	printf("spent %g ms.\n", swatch/(double)CLOCKS_PER_SEC * 1000);
	printf("buy items: ");
	int sum = 0;
	for (unsigned int i = 0; i < pricelist.count; i++) {
		if ( bestCart[i] ) {
			sum += pricelist.price[i];
			printf("%d (%d), ", i, pricelist.price[i]);
		}
	}
	if (sum != totalPrice)
		printf("Error: totalPrice and sum %d do not agree with.", sum);
	printf("\ntotally %d yen.\n", totalPrice);

	free(pricelist.price);
    return 0;
}
