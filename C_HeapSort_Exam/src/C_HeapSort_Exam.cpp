//============================================================================
// Name        : C_HeapSort_Exam.cpp
// Author      : Sin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

using namespace std;

void down_to_leaf(string a[], int i /* 注目するノードの添え字*/, int n /* ヒープのサイズ*/) {
	int child; // 注目する子ノードの添え字
	int r_child; // child の右の兄弟ノードの添え字
	while ((child = i*2 + 1) < n) { // とりあえず注目する子ノードを左の子とする．
		/* printf("%d, %d\n", i, child); */
		r_child = (i+1)*2;
		if ((r_child < n) and !(a[r_child] <= a[child])) {
			child = r_child; // 右の子が存在し，さらに右の子のほうが後である場合
		}
		if (! (a[child] <= a[i]) ) {
			string tmp = a[child];
			a[child] = a[i];
			a[i] = tmp;
		} else
			break;
		i = child;
	}
}

void max_heapify(string a[], int n) {
	for(int i = (n-1)/2; i >= 0; --i) {
		printf("i = %d,\n",i);
		down_to_leaf(a, i, n);
	}
}

int main(int argc, const char * argv[]) {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	int n = argc - 1;
	string * a = new string[n];
	for(int src = 1, dst = 0; src < argc; ++src, ++dst) {
		a[dst] = string(argv[src]);
	}

	for(int i = 0; i < n; ++i) {
		cout << i << ": " << a[i] << ", ";
	}
	cout << "\n";

	max_heapify(a, n);//down_to_leaf(a, 0, n);

	for(int i = 0; i < n; ++i) {
		cout << i << ": " << a[i] << ", ";
	}
	cout << "\n";

	string t = a[n-1];
	a[n-1] = a[0];
	a[0] = t;

	down_to_leaf(a, 0, n-1);

	for(int i = 0; i < n; ++i) {
		cout << i << ": " << a[i] << ", ";
	}
	cout << "\n";

	delete [] a;
	return 0;
}
