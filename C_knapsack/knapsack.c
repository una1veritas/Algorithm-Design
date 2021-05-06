#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int * array;
	int size;
} intarray;

int best_recursive(intarray * pricelist, int start, int budget) {
	int sum_skip, sum_buy;
	if ( start >= pricelist->size ) {
		return 0;
	}
    // 買わない場合
	sum_skip = best_recursive(pricelist, start+1, budget);
	if ( pricelist->array[start] > budget)
		return sum_skip;
    // 買う場合
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
	int prices[number];
	intarray pricelist = { prices, number };
	for (int i = 0; i < number; ++i) {
		pricelist.array[i] = atoi(argv[2+i]);
	}
	
	// Show our input.
	printf("%d yen, %d items.\n", budget, number);
	for (int i = 0; i < number; ++i) {
		printf("%d, ", prices[i]);
	}
	printf("\n\n");

	int totalPrice = 0;
	totalPrice = best_recursive(&pricelist, 0, budget);
	//printf("buy items: ");
	printf("\ntotally %d yen.\n", totalPrice);

	return 0;
}
