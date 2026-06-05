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

// searches the same data or NULL from hashed 2position
unsigned int OAHashtable_linearProbe_for(OAHashtable * htbl, const datatype * dataptr) {
	unsigned int start = hash_code(dataptr) % htbl->tablesize;
	unsigned int i = 0;
	for( ; i < htbl->tablesize; ++i) {
		unsigned int ix = (start + i) % htbl->tablesize;
		if ( htbl->table[ix] == NULL )
			return ix;
		if ( equals(htbl->table[ix], dataptr) )
			return ix;
	}
	return i; // table has no NULL error, returns impossible value
}

bool OAHashtable_add(OAHashtable * htbl, datatype * dataptr) {
	unsigned int ix = OAHashtable_linearProbe_for(htbl, dataptr);
	if ( htbl->table[ix] != NULL )
		return true;

	if ( htbl->count >= htbl->tablesize - 1 ) {
		fprintf(stderr, "Error: Hashtable is full!!\n");
		return false;
	}

	htbl->table[ix] = dataptr;
	++htbl->count;

	return true;
}

bool OAHashtable_remove(OAHashtable * htbl, datatype * dataptr) {
	unsigned int ix = OAHashtable_linearProbe_for(htbl, dataptr);

	if ( htbl->table[ix] == NULL )
		return false; 	// *dataptr is not included. Do nothing.

	htbl->table[ix] = NULL; 	// made the space empty
	--htbl->count;
	// table has at least two empty cell

	// fix collisions from ix
	unsigned int i = 1;
	while ( i < htbl->tablesize ) {
		unsigned int iy = (ix + i) % htbl->tablesize;
		if ( htbl->table[iy] == NULL )
			return true;

		unsigned int h = OAHashtable_linearProbe_for(htbl, htbl->table[iy]);
		if ( h != iy && htbl->table[h] == NULL ) {
			// h == ix
			htbl->table[ix] = htbl->table[iy];
			htbl->table[iy] = NULL;
			ix = iy;
			i = 0;
		}

		++i;
	}
	return true;
}

int OAHashtable_fprintf(FILE * fp, OAHashtable * htbl, const char * fmt) {
	int sum = 0;
	for(int i = 0; i < htbl->tablesize; ++i) {
		if ( htbl->table[i] != NULL ) {
			sum += printOn(fp, htbl->table[i]);
			sum += fprintf(fp, "hashcode = %u / %u", hash_code(htbl->table[i]), hash_code(htbl->table[i]) % htbl->tablesize );
		} else {
			sum += fprintf(fp, "(NULL)");
		}
		fprintf(stdout, "\n");
	}
	return sum;
}
