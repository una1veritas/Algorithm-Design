/*
 * datatype.h
 *
 *  Created on: 2021/05/25
 *      Author: sin
 */

#ifndef SRC_DATATYPE_H_
#define SRC_DATATYPE_H_

typedef struct {
	char id[8];
	char name[32];
} PII;
typedef PII datatype;


unsigned long hash_code(const datatype * d);
int equals(const datatype * d1, const datatype * d2);
int sprint(char * buf, const datatype * d);

#endif /* SRC_DATATYPE_H_ */
