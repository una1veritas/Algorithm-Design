/*
 * datatype.c
 *
 *  Created on: 2021/06/01
 *      Author: sin
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "datatype.h"

// calculate unsigned int hash code by id (32 bit in Win 64) from id (char [8]).
unsigned int hash_code(const datatype * d) {
	unsigned int sum = 0;
	//unsigned long hi8;
	for(int i = 0; d->name[i] != 0; ++i) {
		sum *= 31;
		sum += d->name[i];
	}
	return sum;
}

bool equals(const datatype * d1, const datatype * d2) {
	return strncmp(d1->id, d2->id, 8) == 0;
}

size_t printOn(FILE * stream, const datatype * d) {
	char buf[256];
	snprintf(buf, 255, "(%s: %s) ", d->id, d->name);
	return fputs(buf, stream);
}
