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

typedef int datatype;
struct Element {
	datatype data;
	struct Element * next;
};
typedef struct Element Element;

void clearBuckets(Element ** buckets, int keySize) {
	for(int i = 0; i < keySize; i++)
		buckets[i] = NULL;
}

void addToBuckets(Element ** buckets, datatype d) {
	Element * p = (Element *) malloc(sizeof(Element));
	p->data = d;
	p->next = NULL;

	if ( buckets[d] == NULL) {
		buckets[d] = p;
	} else {
		p->next = buckets[d];
		buckets[d] = p;
	}
}

void purgeBuckets(Element ** buckets, int keySize) {
	for(int i = 0; i < keySize; i++) {
		if ( buckets[i] == NULL)
			continue;
		Element * p = buckets[i];
		printf("[%d] ", i, (long) p);
		while ( p != NULL ) {
			printf("%d, ", p->data);
			Element * nextp = p->next;
			free(p);
			p = nextp;
		}
	}
}
int main(int argc, char * argv[]) {
	if ( argc == 1 )
		return EXIT_FAILURE;

	int capacity = argc - 1;  /* 最大 */
	Element * Buckets[100]; /* キーは 0 から 99 まで */

	clearBuckets(Buckets, 100);
	for(int i = 0; i < capacity; i++) {
		int val = atoi(argv[1+i]);
		addToBuckets(Buckets, val);
	}
	purgeBuckets(Buckets, 100);
	return EXIT_SUCCESS;
}



