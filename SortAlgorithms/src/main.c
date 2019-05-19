#include <stdio.h>
#include <stdlib.h>

#include "stopwatch.h"
#include "sortalgorithms.h"

void make_randarray(long array[], long size, long range) {
	long r;
	r = (rand() % range) + 2;
	for (int i = 0; i < size; i++) {
		array[i] = rand() % r;
	}
}

int main(int argc, char * args[]) {
	data * dt;
	index * ix, size = 1000;

	stopwatch sw;
	long elapsed;

	long range = 1317;
	long seed = 7;

	long rep = 1000;
	long t;
	long worst, best;
	double sum;

	if (argc >= 2) {
		size = atol
				(args[1]);
	}
	if (argc >= 3) {
		range = atol(args[2]);
	}

	if (argc >= 4) {
		seed = atol(args[3]);
	}

	if (argc >= 5) {
		rep = atol(args[4]);
	}

	printf("Size: %ld, Range within: 0 -- %ld, Initial Seed: %ld, Number of trials: %ld\n",
			size, range, seed, rep);

	dt = (data *)malloc(sizeof(data)*size);
	ix = (index *)malloc(sizeof(index)*size);

	// Merge Sort
	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		make_randarray(dt, size, range);
		for(index i = 0; i < size; ++i)
			ix[i] = i;
		//
		stopwatch_start(&sw);
		mergeSort(dt, ix, size);
		stopwatch_stop(&sw);

		elapsed = stopwatch_clocks(&sw);
		//printf("Merge:      \t %ld\n",elapsed);

		if (t == 0) {
			worst = elapsed;
			best = elapsed;
		} else {
			if (elapsed > worst) {
				worst = elapsed;
			}
			if (elapsed < best) {
				best = elapsed;
			}
		}
		sum += elapsed;
	}
	printf("Merge:    \tworst %ld clk., \tbest %ld clk., \tavr. %.1f clk.\n",
			worst, best, sum / (float)rep);

	// showing the last sorted contents
	printf("\n");
	for (int i = 0; i < size; i++) {
		printf("%3ld ", ix[i]);
		if (i > 32) {
			printf("... ");
			break;
		}
	}
	printf("\n--------\n");
	for (int i = 0; i < size; i++) {
		printf("%3ld ", dt[ix[i]]);
		if (i > 32) {
			printf("... ");
			break;
		}
	}
	printf("\n\n");

	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		make_randarray(dt, size, range);
		for(index i = 0; i < size; ++i)
			ix[i] = i;
		//
		stopwatch_start(&sw);
		quickSort(dt, ix, size);
		stopwatch_stop(&sw);
		elapsed = stopwatch_clocks(&sw);
		// showing the contents
		//
		if (t == 0) {
			worst = elapsed;
			best = elapsed;
		} else {
			if (elapsed > worst) {
				worst = elapsed;
			}
			if (elapsed < best) {
				best = elapsed;
			}
		}
		sum += elapsed;
	}
	printf("Quick:    \tworst %ld clk., \tbest %ld clk., \tavr. %.1f clk.\n",
			worst, best, sum / (float)rep);
	/*
	// showing the last sorted contents
	for (int i = 0; i < size; i++) {
		printf("%ld, ", dt[ix[i]]);
		if (i > 32) {
			printf("... ");
			break;
		}
	}
	printf("\n");
	 */

	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		make_randarray(dt, size, range);
		for(index i = 0; i < size; ++i)
			ix[i] = i;
		//
		stopwatch_start(&sw);
		heapSort(dt, ix, size);
		stopwatch_stop(&sw);
		elapsed = stopwatch_clocks(&sw);
		//
		if (t == 0) {
			worst = elapsed;
			best = elapsed;
		} else {
			if (elapsed > worst) {
				worst = elapsed;
			}
			if (elapsed < best) {
				best = elapsed;
			}
		}
		sum += elapsed;
	}
	printf("Heap:    \tworst %ld clk., \tbest %ld clk., \tavr. %.1f clk.\n",
			worst, best, sum / (float)rep);

	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		make_randarray(dt, size, range);
		for(index i = 0; i < size; ++i)
			ix[i] = i;
		//
		stopwatch_start(&sw);
		insertionSort(dt, ix, size);
		stopwatch_stop(&sw);
		elapsed = stopwatch_clocks(&sw);
		// System.out.println("Heap:   \t"+ (((float)ela)/1000));
		// showing the result
		//
		if (t == 0) {
			worst = elapsed;
			best = elapsed;
		} else {
			if (elapsed > worst) {
				worst = elapsed;
			}
			if (elapsed < best) {
				best = elapsed;
			}
		}
		sum += elapsed;
	}
	printf("Insertion: \tworst %ld clk., \tbest %ld clk., \tavr. %.1f clk.\n",
			worst, best, sum / (float)rep);


	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		make_randarray(dt, size, range);
		for(index i = 0; i < size; ++i)
			ix[i] = i;
		//
		stopwatch_start(&sw);
		selectionSort(dt, ix, size);
		stopwatch_stop(&sw);
		elapsed = stopwatch_clocks(&sw);
		// System.out.println("Heap:   \t"+ (((float)ela)/1000));
		// showing the result
		//
		if (t == 0) {
			worst = elapsed;
			best = elapsed;
		} else {
			if (elapsed > worst)
				worst = elapsed;
			if (elapsed < best)
				best = elapsed;
		}
		sum += elapsed;
	}
	printf("Selection: \tworst %ld clk., \tbest %ld clk., \tavr. %.1f clk.\n",
			worst, best, sum / (float)rep);

	printf("1 clk = 1/%ld sec.\n", (long) CLOCKS_PER_SEC);

	free(dt);
	free(ix);
	return EXIT_SUCCESS;
}
