/*
 * datadef.h
 *
 *  Created on: 2020/06/18
 *      Author: sin
 */

#ifndef DATADEF_H_
#define DATADEF_H_

#include <stdio.h>

//typedef char * data;
typedef struct MEMBER {
	char id[10];
	char name[32];
} data;

typedef int (* compfunc)(const void *, const void *);
typedef int (* hashfunc)(const void *);

long keyval(const void * d);
int  equals(const void * d1, const void * d2);
int  lessthan(const void * d1, const void * d2);
int  fprintf_data(FILE * fp, const data * d);

#endif /* DATADEF_H_ */
