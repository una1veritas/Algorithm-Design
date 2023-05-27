/*
 * vlarray.h
 *
 * A simple variable length array.
 *  Created on: 2023/05/27
 *      Author: Sin Shimozono
 */

#ifndef SRC_VLARRAY_H_
#define SRC_VLARRAY_H_

#include "datadef.h"

typedef struct {
	data ** a;
	unsigned int n;
	unsigned int limit;
} vlarray;

int vlarray_init(vlarray * vla, unsigned int capa);
void vlarray_delete(vlarray * vla);

unsigned int vlarray_capacity(vlarray * vla);
int vlarray_enlarge(vlarray * vla);
int vlarray_append(vlarray * vla, data * d);

#endif /* SRC_VLARRAY_H_ */
