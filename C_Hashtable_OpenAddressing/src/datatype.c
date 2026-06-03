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

	for(int i = 0; d->surname[i] != 0; ++i) {
		sum *= 31;
		sum += d->surname[i];
	}

	for(int i = 0; d->givenname[i] != 0; ++i) {
		sum *= 31;
		sum += d->givenname[i];
	}

	return sum;
}

bool equals(const datatype * d1, const datatype * d2) {
	return (strcmp(d1->surname, d2->surname) == 0) && (strcmp(d1->givenname, d2->givenname) == 0);
}

size_t printOn(FILE * stream, const datatype * d) {
	char buf[256];
	char lastname[64];
	snprintf(lastname, 63, "%s,", d->surname);
	snprintf(buf, 255, "%-10s %-10s ", lastname, d->givenname);
	return fputs(buf, stream);
}
