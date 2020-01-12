#ifndef _C_VARRAY_H_
#define _C_VARRAY_H_

#include <stdio.h>
#include <stdlib.h>

typedef void * data;
typedef struct {
	data * array;
	unsigned int capacity;
	unsigned int size;
} varray;

void varray_init(varray * v, unsigned int minsize);
void varray_free(varray * v);

int varray_capacity(varray * v);
int varray_size(varray * v);
void varray_reallocate(varray * v);
data varray_at(varray * v, unsigned int i);
data varray_back(varray * v);
void varray_pushback(varray * v, data d);

int varray_strscan(varray * v, char * str);

#endif /* _C_VARRAY_H_ */
