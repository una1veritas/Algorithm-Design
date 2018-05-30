/*
 ============================================================================
 Name        : TestCode.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Collection {
	int data[32];
	int n;
} ArraySet;

void printCollection(ArraySet * set) {
	for(int i = 0; i < set->n; ++i) {
		printf("%d ",set->data[i]);
	}
	printf("\n");
}

void insertCollection(ArraySet * set, int d) {
	int pos;
	for(pos = 0; pos < set->n; ++pos) {
		if ( d < set->data[pos] )
			break;
	}
	for(int dst = set->n; dst > pos; --dst) {
		set->data[dst] = set->data[dst-1];
	}
	set->data[pos] = d;
	++set->n;
}

int findCollection(ArraySet * set, int d) {
	int rbegin = 0, rend = set->n;
	int mid;
	while ( rbegin != rend ) {
		mid = (rbegin+rend)/2;
		if ( set->data[mid] == d) {
			return mid;
		} else if ( set->data[mid] < d) {
			rbegin = mid + 1;
		} else {
			rend = mid;
		}
	}
	return -1;
}

int main(void) {

	ArraySet set;

	set.n = 0;

	printf("begin.\n");
	printCollection(&set);
	printf("insert.\n");

	int d[] = { 3, 2, 11, 8, 21, 11, 15, 7, 22, 21, 1, 2, };
	for(int i = 0; i < sizeof(d)/sizeof(*d); ++i ) {
		insertCollection(&set, d[i]);
	}
	printCollection(&set);
	int pos = findCollection(&set, 23);

	printf("result = %d\n", pos);

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}
