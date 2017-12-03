//============================================================================
// Name        : GCD.cpp
// Author      : Sin Shimozono
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <time.h>

#define count(x) (++x)

static long loop_Euclidean = 0;
static long loop_naive = 0;

long gcd_Euclidean(long a, long b) {
	long c;
	do {
		c = a % b;
		a = b;
		b = c;
		count(loop_Euclidean);
	} while ( c );
	return a;
}

long gcd_naive(long a, long b) {
	long c;
	for(long i = 1; i < (a >= b ? b : a); ++i ) {
		count(loop_naive);
		if ( (a % i) == 0 && (b % i) == 0 )
			c = i;
	}
	return c;
}

int main(int argc, char * argv[]) {
//	cout << "Hello World!!!" << endl; // prints Hello World!!!

	long a, b, c, t;

	if ( argc < 3 )
		return -1;

	a = atol(argv[1]);
	b = atol(argv[2]);
	cout << "a = " << a << ", b = " << b << endl;

	t = clock();
	c = gcd_Euclidean(a,b);
	t = clock() - t;

	cout << "gcd_euclidean(a,b) = " << c << endl;
	cout << "elapsed time " << (double)t/CLOCKS_PER_SEC * 1000 << endl;

	t = clock();
	c = gcd_naive(a,b);
	t = clock() - t;

	cout << "gcd_naive(a,b) = " << c << endl;
	cout << "elapsed time " << (double)t/CLOCKS_PER_SEC * 1000 << endl;

	cout << "loop_Euclidean = " << loop_Euclidean << " loop_naive = " << loop_naive << endl;
	return 0;
}
