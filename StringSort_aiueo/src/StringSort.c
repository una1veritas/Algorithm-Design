/*
 * 文字列の配列のソートプログラム：入出力部の参考
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char* string;

static char * kanareg(char * s, char * t);
static int compare_str(const void *a, const void *b);
int isvowel(char c);

/* 全順序関係（関数），ソート関数　の型宣言，本体の定義など */


static int compare_str(const void *a, const void *b) {
	/* a, b ともに配列の要素(string)へのポインタ */
	char ta[32], tb[32];
	kanareg(*(string*) a, ta);
	kanareg(*(string*) b, tb);
    return strcmp(ta, tb) ;
}

int isvowel(char c) {
	switch(tolower(c)) {
	case 'a':
	case 'i':
	case 'u':
	case 'e':
	case 'o':
		return 1;
		break;
	}
	return 0;
}

int code50(char * t) {
	static char transtable[][2] =
		{ {'a', '1'}, {'i', '2'}, {'u', '3'}, {'e', '4'}, {'o', '5'},
		{'@', 'A'}, {'k', 'B'}, {'s', 'C'}, {'t', 'D'}, {'n', 'E'},
		{'h', 'F'}, {'m', 'G'}, {'y', 'H'}, {'r', 'I'}, {'w', 'J'}, {'n', 'K'},
		{'\0', '\0'},
	};
	int i;

	while( *t != '\0' ) {
		for(i = 0; transtable[i][0]; i++) {
			if ( *t == transtable[i][0] ) {
				*t = transtable[i][1];
				break;
			}
		}
		t++;
	}
	*t = '\0';
	return 1;
}

static char * kanareg(char * s, char * t) {
	char * ptr = s;
	char * outp = t;
	char c;

	while ( *ptr != '\0' ) {
		c = tolower(*ptr++);
		//アイウエオ
		if ( isvowel(c) ) {
			*outp++ = '@';
			*outp++ = c;
			continue;
		}

		//ん
		if ( c == 'n' && tolower(*ptr) != 'y' && !isvowel(tolower(*ptr)) ) {
			*outp++ = 'n';
			*outp++ = 'n';
			continue;
		}

		//撥音
		if ( *ptr != 0 && c == *ptr && c != 'n') {
			*outp++ = 't';
			*outp++ = 'u';
			ptr++;
		}

		// カ行・濁音・カ行拗音
		if ( c == 'k' || c == 'g' ) {
			*outp++ = 'k';
			c = tolower(*ptr++);
			if ( c == 'y' ) {
				// y をスキップ
				c = tolower(*ptr++); // c は母音
				*outp++ = 'i';
				*outp++ = 'y';
				*outp++ = c;
			} else {
				*outp++ = c;
			}
			continue;
		}

		// サ行・濁音・サ行拗音
		if ( c == 's' || c == 'z' || c == 'j' ) {
			*outp++ = 's';
			if ( c == 'j' ) {
				if ( tolower(*ptr) != 'i') {
					*outp++ = 'i';
					*outp++ = 'y';
				}
			}
			c = tolower(*ptr++);
			if ( c == 'h' ) {
				// h をスキップ
				c = tolower(*ptr++); // c は母音
				if ( c == 'i') {
					*outp++ = 'i';
				} else {
					*outp++ = 'i';
					*outp++ = 'y';
					*outp++ = c;
				}
			} else {
				*outp++ = c;
			}
			continue;
		}

		// タ行・チ・ツ・濁音・拗音
		if ( c == 't' || c == 'c' || c == 'd' ) {
			*outp++ = 't';
			c = tolower(*ptr++);
			if ( c == 'h' ) {
				c = tolower(*ptr++);
				if ( c == 'i' ) {
					*outp++ = 'i';
				} else if ( c == 'a' || c == 'u' || c == 'o' ) {
					*outp++ = 'i';
					*outp++ = 'y';
					*outp++ = c;
				}
			} else if ( c == 's' ) {
				c = tolower(*ptr++);
				*outp++ = c; // c = 'u'
			} else {
				*outp++ = c;
			}
			continue;
		}
		// ハ・パ行拗音
		if ( c == 'h' || c == 'p' || c == 'b' ) {
			*outp++ = 'h';
			c = tolower(*ptr++);
			if ( c == 'y' ) {
				// y をスキップ
				c = tolower(*ptr++); // c は母音
				*outp++ = 'i';
				*outp++ = 'y';
				*outp++ = c;
			} else {
				*outp++ = c;
			}
			continue;
		}

		*outp++ = c;
		do {
			c = tolower(*ptr++);
			*outp++ = c;
		} while ( !isvowel(c) );
	}
	*outp = '\0';

	//code50(t);
	return t;
}


int main(int argcount, string argval[]) {

	int number = argcount - 1;
	string *sarray = argval + 1;
	unsigned int maxlen = 0;

	printf("totally %d words.\n",number);
	for(int i = 0; i < number; i++) {
		maxlen = ( maxlen > strlen(sarray[i]) ? maxlen : strlen(sarray[i]) );
		printf("%d: %s", i, sarray[i]);
		printf("\n");
	}
	printf("\n");

	char buf[ maxlen+1 ];
	/* stdlib の qsort ライブラリ関数を使ってソートする例 */

	qsort(sarray, number, sizeof( string ), compare_str);

	printf("sorted:\n");
	for(int i = 0; i < number; i++) {
		kanareg(sarray[i], buf);
		printf("%d: %s (%s)\n", i, sarray[i], buf);
	}
	printf("\n");
	return EXIT_SUCCESS;
}
