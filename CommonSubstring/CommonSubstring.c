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

int commonSubstring_dp(const char * s, const char * t) {
	int table[strlen(t)][strlen(s)];
	//char * cstr = (char*) malloc(sizeof(char)*(strlen(s) < strlen(t) ? strlen(t) : strlen(s)));
	int i_s, i_t;
	for(i_s = 0; s[i_s]; ++i_s) {
		table[0][i_s] = (t[0] == s[i_s] ? 1 : 0);
	}
	for(i_t = 1; t[i_t]; ++i_t) {
		table[i_t][0] = (t[i_t] == s[0] ? 1 : 0);
		for(i_s = 1; s[i_s] ; ++i_s) {
			if ( t[i_t] == s[i_s] ) {
				table[i_t][i_s] = table[i_t - 1][i_s - 1] + 1;
			} else {
				table[i_t][i_s] = (table[i_t - 1][i_s] > table[i_t][i_s - 1] ?
						table[i_t - 1][i_s] : table[i_t][i_s - 1]);
			}
		}
	}
	return table[strlen(t)-1][strlen(s)-1];
}

int main(int argc, char **argv) {
	if ( argc < 3 ) {
		printf("error: give two strings.\n");
	}
	char * s = argv[1], * t = argv[2];
	printf("%s, %s\n", s, t);
	//char * cs
	int l = commonSubstring_dp(s, t);
	//printf("common substring: \n'%s' (%d)\n", cs, (int)strlen(cs));
	//free(cs);
	printf("%d\n", l);
	return 0;
}
