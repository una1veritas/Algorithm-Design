#include <iostream>
#include <list>  // 双方向連結リストの C++ 標準ライブラリ
#include <algorithm>
#include <string>
// std:: は, 上記 list のほか C++ 標準ライブラリのものであることを指示します．

unsigned int hash(int d) {
	return d;  // 整数のハッシュ値は，その値そのもの．
}

/*
unsigned int hash(char idstr[]) {
     unsigned int hv = 0;
     for(int i = 4; i > 0; --i) {
          hv <<= 7;
          hv += idstr[i] ^ idstr[3+i];
     }
     return hv;
}
*/

int main(int argc, char **argv) {
	if ( argc <= 1 ) {
		printf("input table size as arguments.\n");
		return 1; // エラー終了
	}

	int m = 11;
	int argpos = 1;
	std::string argstr = argv[argpos];
	if ( argstr.starts_with("-size=") ) { // requires C++ 20 ( -std=c++2a )
		m = std::stoi(argstr.substr(std::strlen("-size=")));
		++argpos;
	}
	std::list<int> table[m];  // 初期化は宣言時に行われるので不要
	// データの追加
	for( ; argpos < argc; ++argpos) {
		int d = std::stoi(argv[argpos]);
		table[hash(d) % m].push_back(d);  // リストへの追加
		std::cout << d << " を追加." << std::endl;
	}
	std::cout << "bucket size = " << m << std::endl;

	// table のデータ格納状況の表示
	for(int i = 0; i < m; ++i) {
		std::cout << i << ": ";
		// リストの要素を一つずつたぐる．
		// iterator は，リストの要素をたぐるためのポインタのようなもの．
		std::cout << "(";
		for(auto & d : table[i]) {
			std::cout << d << ", ";
		}
		std::cout << ")" << std::endl;
	}

	// 11 を検索, 削除
	int key = 11;
	int i = hash(key) % m;
	auto p = table[i].begin();
	for( ; p != table[i].end() and *p != key ; ++p) ;
	if ( p == table[i].end() ) {
		std::cout << "含まない" << std::endl;
	} else {
		std::cout << "含む" << std::endl;
		table[i].erase(p);
		std::cout << "削除" << std::endl;
	}

	std::cout << "すべて終了" << std::endl;

	return 0;
}
