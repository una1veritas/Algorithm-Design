/*
 * datatype.c
 *
 *  Created on: 2021/06/01
 *      Author: sin
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "datatype.h"

// calculate unsigned long hash code (32 bit in Win 64) from id (char [8]).
uint32_t hash_code(const datatype * d) {
	uint32_t sum = 0;
	for(int i = 0; d->name[i] != 0; ++i) {
		sum *= 31;
		sum += d->name[i];
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
	return sprintf(buf, "(%s: %s) hash = %lu", tmp, d->name, hash_code(d));
}
