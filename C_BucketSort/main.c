/*
 ============================================================================
 Name        : BucketSort.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

#define max(a, b)  ((a) < (b) ? (a) : (b))


void clearBuckets(LinkedList b[], unsigned int range_size) {
	for(unsigned int i = 0; i < range_size; ++i)
		LinkedList_init(&b[i]);
}

void appendToBuckets(LinkedList b[], unsigned int key) {
	LinkedList_append(&b[key], (void*) key);
}

LinkedList * collectFromBuckets(LinkedList b[], unsigned int range_size, LinkedList * result) {
	for(unsigned int k = 0; k < range_size; ++k) {
		for(ListNode * p = LinkedList_begin(&b[k]); p != NULL; p = p->next ) {
			LinkedList_append(result, p->data);
		}
	}
	return result;
}

void freeBuckets(LinkedList b[], unsigned int range_size) {
	for(unsigned int i = 0; i < range_size; ++i)
		LinkedList_free(&b[i]);
}


int main(int argc, char * argv[]) {
	if ( argc == 1 ) {
		printf("No inputs.\n");
		return EXIT_FAILURE;
	}

	// setup input a[]
	unsigned int range = 24;
	unsigned int capacity = argc - 1;  /* 最大 */
	unsigned int a[capacity];
	for(int i = 0; i < capacity; i++) {
		a[i] = (unsigned int) atoi(argv[1+i]);
		printf("%d, ", a[i]);
	}
	printf("\n\n");

	// do sort by bucket sort
	LinkedList buckets[range];
	clearBuckets(buckets, range);
	for(int i = 0; i < capacity; i++)
		appendToBuckets(buckets, a[i]);

	for(int i = 0; i < range; ++i) {
		printf("%d: [ ", i);
		for(ListNode * ptr = LinkedList_begin(&buckets[i]); ptr != NULL; ptr = ptr->next) {
			printf("%d, ", (unsigned int) ptr->data );
		}
		printf("]\n");
	}
	printf("\n");

	LinkedList result;
	LinkedList_init(&result);
	collectFromBuckets(buckets, range, &result);
	for(ListNode * ptr = LinkedList_begin(&result); ptr != NULL; ptr = ptr->next) {
		printf("%d, ", (unsigned int) ptr->data );
	}
	printf("\n");
	printf("List size = %d\n", LinkedList_count(&result) );

	freeBuckets(buckets, range);
	LinkedList_free(&result);
	return EXIT_SUCCESS;
}



