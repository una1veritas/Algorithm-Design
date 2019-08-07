//============================================================================
// Name        : stairways.cpp
// Author      : Sin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime>

using namespace std;

static int ways[100];

int howmanyways(int n) {
	if ( n == 0 ) return 0;
	if ( n == 1 ) return 1;
	if ( n == 2 ) return 1 + howmanyways(2-1);
	// n >= 3
		return 1 + howmanyways(n - 1) + howmanyways(n - 2);
}

int howmanyways_dprecursion(int n) {
	if ( n == 0 ) {
		ways[n] = 0;
		return ways[n];
	}
	if ( n == 1 ) {
		ways[n] = 1;
		return ways[n];
	}
	if ( n == 2 ) {
		ways[n] = 1 + howmanyways_dprecursion(2-1);
		return ways[n];
	}
	// n >= 3
	if ( ways[n] != 0 )
		return ways[n];
	ways[n] = 1 + howmanyways_dprecursion(n - 1) + howmanyways_dprecursion(n - 2);
	return ways[n];
}

int main(const int argc, const char * argv[]) {
	if ( argc < 2 ) {
		cerr << "usage: command number (< 100)" << endl;
		return 1;
	}
	int n = atoi(argv[1]);
	n = (n > 100 ? 99: n);
	cout << "the number of steps = " << n << endl;

	int count;
	for(int s = 0; s <= n; ++s) {
		clock_t swatch = clock();
		count = howmanyways(s);
		swatch = clock() - swatch;
		cout << "for " << s << " steps, there are " << count << " ways. " << (swatch/(double)CLOCKS_PER_SEC) << endl;
		swatch = clock();
		for(int i = 0; i < 100; ++i) {
			ways[i] = 0;
		}
		count = howmanyways_dprecursion(s);
		swatch = clock() - swatch;
		cout << "for " << s << " steps, there are " << count << " ways. " << (swatch/(double)CLOCKS_PER_SEC) << endl;
	}
	return 0;
}

/*
the number of steps = 45
for 0 steps, there are 0 ways. 3e-06
for 0 steps, there are 0 ways. 0
for 1 steps, there are 1 ways. 1e-06
for 1 steps, there are 1 ways. 0
for 2 steps, there are 2 ways. 1e-06
for 2 steps, there are 2 ways. 1e-06
for 3 steps, there are 4 ways. 1e-06
for 3 steps, there are 4 ways. 1e-06
for 4 steps, there are 7 ways. 0
for 4 steps, there are 7 ways. 1e-06
for 5 steps, there are 12 ways. 2e-06
for 5 steps, there are 12 ways. 1e-06
for 6 steps, there are 20 ways. 0
for 6 steps, there are 20 ways. 1e-06
for 7 steps, there are 33 ways. 1e-06
for 7 steps, there are 33 ways. 2e-06
for 8 steps, there are 54 ways. 1e-06
for 8 steps, there are 54 ways. 1e-06
for 9 steps, there are 88 ways. 1e-06
for 9 steps, there are 88 ways. 1e-06
for 10 steps, there are 143 ways. 1e-06
for 10 steps, there are 143 ways. 2e-06
for 11 steps, there are 232 ways. 1e-06
for 11 steps, there are 232 ways. 1e-06
for 12 steps, there are 376 ways. 2e-06
for 12 steps, there are 376 ways. 1e-06
for 13 steps, there are 609 ways. 3e-06
for 13 steps, there are 609 ways. 3e-06
for 14 steps, there are 986 ways. 5e-06
for 14 steps, there are 986 ways. 1e-06
for 15 steps, there are 1596 ways. 5e-06
for 15 steps, there are 1596 ways. 2e-06
for 16 steps, there are 2583 ways. 8e-06
for 16 steps, there are 2583 ways. 1e-06
for 17 steps, there are 4180 ways. 1.3e-05
for 17 steps, there are 4180 ways. 2e-06
for 18 steps, there are 6764 ways. 3.2e-05
for 18 steps, there are 6764 ways. 1e-06
for 19 steps, there are 10945 ways. 3.5e-05
for 19 steps, there are 10945 ways. 0
for 20 steps, there are 17710 ways. 6e-05
for 20 steps, there are 17710 ways. 2e-06
for 21 steps, there are 28656 ways. 0.000111
for 21 steps, there are 28656 ways. 0
for 22 steps, there are 46367 ways. 0.000143
for 22 steps, there are 46367 ways. 0
for 23 steps, there are 75024 ways. 0.000228
for 23 steps, there are 75024 ways. 0
for 24 steps, there are 121392 ways. 0.00037
for 24 steps, there are 121392 ways. 2e-06
for 25 steps, there are 196417 ways. 0.000598
for 25 steps, there are 196417 ways. 2e-06
for 26 steps, there are 317810 ways. 0.000967
for 26 steps, there are 317810 ways. 0
for 27 steps, there are 514228 ways. 0.001565
for 27 steps, there are 514228 ways. 1e-06
for 28 steps, there are 832039 ways. 0.002533
for 28 steps, there are 832039 ways. 1e-06
for 29 steps, there are 1346268 ways. 0.004099
for 29 steps, there are 1346268 ways. 1e-06
for 30 steps, there are 2178308 ways. 0.006732
for 30 steps, there are 2178308 ways. 2e-06
for 31 steps, there are 3524577 ways. 0.010729
for 31 steps, there are 3524577 ways. 2e-06
for 32 steps, there are 5702886 ways. 0.017561
for 32 steps, there are 5702886 ways. 1e-06
for 33 steps, there are 9227464 ways. 0.0281
for 33 steps, there are 9227464 ways. 1e-06
for 34 steps, there are 14930351 ways. 0.045515
for 34 steps, there are 14930351 ways. 1e-06
for 35 steps, there are 24157816 ways. 0.07243
for 35 steps, there are 24157816 ways. 2e-06
for 36 steps, there are 39088168 ways. 0.115987
for 36 steps, there are 39088168 ways. 1e-06
for 37 steps, there are 63245985 ways. 0.189858
for 37 steps, there are 63245985 ways. 2e-06
for 38 steps, there are 102334154 ways. 0.304215
for 38 steps, there are 102334154 ways. 1e-06
for 39 steps, there are 165580140 ways. 0.487884
for 39 steps, there are 165580140 ways. 2e-06
for 40 steps, there are 267914295 ways. 0.786477
for 40 steps, there are 267914295 ways. 1e-06
for 41 steps, there are 433494436 ways. 1.27611
for 41 steps, there are 433494436 ways. 1e-06
for 42 steps, there are 701408732 ways. 2.08846
for 42 steps, there are 701408732 ways. 1e-06
for 43 steps, there are 1134903169 ways. 3.32685
for 43 steps, there are 1134903169 ways. 2e-06
for 44 steps, there are 1836311902 ways. 5.40851
for 44 steps, there are 1836311902 ways. 2e-06
for 45 steps, there are -1323752224 ways. 8.74348
for 45 steps, there are -1323752224 ways. 1e-06
 */
