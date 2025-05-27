/*
 * Hashtable_OpenAddress.h
 *
 *  Created on: 2025/05/27
 *      Author: sin
 */

#ifndef OAHASHTABLE_H_
#define OAHASHTABLE_H_

#include <stdlib.h>

#include "datatype.h"


typedef struct OAHashtable {
	datatype ** table;
	unsigned int tablesize, elemcount;
} OAHashtable;

OAHashtable * allocate_OAHashtable(unsigned int size);
void free_OAHashtable(OAHashtable * htbl);

unsigned int OAHashtable_find_or_NULL(OAHashtable * htbl, datatype * obj);
int OAHashtable_add(OAHashtable * htbl, datatype * obj);
int OAHashtable_remove(OAHashtable * htbl, datatype * obj);
int OAHashtable_fprintf(FILE *, OAHashtable * htbl, const char *);

#endif /* OAHASHTABLE_H_ */
