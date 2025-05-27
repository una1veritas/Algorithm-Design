/*
 * datatype.h
 *
 *  Created on: 2025/05/27
 *      Author: sin
 */

#ifndef DATATYPE_H_
#define DATATYPE_H_

typedef struct {
	char id[8];
	char name[32];
} PII;
typedef PII datatype;


unsigned int hash_code(const datatype * d);
int equals(const datatype * d1, const datatype * d2);
int sprint(char * buf, const datatype * d);

#endif /* DATATYPE_H_ */
