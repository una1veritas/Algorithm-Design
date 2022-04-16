#include <stdio.h>
#include <stdlib.h>

long modpow(long x, long n, long m) {
	long t = 1, p = x;
	while ( n ) {
		if ( n & 1 )  /* n は奇数か */
			t = (t * p) % m;
		p = (p * p) % m;  /* p = x^1, x^2, x^4, x^8, ... */
		n = n >> 1;   /* n = n/2 */
	}
	return t;
}

long modpow_r(long x, long n, long m) {
	long t;
	if ( n == 1 )
		return x % m;
	t = modpow_r(x, n/2, m);
	if ( (n % 2) == 1 ) {
		return t*t*x % m;
	} else {
		return t*t % m;
	}
	return t;
}

int main(const int argc, const char * argv[]) {
	if (argc < 4) { puts("error: give x, n and m.\n"); return EXIT_FAILURE; }
	long x = atol(argv[1]), n = atol(argv[2]), m = atol(argv[3]);

	printf("%ld^%ld mod %ld = %ld.\n", x, n, m, modpow(x,n,m));
	printf("%ld^%ld mod %ld = %ld.\n", x, n, m, modpow_r(x,n,m));
	return EXIT_SUCCESS;
}
