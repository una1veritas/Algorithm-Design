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
	data * elem;
	unsigned int length;
} dataseq;

#define lt_or_eqs(x, y)  ((x) <= (y) ? 1 : 0)

/* passage counters */
long passcount[] = { 0, 0, };

void down_to_leaf(data a[], unsigned int i, unsigned int n) {
	unsigned int j;
	data t;
	while ( 1 ) {
		j = (i<<1) + 1; // the left child
		if (! (j < n) )
			break;
		//printf("%d, ", j);
		if ( j+1 < n ) { // i has the right child
			if ( lt_or_eqs(a[j], a[j+1]) )
				j += 1; // select the right child
		}
		if ( lt_or_eqs(a[j], a[i]) )
			break;
		t = a[i]; a[i] = a[j]; a[j] = t;
		i = j;
	}
	//printf("\n");
}

void make_heap(data a[], unsigned int n) {
	for(unsigned int i = (n-1)>>1; i > 0; --i)
		down_to_leaf(a, i-1, n);
}

void heapSort(data a[], unsigned int n) {
	unsigned int i;
	data t;
	make_heap(a, n);
	for(unsigned int i = 0; i < n; ++i) {
		printf("%d, ", a[i]);
	}
	printf("\n");
	printf("\n");
	for(i = n; i > 0; --i) {
		t = a[i-1]; a[i-1] = a[0]; a[0] = t;
		down_to_leaf(a, 0, i - 1);
		for(unsigned int j = 0; j < n; ++j) {
			printf("%d, ", a[j]);
		}
		printf("\n");
	}
}

void insertionSort(data a[], unsigned int n){
	unsigned int i, j;
	data t;
	for(;;) {
		for (i = 0; i < n - 1; ++i) {	++passcount[0];
			if ( ! lt_or_eqs(a[i], a[i+1]) ) {
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

dataseq input_array(int argc, char * argv[]) {
	dataseq a;
	unsigned int length = argc-1, i;
	if (length == 1) {
		length = atoi(argv[1]);
	}
	a.elem = (data *) malloc(sizeof(data) * length);
	if ( length >= argc ) {
		srand((unsigned) 20190527 ); //time(NULL));
	    for(i = 0; i < length; ++i)
			a.elem[i] = rand() % (length<<1) + 1;
	} else {
		for(i = 0; i < length; ++i)
			a.elem[i] = atoi(argv[1+i]);
	}
	a.length = length;
	return a;
}

int main(int argc, char * argv[]) {
	dataseq a = input_array(argc, argv);
	unsigned int i;
	for(i = 0; i < a.length; ++i) {
		printf("%d, ", a.elem[i]);
	}
	printf("\n%d data.\n", a.length);

	heapSort(a.elem, a.length);
	//insertionSort(a.elem, a.length);

	for(i = 0; i < a.length; ++i) {
		printf("%d, ", a.elem[i]);
	}
	printf("\n");

	printf("passing counter [0] = %ld, [1] = %ld\n", passcount[0], passcount[1]);

	free(a.elem);
	return 0;
}
