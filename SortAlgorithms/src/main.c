#include <stdio.h>

#include "stopwatch.h"
#include "sortalgorithms.h"

int main(int argc, char * args[]) {
	int * array;
	int size = 10;

	stopwatch sw;
	long elapsed;

	int range = 101;
	long seed = 113;

	int rep = 1;
	int t, r;
	long worst, best;
	long long sum;

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

	printf("Size: %d, Range within: 0 -- %d, Initial Seed: %ld, Number of trials: %ld\n",
			size, range, seed, rep);

	array = (int *)malloc(sizeof(int)*size);

	// Merge Sort
	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		r = (random() % range) + 2;
		for (int i = 0; i < size; i++)
			array[i] = random() % r;
		// showing the contents
		if (t < 1) {
			for (int i = 0; i < size; i++) {
				printf("%d, ", array[i]);
				if (i > 15) {
					printf("... ");
					break;
				}
			}
			printf("\n");
		}
		//
		stopwatch_start(&sw);
		mergeSort(array, size);
		stopwatch_stop(&sw);

		elapsed = stopwatch_micros(&sw)+1000*stopwatch_millis(&sw);
		//printf("Merge:   \t %ld\n",elapsed);

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
	printf("Merge: \tworst %ld u sec., \tbest %ld u sec., \tavr. %ld u sec.",
			worst, best, sum / rep);

	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		r = random() % range + 2;
		for (int i = 0; i < size; i++) {
			array[i] = random() % r;

		}
		stopwatch_start(&sw);
		quickSort(array, size);
		stopwatch_stop(&sw);
		elapsed = stopwatch_micros(&sw)+1000*stopwatch_millis(&sw);

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
	printf("Quick: \tworst %ld u sec., \tbest %ld u sec., \tavr. %ld u sec.",
			worst, best, sum / rep);

	/*
	rnd.setSeed(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		r = rnd.nextInt(range) + 2;
		for (int i = 0; i < size; i++) {
			array[i] = rnd.nextInt(r);

		}

		ela = System.currentTimeMillis();
		SortingAlgorithms.heapSort(array);
		ela = System.currentTimeMillis() - ela;
		// System.out.println("Heap:   \t"+ (((float)ela)/1000));
		// showing the result

		//
		if (t == 0) {
			worst = ela;
			best = ela;
		} else {
			if (ela > worst) {
				worst = ela;
			}
			if (ela < best) {
				best = ela;
			}
		}
		sum += ela;
	}
	System.out.println(
			"Heap: \tworst " + ((float) worst) / 1000 + " sec., \tbest "
					+ ((float) best) / 1000 + " sec., \tavr. "
					+ ((int) ((float) sum) / rep) / (float) 1000 + " sec.");

	rnd.setSeed(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		r = rnd.nextInt(range) + 2;
		for (int i = 0; i < size; i++)
			array[i] = rnd.nextInt(r);

		ela = System.currentTimeMillis();
		SortingAlgorithms.insertionSort(array);
		ela = System.currentTimeMillis() - ela;
		// System.out.println("Heap:   \t"+ (((float)ela)/1000));
		// showing the result
		//
		if (t == 0) {
			worst = ela;
			best = ela;
		} else {
			if (ela > worst) {
				worst = ela;
			}
			if (ela < best) {
				best = ela;
			}
		}
		sum += ela;
	}
	System.out.println(
			"Insertion: \tworst " + ((float) worst) / 1000 + " sec., \tbest "
					+ ((float) best) / 1000 + " sec., \tavr. "
					+ ((int) ((float) sum) / rep) / (float) 1000 + " sec.");

	rnd.setSeed(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		r = rnd.nextInt(range) + 2;
		for (int i = 0; i < size; i++)
			array[i] = rnd.nextInt(r);

		ela = System.currentTimeMillis();
		SortingAlgorithms.selectionSort(array);
		ela = System.currentTimeMillis() - ela;
		// System.out.println("Heap:   \t"+ (((float)ela)/1000));
		// showing the result
		//
		if (t == 0) {
			worst = ela;
			best = ela;
		} else {
			if (ela > worst)
				worst = ela;
			if (ela < best)
				best = ela;
		}
		sum += ela;
	}
	System.out.println(
			"Selection: \tworst " + ((float) worst) / 1000 + " sec., \tbest "
					+ ((float) best) / 1000 + " sec., \tavr. "
					+ ((int) ((float) sum) / rep) / (float) 1000 + " sec.");

	//System.out.println((new BufferedReader(new InputStreamReader(System.in))).readLine()+": Ok?");
*/
	free(array);
	return EXIT_SUCCESS;
}
