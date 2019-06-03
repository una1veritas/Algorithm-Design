#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bitprintf(long v, int bits) {
	int t = 8;
	int count = 0;
	while (t < bits)
		t <<= 1;
	bits = t;
	do {
		bits -= 8;
		t = (v>>(bits)) & 0xff;
		count += printf("%c%c%c%c%c%c%c%c ",
				(t & 0x80 ? '1' : '0'),
				(t & 0x40 ? '1' : '0'),
				(t & 0x20 ? '1' : '0'),
				(t & 0x10 ? '1' : '0'),
				(t & 0x08 ? '1' : '0'),
				(t & 0x04 ? '1' : '0'),
				(t & 0x02 ? '1' : '0'),
				(t & 0x01 ? '1' : '0') );
	} while ( bits > 0);
	return count;
}

int main(int argc, char **argv) {
	long val;
	for(int i = 1; i < argc; ++i) {
		printf("%s ", argv[i]);
		val = strtol(argv[i], NULL, 10);
		if ( val < (((long)1)<<17) ) {
			bitprintf(val, 16); printf("\n");
		} else {
			bitprintf(val, 32); printf("\n");
		}
	}
	return EXIT_SUCCESS;
}
