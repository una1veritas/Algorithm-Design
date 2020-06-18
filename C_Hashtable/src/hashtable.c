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

#include "datadef.h"
#include "llist.h"

long keycode(const data d) {
	long t = 0;
//	char c = 0;
	for(const char * p = (const char *) d->id; *p != (char) 0 ; ++p) {
		t = (t << 5) - t;
		t ^= *p;
	}
	printf("%ld, ", t);
	return t;
}

int equals(const data d1, const data d2) {
	return 0 == strcmp((const char *) d1->id, (const char *) d2->id);
}

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

ListNodePair Hashtable_findList(Hashtable * h, const data d) {
	long hashcode = keycode(d) % h->tablesize;
	ListNodePair pair;
	pair.listptr = & h->table[hashcode];
	pair.nodeptr = LList_find(pair.listptr, d, equals);
	return pair;
}

ListNode * Hashtable_find(Hashtable * h, const data d) {
	ListNodePair pair = Hashtable_findList(h, d);
	return pair.nodeptr;
}

void Hashtable_add(Hashtable * h, const data d) {
	ListNodePair pair = Hashtable_findList(h, d);
	if ( pair.nodeptr == LList_end(pair.listptr) ) {
		LList_append(pair.listptr, d);
		h->elemcount += 1;
	}
}

void Hashtable_remove(Hashtable * h, const data d) {
	ListNodePair pair = Hashtable_findList(h, d);
	if ( pair.nodeptr != LList_end(pair.listptr) ) {
		LList_remove(pair.listptr, d, equals);
		h->elemcount -= 1;
	}
}

void Hashtable_fprintf(FILE * f, Hashtable * h, const char * fmt) {
	printf("tablesize = %ld\ntable = \n", h->tablesize);
	for(long i = 0; i < h->tablesize; ++i) {
		printf("%ld: ", i);
		LList_fprintf(f, &h->table[i], fmt);
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char * argv[]) {
	Hashtable tbl;
	long tblsize = argc;
	idname * d = (idname *) malloc(sizeof(idname));
	long n = 0;
	for(long i = 0; 1+2*i < argc; ++i) {
		strncpy(d[i].id, argv[1+2*i], 8);
		strncpy(d[i].name, argv[1+2*i + 1], 8);
		n += 1;
	}
	tblsize = (tblsize < 211 ? 211 : tblsize );

	Hashtable_init(&tbl, tblsize);
	for(long i = 0; i < n; ++i)
		Hashtable_add(&tbl, &d[i]);

	printf("the number of words = %ld\n", tbl.elemcount);
	//Hashtable_fprintf(stdout, &tbl, "%s, ");

	Hashtable_free(&tbl);
	printf("finished. quit.\n");
	return EXIT_SUCCESS;
}
