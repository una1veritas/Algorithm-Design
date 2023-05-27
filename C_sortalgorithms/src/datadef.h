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
typedef long data;

long keyval(const data * d);
int  equals(const data * d1, const data * d2);
int  lessthan(const data * d1, const data * d2);
int  lessthanoreq(const data * d1, const data * d2);
int  fprintf_data(FILE * fp, const data * d);

#endif /* DATADEF_H_ */
