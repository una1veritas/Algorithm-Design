/*
 ============================================================================
 Name        : sample-random.c
 Author      : Sin Shimozono
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int rnd() {
	static int r = 1102; /* 自分の学生番号の下4 桁に書き換える */
	r = ((r + 1013) * 171) % 1331;
	return r;
}

int main(void) {
	int tp, arg1, arg2;
	for(int i = 0; i < 16; ++i) {
		tp = rnd() % 2;
		arg1 = rnd() % 17;
		arg2 = rnd() % 17;

		if (tp) {
			printf("Find(%d)\n", arg1);
		} else {
			printf("Union(%d, %d)\n",arg1, arg2);
		}
	}
	return EXIT_SUCCESS;
}
