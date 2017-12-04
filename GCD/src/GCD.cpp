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

#define countup (++_loop_counter)
#define countclear (_loop_counter = 0)
#define countvalue (_loop_counter)
static long _loop_counter;

long gcd_Euclidean(long a, long b) {
	long c;
	do {
		c = a % b;
		a = b;
		b = c;
		countup;
	} while ( c );
	return a;
}

long gcd_naive(long a, long b) {
	long c;
	for(long i = 1; i < (a >= b ? b : a); ++i ) {
		countup;
		if ( (a % i) == 0 && (b % i) == 0 )
			c = i;
	}
	return c;
}

int main(int argc, char * argv[]) {
//	cout << "Hello World!!!" << endl; // prints Hello World!!!

	long a, b, c, t;
	long cnt_e, cnt_n;

	if ( argc < 3 ) {
		cout << "two numbers are requested." << endl;
		return -1;
	}

	a = atol(argv[1]);
	b = atol(argv[2]);
	cout << "a = " << a << ", b = " << b << endl;

	countclear;
	t = clock();
	c = gcd_Euclidean(a,b);
	t = clock() - t;
	cnt_e = countvalue;

	cout << "gcd_euclidean(a,b) = " << c << endl;
	cout << "elapsed time " << (double)t/CLOCKS_PER_SEC * 1000 << endl;

	countclear;
	t = clock();
	c = gcd_naive(a,b);
	t = clock() - t;
	cnt_n = countvalue;

	cout << "gcd_naive(a,b) = " << c << endl;
	cout << "elapsed time " << (double)t/CLOCKS_PER_SEC * 1000 << endl;

	cout << "loop_Euclidean = " << cnt_e << " loop_naive = " << cnt_n << endl;
	return 0;
}
