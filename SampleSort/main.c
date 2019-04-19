/*
 * main.c
 *
 *  Created on: 2019/04/18
 *      Author: Sin Shimozono
 */

#include <stdio.h>
#include <stdlib.h>

typedef int data;

/* passage counters */
long passcount[] = { 0, 0, };

void insertionSort(data a[], unsigned int n){
	unsigned int i = 0, j;
	data t;
	while (i < n - 1) {
		++passcount[0];
		if ( !(a[i] < a[i+1]) ) {
			t = a[i+1];
			j = i + 1;
			do {
				a[j] = a[j-1];
				--j;
				++passcount[1];
			} while ( j > 0 && a[j-1] > t);
			a[j] = t;
		}
		++i;
	}
	return;
}

int main(int argc, char * argv[]) {
	unsigned int length = argc-1, i;
	data array[length];
	for(i = 0; i < length; ++i) {
		array[i] = atoi(argv[1+i]);
		printf("%d, ", array[i]);
	}
	printf("\n");

	insertionSort(array, length);

	for(i = 0; i < length; ++i) {
		printf("%d, ", array[i]);
	}
	printf("\n");

	printf("The number of passing counter [0] = %ld, [1] = %ld\n", passcount[0], passcount[1]);
	return 0;
}
