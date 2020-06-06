/*
 ============================================================================
 Name        : Hashtable.c
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
	LList * table;
	unsigned int tablesize;
	unsigned int elemcount;
} Hashtable;

typedef struct {
	LList * list;
	ListNode * node;
} LNPair;

unsigned long hash_str(char * str) {
	unsigned long t = 0;
	unsigned int i = 0;
	for(char * p = str; *p != (char) 0 && i < 8; ++p, ++i) {
		t ^= *p;
		t <<= 5;
	}
	return t;
}

void Hashtable_allocate(Hashtable * h, unsigned int n) {
	h->tablesize = n;
	h->table = (void*) malloc(sizeof(LList) * h->tablesize);
	for(unsigned int i = 0; i < h->tablesize; ++i) {
		LinkedList_init(&h->table[i]);
	}
	h->elemcount = 0;
}

void Hashtable_free(Hashtable * h) {
	for(unsigned int i = 0; i < h->tablesize; ++i)
		LinkedList_free(&h->table[i]);
	free(h->table);
}

LNPair Hashtable_find(Hashtable * h, char * str) {
	LNPair pair;
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
	LNPair pair = Hashtable_find(h, str);
	if ( pair.node->next == NULL ) {
		LinkedList_append(pair.list, str);
		h->elemcount += 1;
	}
}

void Hashtable_remove(Hashtable * h, char * str) {
	unsigned long hashcode = hash_str(str);
	LList * list = & h->table[hashcode % h->tablesize];
	if ( LinkedList_remove(list, str) != NULL )
		h->elemcount -= 1;
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
	Hashtable tbl;
	unsigned int tblsize = atoi(argv[1]);
	tblsize = (tblsize < 11 ? 11 : tblsize );

	Hashtable_allocate(&tbl, tblsize);
	for(unsigned int i = 2; i < argc; ++i)
		Hashtable_add(&tbl, argv[i]);

	printf("the number of words = %d\n", tbl.elemcount);
	Hashtable_print(&tbl);

	Hashtable_free(&tbl);
	printf("finished. quit.\n");
	return EXIT_SUCCESS;
}
