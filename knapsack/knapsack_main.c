#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <stdbool.h>

#include "knapsack.h"

//#define USE_COUNTER
#ifdef USE_COUNTER
long counter;
#endif

int main (int argc, const char * argv[]) {
	int budget, total;
	int n;
	// clock_t swatch;
	struct timespec start, stop;
	long secs, nanos;
	
	if ( argc < 3 ) {
		printf("usage: command budget price_1 price_2 ...\n");
		return EXIT_FAILURE;
	}

	budget = atoi(argv[1]);
	n = argc - 2;
	if ( n <= 0 ) {
		printf("no items.\n");
		return EXIT_FAILURE;
	}

	int plist[n + 1]; 	// the last item should be zero, the termination code.
	int i;
	for (i = 0; i < n; ++i) {
		plist[i] = atoi(argv[2+i]);
	}
	if (plist[n-1] == 0) {
		n -= 1;
	} else {
		plist[n] = 0;
	}
	
	// Show our input.
	printf("Up to %d yen from %d items: \n", budget, n);
	for (int i = 0; i < n; i++) {
		printf("%d, ", plist[i]);
	}
	printf("\n\n");
	fflush(stdout);

	bool cart[n];
	for(int i = 0; i < n; ++i)
		cart[i] = false;

	// compute.
	printf("Find the best by recursive function.\n");
#ifdef USE_COUNTER
	counter = 0;
#endif
	timespec_get(&start, TIME_UTC); 	// swatch = clock();
	total = knapsack_recursive(plist, budget, cart);
	timespec_get(&stop, TIME_UTC);
	secs = stop.tv_sec - start.tv_sec; // swatch = clock() - swatch;
	nanos = stop.tv_nsec - start.tv_nsec;
	printf("Time spent: %.6f sec.\n", (double) secs + ((double) nanos/1e9) );
#ifdef USE_COUNTER
	printf("The execution passed through the counter %ld times.\n", counter);
#endif
	printf("Total %d yen.\n", total);
	printf("Buy item id ");
	for (i = 0; i < n; i++) {
		if ( cart[i] )
			printf("%d (%d), ", i, plist[i]);
	}
	printf("\n\n");

/*
	// -----------------------
	printf("Find the best by enumerating all subsets.\n");
#ifdef USE_COUNTER
	counter = 0;
#endif
	timespec_get(&start, TIME_UTC); 	// swatch = clock();
	total = knapsack_enumerate(plist, budget, cart);
	timespec_get(&stop, TIME_UTC); 	// swatch = clock() - swatch;
	secs = stop.tv_sec - start.tv_sec; // swatch = clock() - swatch;
	nanos = stop.tv_nsec - start.tv_nsec;
	printf("Time spent: %.6f sec.\n", (double) secs + ((double) nanos/1e9) );
#ifdef USE_COUNTER
	printf("The execution passed through the counter %ld times.\n", counter);
#endif
	printf("Total %d yen.\n", total);
	printf("Buy item id ");
	for (i = 0; i < n; i++) {
		if ( cart[i] )
			printf("%d (%d), ", i, plist[i]);
	}
	printf("\n\n");
*/
    return 0;
}
