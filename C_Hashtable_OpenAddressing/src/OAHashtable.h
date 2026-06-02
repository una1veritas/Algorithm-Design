/*
 * Hashtable_OpenAddress.h
 *
 *  Created on: 2025/05/27
 *      Author: sin
 */

#ifndef OAHASHTABLE_H_
#define OAHASHTABLE_H_

#include <stdlib.h>
#include <stdbool.h>

#include "datatype.h"


typedef struct OAHashtable {
	datatype ** table;
	unsigned int tablesize, count;
} OAHashtable;

OAHashtable * OAHashtable_allocate(unsigned int size);
void OAHashtable_free(OAHashtable * htbl);

unsigned int OAHashtable_find_or_NULL(OAHashtable * htbl, datatype * obj);
bool OAHashtable_add(OAHashtable * htbl, datatype * obj);
bool OAHashtable_remove(OAHashtable * htbl, datatype * obj);
int OAHashtable_fprintf(FILE *, OAHashtable * htbl, const char *);

#endif /* OAHASHTABLE_H_ */
