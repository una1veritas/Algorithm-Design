#include <stdio.h>
#include <stdlib.h>

#include "stopwatch.h"
#include "sortalgorithms.h"

int main(int argc, char * args[]) {
	long * array;
	long size = 35000;

	stopwatch sw;
	long elapsed;

	long range = 1317;
	long seed = 7;

	long rep = 1000;
	long t, r;
	long worst, best;
	double sum;

	if (argc >= 2) {
		size = atol(args[1]);
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

	setbuf(stdout, NULL);

	printf("Size: %ld, Range: [0, %ld), Initial Seed: %ld, Number of trials: %ld\n",
			size, range, seed, rep);

	array = (long *)malloc(sizeof(long)*size);

	// Merge Sort
	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		r = (rand() % range) + 2;
		for (int i = 0; i < size; i++) {
			array[i] = rand() % r;
		}

		stopwatch_start(&sw);
		mergeSort(array, size);
		stopwatch_stop(&sw);

		elapsed = stopwatch_clocks(&sw);
		if ( !verify(array, size) ) {
			printf("Merge sort has bug(s)!\n");
		}

		// showing the contents
		if (t < 1) {
			for (int i = 0; i < size; i++) {
				printf("%ld, ", array[i]);
				if (i > 15) {
					printf("... ");
					break;
				}
			}
			printf("\n");
		}

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

	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		r = (rand() % range) + 2;
		for (int i = 0; i < size; i++) {
			array[i] = rand() % r;

		}
		stopwatch_start(&sw);
		quickSort(array, size);
		stopwatch_stop(&sw);
		elapsed = stopwatch_clocks(&sw);

		// System.out.println("Quick:  \t"+ (((float)ela)/1000));
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

	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		r = (rand() % range) + 2;
		for (int i = 0; i < size; i++) {
			array[i] = rand() % r;

		}

		stopwatch_start(&sw);
		heapSort(array, size);
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
	printf("Heap:    \tworst %ld clk., \tbest %ld clk., \tavr. %.1f clk.\n",
			worst, best, sum / (float)rep);

	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		r = (rand() % range) + 2;
		for (int i = 0; i < size; i++)
			array[i] = rand() % r;

		stopwatch_start(&sw);
		insertionSort(array, size);
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
		r = (rand() % range) + 2;
		for (int i = 0; i < size; i++)
			array[i] = rand() % r;

		stopwatch_start(&sw);
		selectionSort(array, size);
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

	free(array);
	return EXIT_SUCCESS;
}
