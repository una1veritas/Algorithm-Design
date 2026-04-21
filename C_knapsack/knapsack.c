#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "knapsack.h"

int best_recursive(int pricelist[], int n, int spot, int budget, bool buyornot[]) {
	int sum_skip, sum_buy;
	if ( spot >= n ) {
		return 0;
	}
    // 買わない場合
	sum_skip = best_recursive(pricelist, n, spot+1, budget, buyornot);
	if ( pricelist[spot] > budget) {
		buyornot[spot] = false;
		return sum_skip;
	}
    // 買う場合
	buyornot[spot] = true;
	sum_buy = pricelist[spot] + best_recursive(pricelist, n, spot + 1, budget - pricelist[spot], buyornot);
	if (sum_buy > sum_skip) {
		buyornot[spot] = true;
		return sum_buy;
	}
	buyornot[spot] = false;
	return sum_skip;
}

int main (int argc, const char * argv[]) {
	// Get the input.
	int budget = atoi(argv[1]);
	int number = argc - 2;
	int prices[number];
	bool buyornot[number];
	for (int i = 0; i < number; ++i) {
		prices[i] = atoi(argv[2+i]);
	}
	
	// Show our input.
	printf("%d yen, the following %d items:\n", budget, number);
	for (int i = 0; i < number; ++i) {
		printf("%d, ", prices[i]);
	}
	printf("\n\n");

	int totalPrice = 0;
	totalPrice = best_recursive(prices, number, 0, budget, buyornot);
	printf("buy items: ");
	for (int i = 0; i < number; ++i) {
		if ( buyornot[i] )
			printf("[%d] %d, ", i, prices[i]);
	}
	printf("\ntotally %d yen.\n", totalPrice);

	return 0;
}
