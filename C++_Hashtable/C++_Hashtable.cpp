#include <stdio.h>
#include <list>  // 双方向連結リストの C++ 標準ライブラリ
#include <algorithm>
#include <string>
// std:: は, 上記 list のほか C++ 標準ライブラリのものであることを指示します．

unsigned int hash(int d) {
	return d;  // 整数のハッシュ値は，その値そのもの．
}

int main(int argc, char **argv) {
	if ( argc <= 1 ) {
		printf("input numbers as arguments.\n");
		return 1; // エラー終了
	}

	int m = 11;
	std::list<int> table[m];  // 初期化はリストの宣言時に行われる
	int i;
	std::list<int>::iterator p, end;
	// iterator は，リストの要素をたぐるためのポインタのようなもの．

	// データの追加
	for(i = 1; i < argc; ++i) {
		int d = std::stoi(argv[i]);
		p = table[hash(d) % m].begin();
		end = table[hash(d) % m].end();
		if ( std::find(p, end, d) == end ) {  // 要素の探索．== end なら含まない
			table[hash(d) % m].push_back(d);  // リストへの追加
			printf("%d を追加.\n", d);
		} else {
			printf("%d はすでにある.\n", d);
		}
	}

	// table のデータ格納状況の表示
	for(i = 0; i < m; ++i) {
		printf("%d : ", i);
		for(p = table[i].begin(); p != table[i].end(); ++p )
			printf("%d, ", *p);
		printf("\n");
	}

	printf("終了.\n");

	return 0;
}
