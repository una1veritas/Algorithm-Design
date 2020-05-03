#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ループ回数計測用 */
#define countup (++_loop_counter)
#define countclear (_loop_counter = 0)
#define countvalue (_loop_counter)
static long _loop_counter;


long gcd_naive(long a, long b) {
	long min_a_b = (a <= b ? a : b);
	for(long i = min_a_b; i > 1; --i ) {
		countup;
		if ( (a % i) == 0 && (b % i) == 0 )
			return i;
	}
	return 1;
}


long gcd_Euclidean(long a, long b) {
	long c;
	for( ; (c = a % b) != 0; a = b, b = c) {
		countup;
	}
	return b;
}

int main(int argc, char * argv[]) {
	long a, b, c, t;
	long cnt_e, cnt_n;

	if ( argc < 3 ) {
		printf("error: two numbers are requested.\n");
		return -1;
	}

	a = atol(argv[1]);
	b = atol(argv[2]);
	printf("input: a = %ld, b = %ld\n", a, b);

	countclear;
	t = clock();
	c = gcd_Euclidean(a,b);
	t = clock() - t;
	cnt_e = countvalue;

	printf("gcd_euclidean(a,b) = %ld\n", c);
	printf("elapsed time: %f\n", (double)t/CLOCKS_PER_SEC * 1000);

	countclear;
	t = clock();
	c = gcd_naive(a,b);
	t = clock() - t;
	cnt_n = countvalue;

	printf("gcd_naive(a,b) = %ld\n", c);
	printf("elapsed time: %f\n", (double)t/CLOCKS_PER_SEC * 1000);

	printf("loop_in Euclidean = %ld, loop_in naive = %ld\n", cnt_e, cnt_n);
	return 0;
}
