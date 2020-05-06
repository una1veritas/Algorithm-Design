#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stopwatch.h"
#include "sortalgorithms.h"

int data_greaterThan(const data * a, const data * b) {
	return *a > *b;
}

data * darray;
int q_gt(const void *c1, const void *c2){
	return darray[*(int*)c1] - darray[*(int*)c2];
}

void make_random_array(data array[], unsigned int nsize, unsigned int range) {
	unsigned long r;
	r =  (rand() % range) + 2;
	for (int i = 0; i < nsize; i++) {
		array[i] = NULL + (rand() % r);
	}
}

int getargs(const int argc, const char * argv[], unsigned int *nsize, unsigned int *range, unsigned int *rep, unsigned int *seed);

int main(const int argc, const char * argv[]) {
	data * dt;
	unsigned int * ix;

	stopwatch sw;
	long elapsed;
	unsigned int nsize = 1000, range = 1317, rep = 1000;
	unsigned int seed = (unsigned int) time(NULL);
	long t, worst, best;
	long sum;

	getargs(argc, argv, &nsize, &range, &rep, &seed);

	printf("Size: %u, Range within: 0 -- %u, Initial Seed: %u, Number of trials: %u\n",
			nsize, range, seed, rep);

	dt = (data *)malloc(sizeof(data)*nsize);
	ix = (unsigned int *)malloc(sizeof(unsigned int)*nsize);

	printf("algorithm \tworst \tbest \tavr\n");
	// Merge Sort
	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		make_random_array(dt, nsize, range);
		for(unsigned int i = 0; i < nsize; ++i)
			ix[i] = i;
		//
		stopwatch_start(&sw);
		mergeSort(dt, ix, nsize);
		stopwatch_stop(&sw);

		elapsed = stopwatch_clocks(&sw);
		//printf("Merge:      \t %ld\n",elapsed);
		if (t == 0) {
			worst = elapsed;
			best = elapsed;
			if ( !verify_sorted(dt, ix, nsize) ) {
				printf("error: sort failure!\n");
			}
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
	printf("Merge:    \t%ld\t%ld\t%.1f\n", worst, best, sum / (float)rep);

#ifdef SHOW_SORTED
	// showing the last sorted contents
	printf("\n");
	for (int i = 0; i < nsize; i++) {
		printf("%u ", ix[i]);
		if (i > 32) {
			printf("... ");
			break;
		}
	}
	printf("\n--------\n");
	for (int i = 0; i < nsize; i++) {
		printf("%lu ", (unsigned long) (0xffffffffLL & (unsigned long long) dt[ix[i]]) );
		if (i > 32) {
			printf("... ");
			break;
		}
	}
	printf("\n\n");
#endif

	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		make_random_array(dt, nsize, range);
		for(unsigned int i = 0; i < nsize; ++i)
			ix[i] = i;
		//
		darray = dt;
		stopwatch_start(&sw);
		qsort(ix, nsize, sizeof(unsigned int), q_gt);
		//quickSort(dt, ix, nsize);
		stopwatch_stop(&sw);
		elapsed = stopwatch_clocks(&sw);
		// showing the contents
		//
		if (t == 0) {
			worst = elapsed;
			best = elapsed;
			if ( !verify_sorted(dt, ix, nsize) ) {
				printf("error: sort failure!\n");
			}
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
	printf("qsort:    \t%ld \t%ld \t%.1f\n", worst, best, sum / (float)rep);
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
		make_random_array(dt, nsize, range);
		for(unsigned int i = 0; i < nsize; ++i)
			ix[i] = i;
		//
		stopwatch_start(&sw);
		heapSort(dt, ix, nsize);
		stopwatch_stop(&sw);
		elapsed = stopwatch_clocks(&sw);
		//
		//
		if (t == 0) {
			worst = elapsed;
			best = elapsed;
			if ( !verify_sorted(dt, ix, nsize) ) {
				printf("error: sort failure!\n");
			}
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
	printf("Heap:    \t%ld\t%ld\t%.1f\n", worst, best, sum / (float)rep);
/*
	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		make_random_array(dt, nsize, range);
		for(unsigned int i = 0; i < nsize; ++i)
			ix[i] = i;
		//
		stopwatch_start(&sw);
		insertionSort(dt, ix, nsize);
		stopwatch_stop(&sw);
		elapsed = stopwatch_clocks(&sw);
		// System.out.println("Heap:   \t"+ (((float)ela)/1000));
		// showing the result
		if ( !verify_sorted(dt, ix, nsize) ) {
			printf("error: sort failure!\n");
		}
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
*/

	srand(seed);
	for (worst = 0, best = 0, sum = 0, t = 0; t < rep; t++) {
		make_random_array(dt, nsize, range);
		for(unsigned int i = 0; i < nsize; ++i)
			ix[i] = i;
		//
		stopwatch_start(&sw);
		selectionSort(dt, ix, nsize);
		stopwatch_stop(&sw);
		elapsed = stopwatch_clocks(&sw);
		// System.out.println("Heap:   \t"+ (((float)ela)/1000));
		// showing the result
		//
		if (t == 0) {
			worst = elapsed;
			best = elapsed;
			if ( !verify_sorted(dt, ix, nsize) ) {
				printf("error: sort failure!\n");
			}
		} else {
			if (elapsed > worst)
				worst = elapsed;
			if (elapsed < best)
				best = elapsed;
		}
		sum += elapsed;
	}
	printf("Selection: \t%ld \t%ld \t%.1f\n", worst, best, sum / (float)rep);

	printf("1 clk = 1/%ld sec.\n", (long) CLOCKS_PER_SEC);

	free(dt);
	free(ix);
	return EXIT_SUCCESS;
}


int getargs(const int argc, const char * argv[], unsigned int *nsize, unsigned int *range, unsigned int *rep, unsigned int *seed) {
	const char * ptr;
	for(int i = 1; i < argc; ++i) {
		ptr = argv[i];
		if ( *ptr == '-' ) {
			++ptr;
			switch(*ptr) {
			case 'n':
				*nsize = strtol(++ptr, NULL, 10);
				break;
			case 'i':
				*rep = strtol(++ptr, NULL, 10);
				break;
			case 's':
				*seed = strtol(++ptr, NULL, 10);
				break;
			case 'r':
				*range = strtol(++ptr, NULL, 10);
				break;
			}
		} else {
			switch(i) {
			case 1:
				*nsize = strtol(ptr, NULL, 10);
				break;
			case 2:
				*range = strtol(ptr, NULL, 10);
				break;
			case 3:
				*seed = strtol(ptr, NULL, 10);
				break;
			case 4:
				*rep = strtol(ptr, NULL, 10);
				break;
			}
		}
	}
	return 0;
}
