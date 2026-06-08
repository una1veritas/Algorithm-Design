/*
 * selelection_sort.c
 * selection sort sample
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "datadef.h"


void selection_sort(data * d[], long n, lessfunc less) {
	data * t;
	for (long i = 0; i < n; ++i) {
		for (long j = i + 1; j < n; ++j) {
			if ( less(d[j], d[i]) ) {
			//if ( d[j] < d[i] ) {
				t = d[i];
				d[i] = d[j];
				d[j] = t;
			}
		}
	}
	return;
}

void selection_sort_reverse(data * d[], long n, lessfunc less) {
   data * t;
   for (long i = n - 1; i > 0; --i) {
	  int max = i;
      for (long j = 0; j < i; ++j) {
         if ( less(d[max], d[j]) )
        	 max = j;
      }
      t = d[max], d[max] = d[i], d[i] = t;
      for(long ix = 0; ix < n; ++ix) {
         fprintf_data(stdout, d[ix]);
         fprintf(stdout,", ");
      }
      printf("\n");
   }
   return;
}

/*
 * 34, 67, 8, 44,
1: 0, 0
2: 3, 0
3: 3, 0
3: 3, 1
4: 3, 1
3: 3, 2
2: 2, 0
3: 2, 0
4: 2, 0
3: 2, 1
4: 2, 1
2: 1, 0
3: 1, 0
8, 34, 44, 67,
 *
 *
 *
34, 8, 44, 67,
1: 0, 0
2: 3, 0
3: 3, 0
3: 3, 1
3: 3, 2
2: 2, 0
3: 2, 0
3: 2, 1
2: 1, 0
3: 1, 0
4: 1, 0
8, 34, 44, 67,
 */
