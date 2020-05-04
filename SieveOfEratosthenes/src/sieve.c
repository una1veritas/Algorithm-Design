/*
 ============================================================================
 Name        : SieveOfEratosthenes.c
 Author      : Sin Shimozono
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int sieve(int n) {
	char sv[n+1];
	int i;
	for(i = 2; i <= n; ++i)
		sv[i] = 1;
	for(i = 2; i <= n/2; ++i ) {
		if (! sv[i] ) continue;
		for(int j = i*2; j <= n; j += i)
			sv[j] = 0;
	}
	// sieve[2] == 1
	for(i = n; i > 2 && !sv[i]; --i);
	return i;
}

int main(const int argc, const char * argv[]) {
	if (argc < 2) { puts("error: give a limit number.\n"); return EXIT_FAILURE; }
	int n = atoi(argv[1]);
	printf("the largest prime no more than %d is: %d.\n", n, sieve(n));
	return EXIT_SUCCESS;
}
