/*
 * datatype.h
 *
 *  Created on: 2021/05/25
 *      Author: sin
 */

#ifndef SRC_DATATYPE_H_
#define SRC_DATATYPE_H_

typedef struct {
	long id;
	char name[32];
} idname;
typedef idname * datatype;


long key(const datatype d);
int equals(const datatype d1, const datatype d2);
int sprint(char * buf, datatype d);

#endif /* SRC_DATATYPE_H_ */
