/*
 ============================================================================
 Name        : C_Hashtable.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

typedef struct {
	LinkedList * table;
	unsigned int tablesize;
} Hashtable;

typedef struct {
	LinkedList * list;
	ListNode * node;
} ListNodePair;

unsigned long hash_str(char * str) {
	unsigned long t = 0;
	unsigned int i = 0;
	for(char * p = str; *p != (char) 0 && i < 8; ++p, ++i) {
		t ^= *p;
		t <<= 6;
	}
	return t;
}

void Hashtable_new(Hashtable * h, unsigned int n) {
	h->tablesize = n;
	h->table = (void*) malloc(sizeof(LinkedList) * h->tablesize);
	for(unsigned int i = 0; i < h->tablesize; ++i) {
		LinkedList_init(&h->table[i]);
	}
}

void Hashtable_free(Hashtable * h) {
	for(unsigned int i = 0; i < h->tablesize; ++i)
		LinkedList_free(&h->table[i]);
	free(h->table);
}

ListNodePair Hashtable_find(Hashtable * h, char * str) {
	ListNodePair pair;
	unsigned long hashcode = hash_str(str);
	pair.list = & h->table[hashcode % h->tablesize];
	for(pair.node = LinkedList_begin(pair.list); pair.node != LinkedList_end(pair.list);
			pair.node = pair.node->next) {
		if ( strcmp((char*)pair.node->next->data, str) == 0 )
			break;
	}
	return pair;
}

void Hashtable_add(Hashtable * h, char * str) {
	ListNodePair pair = Hashtable_find(h, str);
	if ( pair.node->next == NULL )
		LinkedList_append(pair.list, str);
}

void Hashtable_remove(Hashtable * h, char * str) {
	ListNodePair pair = Hashtable_find(h, str);
	if ( pair.node->next != NULL )
		LinkedList_remove(pair.list, str);
}

void Hashtable_print(Hashtable * h) {
	printf("tablesize = %d\ntable = \n", h->tablesize);
	for(unsigned int i = 0; i < h->tablesize; ++i) {
		printf("%d: ", i);
		for(ListNode * p = h->table[i].head.next;
				p != NULL;
				p = p->next) {
			printf("%s (0x%lX), ", (char*) p->data, hash_str((char*)p->data));
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char * argv[]) {

	printf("the number of words = %d\n", argc-1);
	Hashtable tbl;
	Hashtable_new(&tbl, 23);
	for(unsigned int i = 1; i < argc; ++i)
		Hashtable_add(&tbl, argv[i]);

	Hashtable_print(&tbl);

	Hashtable_free(&tbl);
	printf("finished. quit.\n");
	return EXIT_SUCCESS;
}
