#include <stdio.h>
#include <list>  // 双方向連結リストの C++ 標準ライブラリ

// std:: は, 上記 list のほか C++ 標準ライブラリのものであることを指示します．

unsigned int hash(int d) {
	return d;  // 整数のハッシュ値は，その値そのもの．
}

int main(int argc, char **argv) {
	if ( argc <= 1 ) {
		printf("input numbers as arguments.\n");
		return 1; // エラー終了
	}

	int m = 7;
	std::list<int> table[m];
	// 初期化 --- STL の list は宣言時に初期化されるので本来は不要
	for(int i = 0; i < m; ++i)
		table[i].clear();

	// データの追加
	for(int i = 1; i < argc; ++i) {
		int d = std::atoi(argv[i]);
		table[hash(d) % m].push_back(d);  // リストへの追加
		printf("%d を追加.\n", d);
	}

	// table のデータ格納状況の表示
	for(int i = 0; i < m; ++i) {
		printf("%d : ", i);
		// リストの要素を一つずつたぐる．
		// iterator は，リストの要素をたぐるためのポインタのようなもの．
		for(std::list<int>::iterator p = table[i].begin(); p != table[i].end(); ++p) {
			printf("%d, ", *p);
		}
		printf("\n");
	}

	//
	printf("終了.\n");

	return 0;
}
