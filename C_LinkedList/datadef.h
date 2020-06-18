/*
 * datadef.h
 *
 *  Created on: 2020/06/18
 *      Author: sin
 */

#ifndef DATADEF_H_
#define DATADEF_H_

typedef void * data;

unsigned long keycode(const data d1);
int equals(const data d1, const data d2);
int lessthan(const data d1, const data d2);

#endif /* DATADEF_H_ */
