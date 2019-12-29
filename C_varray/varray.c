#include "varray.h"

void varray_init(varray * v, unsigned int minsize) {
	if ( minsize < 8 ) minsize = 8;
	v->capacity = minsize;
	v->array = (data*) malloc(sizeof(data) * v->capacity);
	v->size = 0;
}

void varray_free(varray * v) {
	free(v->array);
	v->capacity = 0;
	v->size = 0;
}

void varray_resize(varray * v) {
	unsigned int newcapa = 8;
	while ( newcapa <= v->capacity ) {
		newcapa <<= 1;
	}
	data * newarray = (data*)malloc(sizeof(data)*newcapa);
	v->capacity = newcapa;
	for(int i = 0; i < v->size; ++i) {
		newarray[i] = v->array[i];
	}
	free(v->array);
	v->array = newarray;
}

data varray_at(varray * v, unsigned int i) {
	return v->array[i];
}

data varray_back(varray * v) {
	return v->array[v->size - 1];
}

void varray_pushback(varray * v, data d) {
	if ( !(v->size < v->capacity) ) {
		varray_resize(v);
	}
	v->array[v->size] = d;
	v->size += 1;
}
