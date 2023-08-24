#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int levdist(const char * s, const char * t, char editops[]) {
	int len_s = strlen(s), len_t = strlen(t);
	int d[len_s+1][len_t+1]; 	// DP 表
	int i, j;
	// DP 表の最左列の初期化
	for(i = 0; i < len_s+1; ++i)
		d[i][0] = i;
	// DP 表の最上行の初期化
	for(i = 0; i < len_t+1; ++i)
		d[0][i] = i;
	// それ以外のセルの計算
	int repl, inst, delt;
	for(i = 1; i < len_s+1; ++i) {
		for(j = 1; j < len_t+1; ++j) {
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

	int oplen = 0; // length of the sequence of edit operations
	i = len_s, j = len_t;
	while (i > 0 || j > 0) {
		printf("i = %d, j = %d, oplen = %d\n", i, j, oplen);
		if ( s[i-1] == t[j-1] && d[i][j] == d[i-1][j-1] ) {
			editops[oplen++] = '>';
			--i, --j;
		} else if (d[i][j] == d[i-1][j-1] + 1) {
			editops[oplen++] = 'R';
			--i, --j;
		} else if (d[i][j] == d[i-1][j] + 1) {
			editops[oplen++] = 'I';
			--i;
		} else if (d[i][j] == d[i][j-1] + 1) {
			editops[oplen++] = 'D';
			--j;
		} else {
			printf("error!\n");
			break;
		}
	}
	editops[oplen] = '\0';
	char tmp;
	for(int i = 0; i < oplen>>1; ++i) {
		tmp = editops[i];
		editops[i] = editops[oplen-1-i];
		editops[oplen-1-i] = tmp;
	}
	return d[len_s][len_t];
}

int main(const int argc, const char *argv[]) {
	const char * s = argv[1], * t = argv[2];
	char ops[strlen(s)+strlen(t)];

	int d = levdist(s, t, ops);
	printf("Levenshtein distance between %s and %s is %d.\n", s, t, d);
	printf("Sequence of edit operations is %s.\n", ops);

	return EXIT_SUCCESS;
}
/*
           c    o    p    y    w    r    i    t    e
-----------------------------------------------------
 |    0    1    2    3    4    5    6    7    8    9
c|    1    0    1    2    3    4    5    6    7    8
o|    2    1    0    1    2    3    4    5    6    7
p|    3    2    1    0    1    2    3    4    5    6
y|    4    3    2    1    0    1    2    3    4    5
r|    5    4    3    2    1    1    1    2    3    4
i|    6    5    4    3    2    2    2    1    2    3
g|    7    6    5    4    3    3    3    2    2    3
h|    8    7    6    5    4    4    4    3    3    3
t|    9    8    7    6    5    5    5    4    3    4

Levenshtein distance between copyright and copywrite is 4.
Sequence of edit operations is >>>>D>>IRR.


           e    f    f    o    r    t
--------------------------------------
 |    0    1    2    3    4    5    6
a|    1    1    2    3    4    5    6
f|    2    2    1    2    3    4    5
f|    3    3    2    1    2    3    4
e|    4    3    3    2    2    3    4
c|    5    4    4    3    3    3    4
t|    6    5    5    4    4    4    3

Levenshtein distance between affect and effort is 3.
Sequence of edit operations is R>>RR>.

 *
 */
/*
 *            a    a    b    a    a    b
--------------------------------------
 |    0    1    2    3    4    5    6
a|    1    0    1    2    3    4    5
b|    2    1    1    1    2    3    4
b|    3    2    2    1    2    3    3
a|    4    3    2    2    1    2    3
a|    5    4    3    3    2    1    2
b|    6    5    4    3    3    2    1

i = 6, j = 6, oplen = 0
i = 5, j = 5, oplen = 1
i = 4, j = 4, oplen = 2
i = 3, j = 3, oplen = 3
i = 2, j = 2, oplen = 4
i = 1, j = 1, oplen = 5
Levenshtein distance between abbaab and aabaab is 1.
Sequence of edit operations is >R>>>>.
 *
 */
