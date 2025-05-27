#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[]) {
	if (argc <= 1) {
		fprintf(stderr, "no arguments.\n");
		return 1;
	}

	char * p;
	int sum;
	for(int i = 0; i < argc-1; ++i) {
		sum = 0;
		for(p = argv[1+i]; *p; ++p) {
			sum += *p;
		}
		printf("sum(%s) = %d\n", argv[1+i], sum);
	}

	return 0;
}
