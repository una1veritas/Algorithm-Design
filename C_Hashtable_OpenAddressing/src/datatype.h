/*
 * datatype.h
 *
 *  Created on: 2025/05/27
 *      Author: sin
 */

#ifndef DATATYPE_H_
#define DATATYPE_H_

#include <stdio.h>

typedef struct {
	char id[12];
	char name[32];
} datatype;


unsigned int hash_code(const datatype * d);
int equals(const datatype * d1, const datatype * d2);
size_t printOn(FILE * stream, const datatype * d);

#endif /* DATATYPE_H_ */
