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

typedef struct OpenHashtable {
	LList * table;
	long tablesize, elemcount;
} OpenHashtable;

typedef struct ListNodePair {
	LList * listptr;
	ListNode * nodeptr;
} ListNodePair;

void OpenHashtable_init(OpenHashtable * h, long n) {
	h->tablesize = n;
	h->table = (void*) malloc(sizeof(LList) * h->tablesize);
	for(long i = 0; i < h->tablesize; ++i) {
		LList_init(&h->table[i]);
	}
	h->elemcount = 0;
}

void OpenHashtable_free(OpenHashtable * h) {
	for(long i = 0; i < h->tablesize; ++i)
		LList_free(&h->table[i]);
	free(h->table);
}

ListNodePair OpenHashtable_findList(OpenHashtable * h, const datatype * d) {
	long hash = hash_code(d) % h->tablesize;
	ListNodePair pair;
	pair.listptr = & h->table[hash];
	pair.nodeptr = LList_find(pair.listptr, d, equals);
	return pair;
}

ListNode * OpenHashtable_find(OpenHashtable * h, const datatype * d) {
	ListNodePair pair = OpenHashtable_findList(h, d);
	return pair.nodeptr;
}

void OpenHashtable_add(OpenHashtable * h, const datatype * d) {
	ListNodePair pair = OpenHashtable_findList(h, d);
	if ( pair.nodeptr == LList_end(pair.listptr) ) {
		LList_append(pair.listptr, d);
		h->elemcount += 1;
	}
}

void OpenHashtable_remove(OpenHashtable * h, const datatype * d) {
	ListNodePair pair = OpenHashtable_findList(h, d);
	if ( pair.nodeptr != LList_end(pair.listptr) ) {
		LList_remove(pair.listptr, d, equals);
		h->elemcount -= 1;
	}
}

void OpenHashtable_fprintf(FILE * f, OpenHashtable * h, const char * fmt) {
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
		fprintf(f, "\n");
	}
	fprintf(f,"\n");
}

typedef struct ClosedHashtable {
	datatype ** table;
	long tablesize, elemcount;
} ClosedHashtable;

void ClosedHashtable_init(ClosedHashtable * h, long n) {
	h->tablesize = n;
	h->table = (datatype **) malloc(sizeof(datatype *) * h->tablesize);
	for(long i = 0; i < h->tablesize; ++i) {
		h->table[i] = NULL;
	}
	h->elemcount = 0;
}

int main(const int argc, const char * argv[]) {
	OpenHashtable tbl;
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
	OpenHashtable_init(&tbl, tblsize);
	for(long i = 0; i < n; ++i)
		OpenHashtable_add(&tbl, &d[i]);

	printf("the number of entries = %ld\n", tbl.elemcount);
	OpenHashtable_fprintf(stdout, &tbl, "%s, ");

	OpenHashtable_free(&tbl);
	printf("finished. quit.\n");
	return EXIT_SUCCESS;
}

/*
 *
Hash table size = 7
the number of entries = 6
tablesize = 7
table =
0: (333C1193: Jouji Shou) 3468268706,
1: (332C1105: Tate Chabashira) 3458912892,
2: (333C2307: Takamine Yamada) 3468240106, (332C1088: Kouki Han) 3458912368,
3:
4: (333C1089: Takashi Nami) 3468267590,
5:
6: (333C1306: Batuta Shouryou) 3468266934,

finished. quit.
 */
