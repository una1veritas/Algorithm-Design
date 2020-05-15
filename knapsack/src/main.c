#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* 時間計測用 */

#include "knapsack.h"

int main (int argc, const char * argv[]) {
	int budget = atoi(argv[1]);
	int pricelist[argc - 2];  /* malloc のかわり */
	Knapsack inst = { pricelist, argc - 2, budget };
	for (int i = 0; i < inst.number; ++i) {
		inst.price[i] = atoi(argv[i+2]);
	}
	
	// Show our input.
	printf("%d yen, %d items.\n", inst.budget, inst.number);
	for (int i = 0; i < inst.number; i++) {
		printf("%d, ", inst.price[i]);
	}
	printf("\n\n");

	int totalPrice;
	clock_t swatch = clock(); 	/* 時間計測用 */
	totalPrice = bestprice_recursive(&inst, 0, inst.budget);
	swatch = clock() - swatch; 	/* 時間計測用 */
	printf("spent %g ms.\n", swatch/(double)CLOCKS_PER_SEC * 1000); /* for stop watch */
	printf("buy items: ");
	printf("\ntotally %d yen.\n", totalPrice);

	swatch = clock(); 	/* 時間計測用 */
	totalPrice = bestprice_enumerate(&inst);
	swatch = clock() - swatch; 	/* 時間計測用 */
	printf("spent %g ms.\n", swatch/(double)CLOCKS_PER_SEC * 1000); /* for stop watch */
	printf("buy items: ");
	printf("\ntotally %d yen.\n", totalPrice);

	return 0;
}
