/*
 * Hashtable_OpenAdress.c
 *
 *  Created on: 2025/05/27
 *      Author: sin
 */

#include <stdio.h>

#include "OAHashtable.h"

OAHashtable * allocate_OAHashtable(unsigned int size) {
	OAHashtable * h;
	h = (OAHashtable *) malloc(sizeof(OAHashtable));
	h->tablesize = size;
	h->table = (datatype **) malloc(sizeof(datatype *) * h->tablesize);
	for(long i = 0; i < h->tablesize; ++i) {
		h->table[i] = NULL;
	}
	h->elemcount = 0;
	return h;
}

void free_OAHashtable(OAHashtable * h) {
	free(h->table);
	free(h);
}

unsigned int OAHashtable_find_or_NULL(OAHashtable * htbl, datatype * obj) {
	unsigned int start_ix = hash_code(obj) % htbl->tablesize;
	unsigned int i;
	for(i = 0; i < htbl->tablesize; ++i) {
		if ( htbl->table[(start_ix + i) % htbl->tablesize] == NULL )
			return start_ix;
		if ( equals(htbl->table[(start_ix + i) % htbl->tablesize], obj) )
			return start_ix + i;
	}
	return i;
}

int OAHashtable_add(OAHashtable * htbl, datatype * obj) {
	unsigned int find_ix = OAHashtable_find_or_NULL(htbl, obj);
	if ( find_ix == htbl->tablesize ) {
		fprintf(stderr, "Error: Hashtable is full!!\n");
		return -1;
	}
	if ( htbl->table[find_ix] == NULL ) {
		htbl->table[find_ix] = obj;
	}
	return find_ix;
}

int OAHashtable_fprintf(FILE * fp, OAHashtable * htbl, const char * fmt) {
	int sum = 0;
	char buf[256];
	for(int i = 0; i < htbl->tablesize; ++i) {
		if ( htbl->table[i] != NULL ) {
			sprint(buf, htbl->table[i]);
			sum += fprintf(fp, fmt, buf);
		}
	}
	return sum;
}
