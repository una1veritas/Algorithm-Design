#include <stdio.h>
#include <stdlib.h>

int knapsack_recursive(const int prices[], const int budget, char cart[], int m) {
	int sum0, sum1;
	char cart0[m];
	char cart1[m];

	if ( m == 0 )
		return 0;

	for(int i = 0; i < m; ++i) {
		cart0[i] = cart[i];
		cart1[i] = cart[i];
	}

	sum0 = knapsack_recursive(prices, budget, cart0, m - 1);

	if ( prices[m-1] <= budget) {
		sum1 = prices[m-1] + knapsack_recursive(prices, budget - prices[m-1], cart1, m - 1);
		if (sum1 > sum0) {
			for(int i = 0; i < m - 1; ++i)
				cart[i] = cart1[i];
			cart[m - 1] = 1;
			return sum1;
		}
	}
	for(int i = 0; i < m - 1; ++i) {
		cart[i] = cart0[i];
	}
	cart[m - 1] = 0;
	return sum0;
}
