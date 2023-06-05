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

#include "datatype.h"

#include "llist.h"

typedef struct Hashtable {
	LList * table;
	long tablesize, elemcount;
} Hashtable;

typedef struct ListNodePair {
	LList * listptr;
	ListNode * nodeptr;
} ListNodePair;

void Hashtable_init(Hashtable * h, long n) {
	h->tablesize = n;
	h->table = (void*) malloc(sizeof(LList) * h->tablesize);
	for(long i = 0; i < h->tablesize; ++i) {
		LList_init(&h->table[i]);
	}
	h->elemcount = 0;
}

void Hashtable_free(Hashtable * h) {
	for(long i = 0; i < h->tablesize; ++i)
		LList_free(&h->table[i]);
	free(h->table);
}

ListNodePair Hashtable_findList(Hashtable * h, const datatype * d) {
	long hash = hash_code(d) % h->tablesize;
	ListNodePair pair;
	pair.listptr = & h->table[hash];
	pair.nodeptr = LList_find(pair.listptr, d, equals);
	return pair;
}

ListNode * Hashtable_find(Hashtable * h, const datatype * d) {
	ListNodePair pair = Hashtable_findList(h, d);
	return pair.nodeptr;
}

void Hashtable_add(Hashtable * h, const datatype * d) {
	ListNodePair pair = Hashtable_findList(h, d);
	if ( pair.nodeptr == LList_end(pair.listptr) ) {
		LList_append(pair.listptr, d);
		h->elemcount += 1;
	}
}

void Hashtable_remove(Hashtable * h, const datatype * d) {
	ListNodePair pair = Hashtable_findList(h, d);
	if ( pair.nodeptr != LList_end(pair.listptr) ) {
		LList_remove(pair.listptr, d, equals);
		h->elemcount -= 1;
	}
}

void Hashtable_fprintf(FILE * f, Hashtable * h, const char * fmt) {
	char buf[256];
	printf("tablesize = %ld\ntable = \n", h->tablesize);
	for(long i = 0; i < h->tablesize; ++i) {
		printf("%ld: ", i);
		//LList_fprintf(f, &h->table[i], fmt);
		LList * list = &h->table[i];
		for(ListNode * node = LList_begin(list);
				node != LList_end(list);
				node = node->next) {
			sprint(buf, & node->data);
			fprintf(f,"%s, ", buf);
		}
		fprintf(f,"\n");
	}
	fprintf(f,"\n");
}

int main(const int argc, const char * argv[]) {
	Hashtable tbl;
	long tblsize = atol(argv[1]);
	const char ** arg = &argv[2];
	long n = (argc - 2)>>1;
	datatype d[n];
	for(int i = 0; i < n; ++i) {
		strncpy(d[i].id, arg[i*2], 8);
		strncpy(d[i].name, arg[i*2+1], 32);
		d[i].name[31] = 0;
	}
	printf("Hash table size = %ld\n", tblsize);
	Hashtable_init(&tbl, tblsize);
	for(long i = 0; i < n; ++i)
		Hashtable_add(&tbl, &d[i]);

	printf("the number of entries = %ld\n", tbl.elemcount);
	Hashtable_fprintf(stdout, &tbl, "%s, ");

	Hashtable_free(&tbl);
	printf("finished. quit.\n");
	return EXIT_SUCCESS;
}
