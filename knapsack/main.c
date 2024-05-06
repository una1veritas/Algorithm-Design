#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "knapsack.h"

//#define USE_COUNTER
#ifdef USE_COUNTER
long counter;
#endif

int main (int argc, const char * argv[]) {
	int budget, total;
	int n;
	clock_t swatch;
	
	if ( argc < 3 ) {
		printf("usage: command budget price_1 price_2 ...");
		return EXIT_FAILURE;
	}
	budget = atoi(argv[1]);
	n = argc - 2;

	int plist[n];
	int i;
	for (i = 0; i < n; ++i) {
		plist[i] = atoi(argv[2+i]);
	}
	
	// Show our input.
	printf("%d yen, %d items: \n", budget, n);
	for (int i = 0; i < n; i++) {
		printf("%d, ", plist[i]);
	}
	printf("\n\n");
	fflush(stdout);

	char cart[n];
	for(int i = 0; i < n; ++i)
		cart[i] = 0;

#ifdef USE_COUNTER
	counter = 0;
#endif
	for(int i = 0; i < n; ++i)
		cart[i] = 0;
	// compute.
	swatch = clock();
	//total = knapsack_recursive(plist, n, budget, cart);
	total = knapsack_allsubset(plist, n, budget, cart);
	swatch = clock() - swatch;
	// Show the result.
	printf("By enumerating all subsets: %.3f sec.\n", (double) swatch / CLOCKS_PER_SEC);
	//printf("By recursion: %.3f sec.\n", (double) swatch / CLOCKS_PER_SEC);
#ifdef USE_COUNTER
	printf("function calls = %ld\n", counter);
#endif
	printf("Total %d yen.\n", total);
	printf("Buy item id ");
	for (i = 0; i < n; i++) {
		if ( cart[i] )
			printf("%d (%d), ", i, plist[i]);
	}
	printf("\n\n");

    return 0;
}
