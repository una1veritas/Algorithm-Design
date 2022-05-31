#include <stdio.h>
#include <list>  // 双方向連結リストの C++ 標準ライブラリ
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
	std::list<int> table[m];  // 初期化は宣言時に行われるので不要

	// データの追加
	for(int i = 1; i < argc; ++i) {
		int d = std::stoi(argv[i]);
		table[hash(d) % m].push_back(d);  // リストへの追加
		printf("%d を追加.\n", d);
	}

	// table のデータ格納状況の表示
	for(int i = 0; i < m; ++i) {
		printf("%d : ", i);
		// リストの要素を一つずつたぐる．
		// iterator は，リストの要素をたぐるためのポインタのようなもの．
		for(auto & d : table[i]) {
			printf("%d, ", d);
		}
		printf("\n");
	}

	// 11 を検索, 削除
	int key = 11;
	int i = hash(key) % m;
	auto p = table[i].begin();
	for( ; p != table[i].end() and *p != key ; ++p) ;
	if ( p == table[i].end() ) {
		printf("含まない\n");
	} else {
		printf("含む\n");
		table[i].erase(p);
		printf("削除\n");
	}
	printf("終了.\n");

	return 0;
}
