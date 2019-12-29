#ifndef _C_VARRAY_H_
#define _C_VARRAY_H_

#include <stdio.h>
#include <stdlib.h>

typedef int data;

typedef struct {
	data * array;
	unsigned int capacity;
	unsigned int size;
} varray;

void varray_init(varray * v, unsigned int minsize);
void varray_free(varray * v);

void varray_resize(varray * v);
data varray_at(varray * v, unsigned int i);
data varray_back(varray * v);
void varray_pushback(varray * v, data d);

#endif /* _C_VARRAY_H_ */
