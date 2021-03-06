/*
 * datadef_str.c
 *
 *  Created on: 2021/06/02
 *      Author: sin
 */


#include "datadef.h"

/*
int lessthan(const data * x, const data * y) {
	return *x < *y;
}

long keyval(const data * x) {
	return *x;
}
*/

#include <string.h>

int lessthan(const data * x, const data * y) {
	return strcmp(*x, *y) < 0;
}

long keyval(const data * x) {
	char * str = *x;
	long t = 0;
	long f = 31;
	for (int i = 0; str[i]; ++i) {
		t+= str[i]*31;
		f *= 31;
	}
	return t;
}

int  fprintf_data(FILE * fp, const data * d) {
	return fprintf(fp, "%s", *d);
}
