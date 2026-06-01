/*
 * Hashtable_OpenAdress.c
 *
 *  Created on: 2025/05/27
 *      Author: sin
 */

#include <stdio.h>

#include "OAHashtable.h"

OAHashtable * OAHashtable_allocate(unsigned int size) {
	OAHashtable * h;
	h = (OAHashtable *) malloc(sizeof(OAHashtable));
	h->tablesize = size;
	h->table = (datatype **) malloc(sizeof(datatype *) * h->tablesize);
	for(long i = 0; i < h->tablesize; ++i) {
		h->table[i] = NULL;
	}
	h->count = 0;
	return h;
}

void OAHashtable_free(OAHashtable * h) {
	free(h->table);
	free(h);
}

unsigned int OAHashtable_find_or_NULL(OAHashtable * htbl, datatype * ptr) {
	unsigned int start_ix = hash_code(ptr) % htbl->tablesize;
	unsigned int i;
	for(i = 0; i < htbl->tablesize; ++i) {
		if ( htbl->table[(start_ix + i) % htbl->tablesize] == NULL ) {
			//fprintf(stdout, "found NULL\n");
			return start_ix + i;
		}
		if ( equals(htbl->table[(start_ix + i) % htbl->tablesize], ptr) ) {
			//fprintf(stdout, "found elem\n");
			return start_ix + i;
		}
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
		//fprintf(stdout, "put into %d\n", find_ix);
		htbl->table[find_ix] = obj;
	}
	return find_ix;
}

int OAHashtable_remove(OAHashtable * htbl, datatype * obj) {
	unsigned int start = OAHashtable_find_or_NULL(htbl, obj);
	unsigned int ix = 0;
	for( ; ix < htbl->tablesize ; ++ix) {
		datatype * ptr = htbl->table[(start + ix) % htbl->tablesize];
		if ( ptr == NULL )
			return ix; 	// no such data and thus removal is completed.
		if ( equals(ptr, obj) ) {
			htbl->table[(start + ix) % htbl->tablesize] = NULL;
			break;
		}
	}

	if ( ix == htbl->tablesize ) {
		fprintf(stderr, "Error: Hashtable is full!!\n");
		return -1;
	}

	start = (start + ix) % htbl->tablesize; // NULL cell
	ix = 1;
	while ( htbl->table[(start + ix) % htbl->tablesize] != NULL ) {
		unsigned int h = hash_code(htbl->table[(start + ix) % htbl->tablesize]) % htbl->tablesize;
		if ( h <= start ) {
			htbl->table[start] = htbl->table[(start + ix) % htbl->tablesize];
			start = (start + ix) % htbl->tablesize;
		}
		++ix;
	}
	return ix;
}

int OAHashtable_fprintf(FILE * fp, OAHashtable * htbl, const char * fmt) {
	int sum = 0;
	for(int i = 0; i < htbl->tablesize; ++i) {
		if ( htbl->table[i] != NULL ) {
			sum += printOn(fp, htbl->table[i]);
			sum += fprintf(fp, " %u", hash_code(htbl->table[i]) % htbl->tablesize );
		} else {
			sum += fprintf(fp, "(NULL)");
		}
		fprintf(stdout, "\n");
	}
	return sum;
}
