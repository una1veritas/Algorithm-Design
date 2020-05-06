#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * commonSubstring(const char * s, const char * t) {
	char * cstr = (char*) malloc(sizeof(char)*(strlen(s) < strlen(t) ? strlen(t) : strlen(s)));
	int i_s, i_t, i_c;
	int bestlen = 0;
	for(i_s = 0; s[i_s] ; ++i_s) {
		for(i_t = 0; t[i_t]; ++i_t) {
			for(i_c = 0; s[i_s+i_c] && t[i_t+i_c] && s[i_s+i_c] == t[i_t+i_c]; ++i_c) ;
			if ( i_c > bestlen ) {
				strncpy(cstr, s+i_s, i_c);
				cstr[i_c] = 0;
				bestlen = i_c;
			}
		}
	}
	return cstr;
}

int main(int argc, char **argv) {
	if ( argc < 3 ) {
		printf("error: give two strings.\n");
	}
	char * s = argv[1], * t = argv[2];
	printf("%s, %s\n", s, t);
	char * cs = commonSubstring(s, t);
	printf("common substring: \n'%s' (%d)\n", cs, (int)strlen(cs));
	free(cs);
	return 0;
}
