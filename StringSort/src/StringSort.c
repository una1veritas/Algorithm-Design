/*
 * 文字列の配列のソートプログラム：入出力部の参考
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef char* string;

/* 全順序関係（関数），ソート関数　の型宣言，本体の定義など */

int compare_str(const void *a, const void *b) {
	/* a, b ともに配列の要素(string)へのポインタ */
    return strcmp(*(string*) a, *(string*) b) ;
}

char * convert(char * s, char * t) {
	char * ptr = s;
	char * outp = t;
	char c;

	do {
		c = *ptr++;
		switch( tolower(c) ) {
		case 'a':
			*outp++ = '1';
			break;
		case 'i':
			*outp++ = '2';
			break;
		case 'u':
			*outp++ = '3';
			break;
		case 'e':
			*outp++ = '4';
			break;
		case 'o':
			*outp++ = '5';
			break;
		case 'k':
			*outp++ = 'A';
			break;
		case 's':
		case 'z':
		case 'j':
			*outp++ = 'B';
			if ( *ptr == 'h' ) {
				ptr++;
			}
			break;
		case 't':
			*outp++ = 'C';
			if ( *ptr == 's' ) {
				ptr++;
			}
			break;
		case 'c':
			*outp++ = 'C';
			if ( *ptr == 'h' ) {
				ptr++;
			}
			break;
		case 'n':
			if ( *ptr == 'a' || *ptr == 'i' || *ptr == 'u' || *ptr == 'e' || *ptr == 'o' ) {
				*outp++ = 'D';
			} else {
				*outp++ = 'Z';
				if ( *ptr == 'n' || *ptr == '-' || *ptr == '\'' )
					ptr++;
			}
			break;
		case 'h':
		case 'b':
			*outp++ = 'E';
			break;
		case 'm':
			*outp++ = 'F';
			break;
		case 'y':
			*outp++ = 'G';
			break;
		case 'r':
			*outp++ = 'H';
			break;
		case 'w':
			*outp++ = 'I';
			break;
		default:
			*outp++ = '\0';
			break;
		}
	} while ( c != '\0');
	return t;
}


int main(int argcount, string argval[]) {

	int number = argcount - 1;
	string *sarray = argval+1;
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
		printf("%d: %s (%s)\n", i, sarray[i], convert(sarray[i], buf) );
	}
	printf("\n");

	return EXIT_SUCCESS;
}
