//============================================================================
// Name        : STL-sample.cpp
// Author      : Sin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
// set implemented by red-black tree
#include <set>
// variable-length array
#include <vector>

// std:: という std （C++標準）ライブラリの前書きを省略する
using namespace std;

int main(int argc, char * argv[]) {
	set<int> intset; 			// set of ints.

	for(int i = 0; i < 10; ++i) {
		intset.insert(rand() % 10000);
	}

	for(set<int>::iterator i = intset.begin(); i != intset.end(); ++i ) {
		printf("%d, ", *i);
	}
	printf("\n\n");

	set<vector<int> > vecset; 	// 整数の列（を表す vector ）の集合

	vector<int> args; 	// プログラム main の引数を整数の列として解釈して vector を作る
	for(int i = 1; i < argc; ++i) {
		long t = strtol(argv[i], NULL, 10);
		args.push_back((int)t);
	}
	vecset.insert(args);

	for(int i = 0; i < 10; ++i) {
		vector<int> vec;
		for(int j = 0; j < i + 1; ++j)
			vec.push_back(rand() % 100);
		vecset.insert(vec);
	}

	// iterator はコンテナ（データの入れ物）型の要素を指すポインタのようなもの。
	// 要素に順序を持たないコンテナでも、要素を枚挙する順序で begin() で最初の要素を指し、
	// end() に等しくなると枚挙を終えている。
	for(set<vector<int> >::iterator i = vecset.begin(); i != vecset.end(); ++i ) {
		for (vector<int>::const_iterator v = i->begin(); v != i->end(); ++v) {
			printf("%d, ", *v);
		}
		printf(";\n");
	}
	printf("\n");

	// iterator は要素を見つけたり、削除する場合にも要素を指すポインタのように使う。
	// set<vector<int> >::iterator あるいは set<vector<int> >::const_iterator
	// は長ったらしいので、C++11 で取り入れられた、拡張の型を自動で推定し決定する auto
	// 型を使うと短くかける。
	// C の記憶タイプ（メモリか、レジスタかなど）を自動決定する auto 修飾はなくなっている。
	auto i = vecset.find(args);
	if ( i != vecset.end() ) { 	// i == vecset.end() のとき，見つからなかった
		printf("found!\n");
		for (auto j = i->begin(); j != i->end(); ++j) {
			printf("%d, ", *j);
		}
		printf(";\n");
	}
	return 0;
}
