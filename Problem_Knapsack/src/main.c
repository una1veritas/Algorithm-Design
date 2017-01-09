#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define USE_COUNTER
#ifdef USE_COUNTER
long counter;
#endif

int best_recursive(int * prices, int n, int budget, char cart[]) {
	int sum, sum_backup;
	char cart_backup[n];
	
#ifdef USE_COUNTER
	counter ++;
#endif

	if ( n == 0 )
		return 0;

	sum_backup = best_recursive(prices+1, n-1, budget, cart+1);
	cart[0] = 0;
	memcpy(cart_backup, cart, n);

	if ( *prices <= budget) {
		sum = *prices + best_recursive(prices+1, n-1, budget - *prices, cart+1);
		cart[0] = 1;
		if (sum > sum_backup) {
			return sum;
		}
	}
	memcpy(cart, cart_backup, n);
	return sum_backup;
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
	
	if ( argc < 3 ) {
		printf("usage: command budget price_1 price_2 ...");
		return EXIT_FAILURE;
	}
	budget = atoi(argv[1]);
	itemCount = argc - 2;

	int plist[itemCount];
	char cart[itemCount];

	for (i = 0; i < itemCount; i++) {
		plist[i] = atoi(argv[i+2]);
	}
	
	// Show our input.
	printf("%d yen, %d items: \n", budget, itemCount);
	for (i = 0; i < itemCount; i++) {
		printf("%d, ", plist[i]);
	}
	printf("\n\n");

#ifdef USE_COUNTER
	counter = 0;
#endif
	// compute.
	swatch = clock();
	totalPrice = best_recursive(plist, itemCount, budget, cart);
	swatch = clock() - swatch;
	// Show the result.
	printf("By recursion: %.3f milli sec.\n", (double) swatch*1000 / CLOCKS_PER_SEC);
#ifdef USE_COUNTER
	printf("function calls = %ld\n\n", counter);
#endif
	printf("Total %d yen.\n", totalPrice);
	printf("Buy item id ");
	for (i = 0; i < itemCount; i++) {
		if ( cart[i] == 1 )
			printf("%d (%d), ", i, plist[i]);
	}
	printf("\n\n");

	swatch = clock();
	totalPrice = best_dp(plist, itemCount, budget);
	swatch = clock() - swatch;
	// Show the result.
	printf("By dp: %.3f milli sec.\n", (double) swatch*1000 / CLOCKS_PER_SEC);

	printf("Total %d yen.\n", totalPrice);
    return 0;
}
/*
 * $ ./Debug/Problem_Knapsack.exe 500 15, 20, 49, 52, 19, 18, 68, 38, 38, 38, 55, 39, 108, 103, 18, 41, 44, 45, 78, 78, 58, 58, 68, 58, 128, 158, 108, 138, 78, 78, 58, 158, 68, 128, 98, 158, 118, 128, 328, 228, 238, 198, 298, 64, 178, 115, 138, 148, 88, 89, 178, 138, 338, 98, 93
500 yen, 55 items:
15, 20, 49, 52, 19, 18, 68, 38, 38, 38, 55, 39, 108, 103, 18, 41, 44, 45, 78, 78, 58, 58, 68, 58, 128, 158, 108, 138, 78, 78, 58, 158, 68, 128, 98, 158, 118, 128, 328, 228, 238, 198, 298, 64, 178, 115, 138, 148, 88, 89, 178, 138, 338, 98, 93,

By recursion: 40426.000 milli sec.
function calls = 1397868482

Total 500 yen.
Buy item id 43 (64), 52 (338), 53 (98),

By dp: 0.000 milli sec.
Total 500 yen.
 *
 *
 *
 * $ ./Debug/Problem_Knapsack.exe 500 15, 15, 20, 15, 20, 21, 21, 20, 20, 15, 61, 21, 20, 30, 30, 30, 30, 10, 10, 10, 100, 21, 21, 21, 21, 43, 21, 33, 33, 33, 33, 21, 21, 10, 10, 33
 *
 *$ ./Debug/Problem_Knapsack.exe 500 15, 15, 20, 15, 20, 21, 21, 20, 20, 15, 61, 21, 20, 30, 30, 30, 30, 10, 10, 10, 100, 21, 21, 21, 21, 43, 21, 33, 33, 33, 33, 21, 21
500 yen, 33 items:
15, 15, 20, 15, 20, 21, 21, 20, 20, 15, 61, 21, 20, 30, 30, 30, 30, 10, 10, 10, 100, 21, 21, 21, 21, 43, 21, 33, 33, 33, 33, 21, 21,

By recursion: 232370.000 milli sec.
function calls = 1217729287

Total 500 yen.
Buy item id 14 (30), 15 (30), 16 (30), 17 (10), 18 (10), 19 (10), 20 (100), 23 (21), 24 (21), 25 (43), 26 (21), 27 (33), 28 (33), 29 (33), 30 (33), 31 (21), 32 (21),

By dp: 0.000 milli sec.
Total 500 yen.
 *
 *$ ./Debug/Problem_Knapsack.exe 500 15, 15, 20, 15, 20, 21, 21, 20, 20, 15, 61, 21, 20, 30, 30, 30, 30, 10, 10, 10, 100, 21, 21, 21, 21, 43, 21, 33, 33, 33, 33, 21, 21, 10, 10, 33

500 yen, 36 items:
15, 15, 20, 15, 20, 21, 21, 20, 20, 15, 61, 21, 20, 30, 30, 30, 30, 10, 10, 10, 100, 21, 21, 21, 21, 43, 21, 33, 33, 33, 33, 21, 21, 10, 10, 33,

By recursion: 1686296.000 milli sec.
function calls = 1723858092
28.1 min., 1.7G times
Total 500 yen.
Buy item id 14 (30), 15 (30), 16 (30), 19 (10), 20 (100), 23 (21), 24 (21), 25 (43), 26 (21), 28 (33), 29 (33), 30 (33), 31 (21), 32 (21), 33 (10), 34 (10), 35 (33),

By dp: 0.000 milli sec.
Total 500 yen.
 *
 */
