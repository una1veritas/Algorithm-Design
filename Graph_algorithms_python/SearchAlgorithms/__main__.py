'''
Created on 2019/12/23

@author: sin
'''
# Breadth First Search example program
# example execution:
# python3 BreadthFirstSearch.py "{1, 2, 3, 4, 5, 6}" "{(1, 2), (2, 3), (1, 4), (3, 4), (4, 5), (2,6), (3, 6)}" 1
import sys

class Graph:
    def __init__(self, vertices={}, edges={}):
        self.vertices = set(vertices)
        self.edges = set([tuple(e) for e in edges])
    
    def add_edge(self, u, v):
        self.vertices.add(u)
        self.vertices.add(v)
        self.edges.add( (u, v) )

    def adjacent(self, u, v):
        return (u,v) in self.edges or (v,u) in self.edges
        
    def adjacent_points(self, v):
        adjs = list()
        for u in self.vertices:
            if self.adjacent(u, v) :
                adjs.append(u)
        return adjs
    
    def __str__(self):
        return 'Graph(' + str(self.vertices) + ', ' + str(self.edges) + ') '
    
def BreadthFirstSearch(G, start, do_vertex = None, do_edge = None):
    T = Graph(G.vertices, {})
    Q = list()
    enqueued = set()
    checked = set()
    Q.append(start)  # push the initial front line
    enqueued.add(start)
    while len(Q) != 0 :
        v = Q.pop(0)
        if callable(do_vertex) : 
            do_vertex(v)  # v を訪問．
        for w in G.adjacent_points(v) :
            if (v, w) not in checked and (w, v) not in checked :
                if callable(do_edge) :
                    do_edge( (v, w) )
                checked.add( (v, w) )
            if w not in enqueued : 
                Q.append(w)
                enqueued.add(w)
                T.add_edge(v, w)
    return T

def DepthFirstSearch(G, start, do_vertex = None, do_edge = None):
    T = Graph(G.vertices, {})         # 各点に最初に到達した時の道の辺をまとめた木
    visited = set()     # 訪問済みの点の集合
    S = list()          # 始点からの探索パスを表す列（スタックとして使用）
    S.append( start )   
    while len(S) > 0 :  # == 0 なら S は
        v = S[-1]       # スタックのトップ（最後の要素）を訪問する v として参照
        if v not in visited :
            # 未訪問の場合
            if callable(do_vertex) : 
                do_vertex(v)  # v を訪問．先がけ順での実行となる
            visited.add(v)  # v を訪問済みに
            for w in G.adjacent_points(v):
                if not T.adjacent(v, w) :
                    if callable(do_edge) : 
                        do_edge( (v, w) )
                if w not in visited :
                    S.append(w)
                    T.add_edge(v, w)
        else:
            # 訪問済み（戻ってきたところ）の場合
            S.pop()
    return T

#"{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}" "{('a','c'), ('a', 'e'), ('a', 'd'), ('b', 'c'), ('b', 'h'), ('c', 'd'), ('c', 'h'), ('d', 'h'), ('e', 'f'), ('e', 'g'), ('e', 'h')}" "'a'"
#入力を集合として解釈
V = eval(sys.argv[1])
E = eval(sys.argv[2])
print(V, E)


if len(sys.argv) > 3 :
    s = eval(sys.argv[3])
else:
    s = sorted(list(V))[0]
#グラフを定義（G に (V, E) を代入）
G = Graph(V, E)
#確認のためグラフを表示
print('G='+str(G)+', start = ' + str(s))

def prn(v):
    print(v)
#計算し，得られた木を表示
print('\nBreadth First Search:')
print('BFS Tree =', BreadthFirstSearch(G, s, do_vertex=lambda v: print('visited ', v), do_edge=lambda e: print('checked', e)))
print('\nDepth First Search:')
print('DFS Tree =', DepthFirstSearch(G, s, do_vertex=lambda v: print('visited ', v), do_edge=lambda e: print('checked', e)))
