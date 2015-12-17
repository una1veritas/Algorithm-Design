/*
 * 文字列の配列のソートプログラム：入出力部の参考
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* string;

/* 全順序関係（関数），ソート関数　の型宣言，本体の定義など */

int compare_str(const void *a, const void *b) {
	/* a, b ともに配列の要素(string)へのポインタ */
    return strcmp(*(string*) a, *(string*) b) ;
}

int main(int argcount, string argval[]) {

	int number = argcount - 1;
	string *sarray = argval+1;

	printf("totally %d words.\n",number);
	for(int i = 0; i < number; i++) {
		printf("%d: %s\n", i, sarray[i]);
	}
	printf("\n");

	/* stdlib の qsort ライブラリ関数を使ってソートする例 */

	qsort(sarray, number, sizeof( string ), compare_str);

	printf("sorted:\n");
	for(int i = 0; i < number; i++) {
		printf("%d: %s\n", i, sarray[i]);
	}
	printf("\n");

	return EXIT_SUCCESS;
}
