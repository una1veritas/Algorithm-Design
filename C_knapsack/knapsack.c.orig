#include <stdio.h>
#include <stdlib.h>
#include <time.h> /* 時間計測用 */

typedef struct {
	int * array;
	int size;
} intarray;

int best_recursive(intarray * pricelist, int start, int budget) {
	int sum_skip, sum_buy;
	if ( start >= pricelist->size ) {
		return 0;
	}
	sum_skip = best_recursive(pricelist, start+1, budget);
	// default --- don't buy it
	if ( pricelist->array[start] > budget)
		return sum_skip;
	sum_buy = pricelist->array[start] + best_recursive(pricelist,
			start + 1,
			budget - pricelist->array[start]);
	if (sum_buy > sum_skip)
		return sum_buy;
	return sum_skip;
}

int main (int argc, const char * argv[]) {
	// Get the input.
	int budget = atoi(argv[1]);
	int number = argc - 2;
	int prices[number], bools[number];
	intarray
		pricelist = { prices, number },
		cart = { bools, number };
	pricelist.array = prices;
	pricelist.size = number;
	for (int i = 0; i < number; ++i) {
		pricelist.array[i] = atoi(argv[2+i]);
	}
	cart.array = bools;
	
	// Show our input.
	printf("%d yen, %d items.\n", budget, number);
	for (int i = 0; i < number; ++i) {
		printf("%d, ", prices[i]);
	}
	printf("\n\n");

	int totalPrice = 0;
	clock_t swatch = clock(); 	/* 時間計測用 */
	totalPrice = best_recursive(&pricelist, 0, budget);
	swatch = clock() - swatch; 	/* 時間計測用 */
	printf("spent %g ms.\n", swatch/(double)CLOCKS_PER_SEC * 1000); /* for stop watch */
	printf("buy items: ");
	printf("\ntotally %d yen.\n", totalPrice);

	swatch = clock(); 	/* 時間計測用 */
//	totalPrice = bestprice_enumerate(inst.price, inst.number, inst.budget);
	swatch = clock() - swatch; 	/* 時間計測用 */
	printf("spent %g ms.\n", swatch/(double)CLOCKS_PER_SEC * 1000); /* for stop watch */
	printf("buy items: ");
	printf("\ntotally %d yen.\n", totalPrice);

	return 0;
}
