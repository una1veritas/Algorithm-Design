#include <stdio.h>
#include <stdlib.h>

int knapsack_recursive(const int prices[], const int nsize, const int budget, char cart[]) {
	if ( nsize == 0 )
		return 0;

	int sum0, sum1;
	char cart0[nsize];
	char cart1[nsize];

	sum0 = knapsack_recursive(prices, nsize - 1, budget, cart0);

	if ( prices[nsize - 1] <= budget) {
		sum1 = prices[nsize - 1] + knapsack_recursive(prices, nsize - 1, budget - prices[nsize-1], cart1);
		if (sum1 > sum0) {
			for(int i = 0; i < nsize - 1; ++i)
				cart[i] = cart1[i];
			cart[nsize - 1] = 1;
			return sum1;
		}
	}
	for(int i = 0; i < nsize - 1; ++i) {
		cart[i] = cart0[i];
	}
	cart[nsize - 1] = 0;
	return sum0;
}
