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

        // Perform a "gapped" insertion sort for this gap size
        for (long i = gap; i < n; i++) {

            // Current element to be placed correctly
            data * ptr = a[i];
            long j = i;

            // Shift elements that are greater than temp to make space
            while (j >= gap && less(ptr, a[j - gap]) ) {
                a[j] = a[j - gap];
                j -= gap;
            }
            // Place temp in its correct location
            a[j] = ptr;
        }
    }
}
