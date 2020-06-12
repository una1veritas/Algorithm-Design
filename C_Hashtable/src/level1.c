#include <stdio.h>
#include <string.h>

int main(void) {
	char str[] = "THIS IS A PEN.";
	int m = 13;
	for(int i = 0; i < strlen(str); ++i) {
		printf("%c: %d\n", str[i], str[i] % m);
	}
	printf("\n");

	return 0;
}
