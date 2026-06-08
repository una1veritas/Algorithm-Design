/*
 * datadef.h
 *
 *  Created on: 2020/06/18
 *      Author: sin
 */

#ifndef DATADEF_H_
#define DATADEF_H_

#include <stdio.h>
#include <stdbool.h>

/*
//typedef char * data;
typedef struct MEMBER {
	char id[10];
	char name[32];
} data;
*/

typedef struct IntPair {
	int x, y;
} data;

typedef bool (* eqfunc)(const void *, const void *);
typedef bool (* lessfunc)(const void *, const void *);
typedef bool (* hashfunc)(const void *);

int keyval(const void * d);
bool equals(const void * d1, const void * d2);
bool lessthan(const void * d1, const void * d2);
int fprintf_data(FILE * fp, const data * d);

#endif /* DATADEF_H_ */
