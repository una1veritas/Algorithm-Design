/*
 ============================================================================
 Name        : Test.c
 Author      : Sin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

static const int N = 5; // rows
static const int M = 7; // columns

int xy2v(int x, int y) {
	// x -- column, y -- row
	if ( x < 0 || y < 0 || x >= M || y >= N ) {
		printf("xy2v domain error: %d, %d \n", x, y);
		return -1;
	}
	return y * M + x;
}

typedef struct {
	int x, y;
} XY;

XY v2xy(int v) {
	// x -- column, y -- row
	XY result = {-1, -1};
	if ( v < 0 || v >= N * M ) {
		printf("v2xy domain error. \n");
		return result;
	}
	result.y = v / M;
	result.x = v % M;
	return result;
}

int * enum_moves(int v) {
	int * result = (int *)malloc(sizeof(int)*5);
	static XY leftupKnight[4] = {
			{-2, -1},
			{-2, +1},
			{-1, -2},
			{+1, -2},
	};
	XY pos = v2xy(v);
	int cnt = 0;
	int cellnum;
	for(int i = 0; i < 4; ++i) {
		printf("x = %d, y = %d\n", pos.x + leftupKnight[i].x, pos.y + leftupKnight[i].y);
		cellnum = xy2v(pos.x + leftupKnight[i].x, pos.y + leftupKnight[i].y);
		if (cellnum != -1) {
			result[cnt] = cellnum;
			++cnt;
		}
	}
	result[cnt] = -1;
	return result;
}

int main(void) {

	printf("%d\n", xy2v(4, 2));

	XY r = v2xy(29);
	printf("x = %d, y = %d \n", r.x, r.y);
	int * ptr = enum_moves(xy2v(1,3));
	for(int * p = ptr; *p != -1; ++p) {
		printf("%d, ", *p);
	}
	printf("\n");
	free(ptr);
	return EXIT_SUCCESS;
}
