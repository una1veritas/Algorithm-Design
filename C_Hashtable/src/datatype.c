/*
 * datatype.c
 *
 *  Created on: 2021/06/01
 *      Author: sin
 */

#include <stdio.h>

#include "datatype.h"

long key(const datatype d) {
	return d->id;
}

int equals(const datatype d1, const datatype d2) {
	return d1->id == d2->id;
}

int sprint(char * buf, datatype d) {
	return sprintf(buf, "(%ld: %s)", d->id, d->name);
}
