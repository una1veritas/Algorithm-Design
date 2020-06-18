/*
 * datadef.h
 *
 *  Created on: 2020/06/18
 *      Author: sin
 */

#ifndef DATADEF_H_
#define DATADEF_H_

typedef struct {
	char id[8];
	char name[32];
} idname;
typedef idname * data;

long keycode(const data d);

#endif /* DATADEF_H_ */
