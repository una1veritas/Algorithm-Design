プログラムのコンパイル，実行のしかた (202/12/27)

(1) コンパイルと入力の与え方
Kruskal のアルゴリズムの部分のオリジナルは Kruskal’s Minimum Spanning Tree Algorithm | Greedy Algo-2
 - GeeksforGeeks で，
オリジナルの単純辺重み付きグラフを対象として動作する真剣な Set union-find を使ったC言語
での実装として手を加えたもの．

まずCコンパイラでコンパイルする．
% make

または
% gcc -std=c11 -o kruskal.exe Graph_algorithms.c SimpleGraph.c UnionFind.c kruskal.c
% ls
   ...
   kruskal.exe
   ...
実行形式ファイル kruskal.exe の名前はなんでもよい
実行　（linux, Msys64/MinGW の場合）
% ./kruskal.exe  "0, 1, 2, 3" "0-1:10, 0-2:6, 0-3: 5, 1 - 3 : 15, 2 - 3: 4"
実行　（windows プロンプトの場合）
C:\(省略)>.\kruskal.exe "0, 1, 2, 3" "0-1:10, 0-2:6, 0-3: 5, 1 - 3 : 15, 2 - 3: 4"

引数で定義される点数 4 のごく簡単な重み付きグラフの MST が出力されます．
プログラムを簡単にするため点数は最大 16 になっています（SimpleGraph.h の MAX_VERTICES_SIZE で定義）．

(2) kruskal.py の実行と入力の与え方
Python バージョンは完全オリジナルの簡易 Set union-find 使用のプログラムです．

Python3 プログラムです．Python 3.x が必要ですが，
プログラミング演習用 VirtualBOX の linux にはインストール済みのようです．
プログラム内に定義されたグラフを入力として実行
% python3 kruskal.py

グラウ G, 重み関数（python の辞書型を利用），
最小全域木の計算過程，最小全域木の辺集合 Et が出力されます．

入力をコマンドの引数で与えることもできます．
例
% python3 kruskal.py  "[1, 2, 3, 4]" "{(1,2): 3, (2,3): 2, (3,4): 7, (1,4): 2, (1,3): 2}"
reading arg vales.
G = ([1, 2, 3, 4], {(1, 2), (3, 4), (1, 4), (2, 3), (1, 3)})
w = {(1, 2): 3, (2, 3): 2, (3, 4): 7, (1, 4): 2, (1, 3): 2}
(2, 3)
{1: 1, 2: 2, 3: 2, 4: 4}
(1, 4)
{1: 1, 2: 2, 3: 2, 4: 1}
(1, 3)
{1: 1, 2: 2, 3: 1, 4: 1}
(1, 2)
{1: 1, 2: 1, 3: 1, 4: 1}
Et =  {(2, 3), (1, 2), (1, 3), (1, 4)}
%