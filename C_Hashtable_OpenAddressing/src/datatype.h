/*
 * datatype.h
 *
 *  Created on: 2025/05/27
 *      Author: sin
 */

#ifndef DATATYPE_H_
#define DATATYPE_H_

#include <stdio.h>
#include <stdbool.h>

typedef struct PersonalData {
	char givenname[12];
	char surname[32];
} datatype;


unsigned int hash_code(const datatype * d);
bool equals(const datatype * d1, const datatype * d2);
size_t printOn(FILE * stream, const datatype * d);

#endif /* DATATYPE_H_ */
