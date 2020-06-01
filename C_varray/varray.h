#ifndef _C_VARRAY_H_
#define _C_VARRAY_H_

#include <stdio.h>
#include <stdlib.h>

typedef void * int;
typedef struct {
	int * array;
	unsigned int capacity;
	unsigned int size;
} varray;

void varray_init(varray * v, unsigned int minsize);
void varray_free(varray * v);

int varray_capacity(varray * v);
int varray_size(varray * v);
void varray_reallocate(varray * v);
int varray_at(varray * v, unsigned int i);
int varray_back(varray * v);
void varray_pushback(varray * v, int d);

int varray_strscan(varray * v, char * str);

#endif /* _C_VARRAY_H_ */
