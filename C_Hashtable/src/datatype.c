/*
 * datatype.c
 *
 *  Created on: 2021/06/01
 *      Author: sin
 */

#include <stdio.h>
#include <string.h>

#include "datatype.h"

// calcurate unsigned long hash code (32 bit in Win 64) from id (char [8]).
unsigned long hash_code(const datatype * d) {
	unsigned long sum = 0;
	unsigned long hi8;
	for(int i = 0; i < 8; ++i) {
		hi8 = (sum>>24) & 0xff;
		sum *= 27;
		sum ^= d->id[i];
		sum ^= hi8;
	}
	return sum;
}

int equals(const datatype * d1, const datatype * d2) {
	return strncmp(d1->id, d2->id, 8) == 0;
}

int sprint(char * buf, const datatype * d) {
	char tmp[9];
	for(int i = 0; i < 8; ++i)
		tmp[i] = d->id[i];
	tmp[8] = 0;
	return sprintf(buf, "(%s: %s)", tmp, d->name);
}
