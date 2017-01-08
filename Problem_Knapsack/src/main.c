#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int best_recursive(int * price, int n, int budget, char cart[]) {
	int sum_notbuy, sum_buy;
	char cart_notbuy[n];
	
	if ( *price == 0 )
		return 0;

	sum_notbuy = best_recursive(price+1, n-1, budget, cart+1);
	memcpy(cart_notbuy, cart, n);
	cart_notbuy[0] = 0;

	if ( *price <= budget) {
		sum_buy = *price + best_recursive(price+1, n-1, budget - *price, cart+1);
		cart[0] = 1;
		if (sum_buy > sum_notbuy) {
			return sum_buy;
		}
	}
	memcpy(cart, cart_notbuy, n);
	return sum_notbuy;
}

int best_dp(int price[], int n, int budget) {
	int i, b;
	
	int best[n][budget+1];

	for (b = 0; b <= budget; b++) {
		if (price[0] > b) {
			best[0][b] = 0;
		} else {
			best[0][b] = price[0];
		}
	}

	for (i = 1; i < n; i++) {
		for (b = 0; b <= budget; b++) {
			if (price[i] > b) {
				best[i][b] = best[i-1][b];
				continue;
			}
			if ( best[i-1][b] > price[i] + best[i-1][b-price[i]] ) {
				best[i][b] = best[i-1][b];
			} else {
				best[i][b] = price[i] + best[i-1][b-price[i]];
			}
		}
	}
	
	return best[n-1][budget];
}


int main (int argc, const char * argv[]) {
	int budget;
	int itemCount;
	int i, totalPrice;
	clock_t swatch;
	
	budget = atoi(argv[1]);
	itemCount = argc - 2;

	int priceList[itemCount+1];
	char cart[itemCount];
	//int * priceList; priceList = (int *) malloc(sizeof(int) * (itemCount+1) );
	for (i = 0; i < itemCount; i++) {
		priceList[i] = atoi(argv[i+2]);
	}
	priceList[itemCount] = 0;
	
	// Show our input.
	printf("%d yen for %d items.\n", budget, itemCount);
	for (i = 0; i < itemCount; i++) {
		printf("%d, ", priceList[i]);
	}
	printf("\n");
	
	// compute.
	swatch = clock();
	totalPrice = best_recursive(priceList, itemCount, budget, cart);
	swatch = clock() - swatch;
	// Show the result.
	printf("bought totally %d yen.\n", totalPrice);
	printf("By recursion: %f\n", (double) swatch / CLOCKS_PER_SEC);

	for (i = 0; i < itemCount; i++) {
		if ( cart[i] == 1 )
			printf("%d: %d,\n", i, priceList[i]);
	}
	printf("\n");

	swatch = clock();
	totalPrice = best_dp(priceList, itemCount, budget);
	swatch = clock() - swatch;
	// Show the result.
	printf("bought totally %d yen.\n", totalPrice);
	printf("By dp: %f\n", (double) swatch / CLOCKS_PER_SEC);
    return 0;
}
