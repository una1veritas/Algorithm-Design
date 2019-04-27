/*
 * main.c
 *
 *  Created on: 2019/04/18
 *      Author: Sin Shimozono
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "mt.h"

typedef int data;
typedef struct {
	data * array;
	unsigned int length;
} array;

#define lessthan_or_equals(x, y)  ((x) <= (y) ? 1 : 0)

/* passage counters */
long passcount[] = { 0, 0, };

void insertionSort(data a[], unsigned int n){
	unsigned int i, j;
	data t;
	for(;;) {
		for (i = 0; i < n - 1; ++i) {	++passcount[0];
			if ( ! lessthan_or_equals(a[i], a[i+1]) ) {
				t = a[i+1];
				j = i + 1;
				do { 	++passcount[1];
					a[j] = a[j-1];
					--j;
				} while ( j > 0 && a[j-1] > t);
				a[j] = t;
				break;
			}
		}
		if ( i == n - 1 )
			break;
	}
	return;
}

array prepare_array(int argc, char * argv[]) {
	array a;
	unsigned int length = argc-1, i;
	if (length == 1) {
		length = atoi(argv[1]);
	}
	a.array = (data *) malloc(sizeof(data) * length);
	if ( length >= argc ) {
		srand((unsigned)time(NULL));
	    for(i = 0; i < length; ++i)
			a.array[i] = rand() % (length<<1) + 1;
	} else {
		for(i = 0; i < length; ++i)
			a.array[i] = atoi(argv[1+i]);
	}
	a.length = length;
	return a;
}

int main(int argc, char * argv[]) {
	array a = prepare_array(argc, argv);
	unsigned int i;
	for(i = 0; i < a.length; ++i) {
		printf("%d, ", a.array[i]);
	}
	printf("\n%d data.\n", a.length);

	insertionSort(a.array, a.length);

	for(i = 0; i < a.length; ++i) {
		printf("%d, ", a.array[i]);
	}
	printf("\n");

	printf("passing counter [0] = %ld, [1] = %ld\n", passcount[0], passcount[1]);

	free(a.array);
	return 0;
}
