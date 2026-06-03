/*
 * heapchecker.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datadef.h"
#include "sort_algorithms.h"

void shell_sort(data * a[], long n, int (* less)(const void *, const void *)) {
    // Start with a large gap, then reduce it step by step
    for (long gap = n>>1; gap > 0; gap >>= 1) {
        fprintf(stdout, "gap = %ld\n", gap);

        // Perform a "gapped" swap, from shortest length-1 chain to longer ones
        for (long i = gap; i < n; i++) {
            fprintf(stdout, "i = %ld\n", i);
            for(int i = 0; i < n; ++i) {
            	fprintf_data(stdout, a[i]);
            }
            fprintf(stdout, "\n");

            // Current element to be placed correctly
            data * tmp = a[i];

            // j - gap < j
            // Shift elements that are greater than temp to make space
            long j;
            for (j = i; j >= gap && less(tmp, a[j - gap]); j -= gap ) {
                a[j] = a[j - gap];
            }
            a[j] = tmp;

            for(int i = 0; i < n; ++i) {
            	fprintf_data(stdout, a[i]);
            }
            fprintf(stdout, "\n\n");
        }
    }
}
