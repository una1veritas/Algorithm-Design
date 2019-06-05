#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bitprintf(unsigned int bwidth, unsigned long val) {
	bwidth = (bwidth > 64 ? 64 : bwidth);
	do {
		--bwidth;
		printf("%c", (val & (1<<bwidth) ? '1' : '0'));
	} while (bwidth > 0);
	return bwidth;
}

int main(int argc, char **argv) {
	long val;
	for(int i = 1; i < argc; ++i) {
		printf("%s ", argv[i]);
		val = strtol(argv[i], NULL, 10);
		if ( val < (((long)1)<<8) ) {
			bitprintf(val, 8); printf("\n");
		} else if ( val < (((long)1)<<17) ) {
			bitprintf(val, 16); printf("\n");
		} else {
			bitprintf(val, 32); printf("\n");
		}
	}
	return EXIT_SUCCESS;
}

/*
make

./BitManip 3487 33 987324
3487 00001101 10011111
33 00100001
987324 00000000 00001111 00010000 10111100
 */
