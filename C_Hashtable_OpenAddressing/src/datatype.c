/*
 * datatype.c
 *
 *  Created on: 2021/06/01
 *      Author: sin
 */

#include <stdio.h>
#include <string.h>

#include "datatype.h"

// calculate unsigned int hash code by id (32 bit in Win 64) from id (char [8]).
unsigned int hash_code(const datatype * d) {
	unsigned int sum = 0;
	//unsigned long hi8;
	for(int i = 0; i < 8; ++i) {
		//hi8 = (sum>>(sizeof(unsigned long)*8 - 8)) & 0xff;
		sum *= 31;
		sum += d->id[i];
	}
	return sum;
}

int equals(const datatype * d1, const datatype * d2) {
	return strncmp(d1->id, d2->id, 8) == 0;
}

size_t printOn(FILE * stream, const datatype * d) {
	char buf[256];
	snprintf(buf, 255, "(%s: %s) hash = %u", d->id, d->name, hash_code(d));
	return fputs(buf, stream);
}
