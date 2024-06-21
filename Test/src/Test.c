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

static int N = 32; // rows
static int M = 32; // columns

typedef struct XY {
	int x, y;
} XY;

int xy2v(int x, int y) {
	// x -- column, y -- row
	if ( x < 0 || y < 0 || x >= M || y >= N ) {
		//printf("xy2v domain error: %d, %d \n", x, y);
		return -1;
	}
	return y * M + x;
}

XY v2xy(int v) {
	// x -- column, y -- row
	XY result = {-1, -1};
	if ( v < 0 || v >= N * M ) {
		//printf("v2xy domain error. \n");
		return result;
	}
	result.y = v / M;
	result.x = v % M;
	return result;
}

int * enum_moves(int v, int result[4]) {
	static XY knightmoves[4] = {
			{-2, -1},
			{-2, +1},
			{-1, -2},
			{+1, -2},
	};
	if ( v < 0 || v >= N * M) {
		result[0] = -1;
		return result;
	}
	XY pos = v2xy(v);
	int cnt = 0;
	int cellnum;
	for(int i = 0; i < 4; ++i) {
		cellnum = xy2v(pos.x + knightmoves[i].x, pos.y + knightmoves[i].y);
		if (cellnum != -1) {
			//printf("x = %d, y = %d\n", pos.x + knightmoves[i].x, pos.y + knightmoves[i].y);
			result[cnt] = cellnum;
			++cnt;
		}
	}
	if ( cnt < 4 )
		result[cnt] = -1;
	return result;
}

int move_depth(int x, int y) {
	int mv[4];
	int t, best = 0;
	XY pos, bestpos;
	enum_moves(xy2v(x,y), mv);
	for(int i = 0; i <= 4 && mv[i] != -1; ++i) {
		pos = v2xy(mv[i]);
		t = 1 + move_depth(pos.x, pos.y);
		if (t > best) {
			best = t;
			bestpos = pos;
		}
	}
	//printf("%d, %d\n", bestpos.x, bestpos.y);
	return best;
}

int main(int argc, char * argv[]) {
	int t, startx, starty;
	if (argc > 1 && argc < 4) {
		startx = atoi(argv[1]);
		starty = atoi(argv[2]);
	} else {
		printf("Invalid number of arguments.\n");
		return EXIT_FAILURE;
	}

	printf("%d\n", xy2v(4, 2));

	XY r = v2xy(29);
	printf("x = %d, y = %d \n\n", r.x, r.y);
	int moves[4];
	enum_moves(xy2v(1,3), moves);
	for(int i = 0; i <= 4 && moves[i] != -1; ++i) {
		printf("%d, ", moves[i]);
	}
	printf("\n");
	printf("moves = %d\n\n", move_depth(startx, starty));
	return EXIT_SUCCESS;
}
