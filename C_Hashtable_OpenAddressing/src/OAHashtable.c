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

unsigned int OAHashtable_find_or_NULL(OAHashtable * htbl, datatype * obj) {
	unsigned int start_ix = hash_code(obj) % htbl->tablesize;
	unsigned int i;
	for(i = 0; i < htbl->tablesize; ++i) {
		unsigned int ix = (start_ix + i) % htbl->tablesize;
		if ( htbl->table[ix] == NULL ) {
			//fprintf(stdout, "found NULL @ %d\n", ix);
			return ix;
		}
		if ( equals(htbl->table[ix], obj) ) {
			//fprintf(stdout, "found the obj @ %d\n", ix);
			return ix;
		}
	}
	// error. table[] has no NULL!
	return i;
}

bool OAHashtable_add(OAHashtable * htbl, datatype * obj) {
	unsigned int find_ix = OAHashtable_find_or_NULL(htbl, obj);
	if ( htbl->count >= htbl->tablesize - 1 ) {
		fprintf(stdout, "Error: Hashtable is full!!\n");
		return false;
	}

	if ( htbl->table[find_ix] == NULL ) {
		htbl->table[find_ix] = obj;
		++htbl->count;
		//fprintf(stdout, "%d is filled\n", find_ix);
	}
	// If != NULL, obj is already included. Do nothing.
	return true;
}

bool OAHashtable_remove(OAHashtable * htbl, datatype * obj) {
	unsigned int startix = OAHashtable_find_or_NULL(htbl, obj);

	if ( htbl->table[startix] == NULL )
		return false; 	// obj is not included, do nothing.

	--htbl->count;

	htbl->table[startix] = NULL; 	// made the space empty
	for (unsigned int i = 1; i < htbl->tablesize; ++i ) {
		if ( htbl->table[(startix + i) % htbl->tablesize] == NULL )
			return true;
		unsigned int h = hash_code(htbl->table[(startix + i) % htbl->tablesize]) ;
		for (unsigned int j = 0; j < htbl->tablesize; ++j) {
			if ( (h + j) % htbl->tablesize == startix ) {
				htbl->table[startix] = htbl->table[(startix + i) % htbl->tablesize];
				startix = (startix + i) % htbl->tablesize;
				htbl->table[startix] = NULL;
				break;
			}
			if ( htbl->table[(h + j) % htbl->tablesize] == NULL ) {
				fprintf(stdout, "found NULL error at %d\n", (h + j) % htbl->tablesize);
				return false;
			}
			if ( (h + j) % htbl->tablesize == (startix + i) % htbl->tablesize )
				break;
		}
	}
	return true;
}

int OAHashtable_fprintf(FILE * fp, OAHashtable * htbl, const char * fmt) {
	int sum = 0;
	for(int i = 0; i < htbl->tablesize; ++i) {
		if ( htbl->table[i] != NULL ) {
			sum += printOn(fp, htbl->table[i]);
			sum += fprintf(fp, "hashcode = %u, mod %u =  %u", hash_code(htbl->table[i]), htbl->tablesize, hash_code(htbl->table[i]) % htbl->tablesize );
		} else {
			sum += fprintf(fp, "(NULL)");
		}
		fprintf(stdout, "\n");
	}
	return sum;
}
