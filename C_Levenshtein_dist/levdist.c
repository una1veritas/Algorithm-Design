#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int levdist(const char * s, const char * t) {
	int len_s = strlen(s), len_t = strlen(t);
	int d[len_s+1][len_t+1]; 	// DP 表
	// DP 表の最左列の初期化
	for(int i = 0; i < len_s+1; ++i)
		d[i][0] = i;
	// DP 表の最上行の初期化
	for(int i = 0; i < len_t+1; ++i)
		d[0][i] = i;
	// それ以外のセルの計算
	int repl, inst, delt;
	for(int i = 1; i < len_s+1; ++i) {
		for(int j = 1; j < len_t+1; ++j) {
			if (s[i-1] == t[j-1]) {
				d[i][j] = d[i-1][j-1];
			} else {
				repl = d[i-1][j-1] + 1;
				inst = d[i][j-1] + 1;
				delt = d[i-1][j] + 1;
				if (repl <= inst) {
					if (repl <= delt) {
						d[i][j] = repl;
					} else {
						d[i][j] = delt;
					}
				} else {
					if (inst <= delt) {
						d[i][j] = inst;
					} else {
						d[i][j] = delt;
					}
				}
			}
		}
	}
	// only for displaying the table
	printf("   ");
	for(int j = 0; j < len_t+1; ++j) {
		printf("   %c ", (j == 0 ? ' ' : t[j-1]) );

	}
	printf("\n---");
	for(int j = 0; j < len_t+1; ++j) {
		printf("-----");
	}
	printf("\n");
	for(int i = 0; i < len_s+1; ++i) {
		printf("%c| ", (i == 0 ? ' ' : s[i-1]) );
		for(int j = 0; j < len_t+1; ++j) {
			printf("%4d ", d[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	//
	return d[len_s][len_t];
}

int main(const int argc, const char *argv[]) {
	const char * s = argv[1], * t = argv[2];

	int d = levdist(s, t);
	printf("Levenshtein distance between %s and %s is %d.\n", s, t, d);
	return EXIT_SUCCESS;
}
