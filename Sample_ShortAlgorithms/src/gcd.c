#include <stdio.h>
#include <stdlib.h>

static long counter;

int gcd_Euclidean(int a, int b) {
	int t;
	while ( (t = a % b) != 0 ) {
		a = b;
		b = t;
		++counter;
		printf("a = %d, b= %d\n", a, b);
	}
	return b;
}

int gcd_Naive(int a, int b) {
	int i;
	for (i = (a < b ? a : b); /* min{a, b} */
			(a%i) != 0 || (b%i) != 0 ; i -= 1) {
		++counter; /* printf("i = %d\n", i); */
	}
	return i;
}

int main (int argc, char * argv[]) {
	int a, b, gcd;
	
	if (argc < 3 ) {
		printf("give two numbers in arguments.");
		return 1;
	}
	a = atoi(argv[1]);
	b = atoi(argv[2]);

	printf("Input: a = %d, b = %d\n", a, b);

	printf("by Euclidean algorithm...\n");
	counter = 0;
	gcd = gcd_Euclidean(a, b);
	printf("GCD: %d, counter = %ld\n", gcd, counter);

	printf("by naive enumeration algorithm...\n");
	counter = 0;
	gcd = gcd_Naive(a, b);
	printf("GCD: %d, counter = %ld\n", gcd, counter);

	return 0;
}
