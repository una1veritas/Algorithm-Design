'''
Created on 2019/12/23

@author: sin
'''
# Breadth First Search example program
# example execution:
# python3 BreadthFirstSearch.py "{1, 2, 3, 4, 5, 6}" "{(1, 2), (2, 3), (1, 4), (3, 4), (4, 5), (2,6), (3, 6)}" 1
import sys
from collections import deque

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
    ''' initialization '''
    tree = Graph(G.vertices, {})    # 根は start
    schedule = deque()              # 訪問予約の列
    checked = set()                 # 訪問済みまたは訪問予約済みの点
    edges_checked = set()           # 訪問済みの辺
    schedule.append(start)      # push the initial vertex
    checked.add(start)
    
    '''search loop'''
    while schedule : # while schedule is not empty
        print(f'schedule = {schedule}, \nchecked = {checked}\n')
        v = schedule.popleft()
        if callable(do_vertex) : 
            do_vertex(v)  # v を訪問して必要な作業を実行
        for w in sorted(G.adjacent_points(v)) :
            if (v, w) not in edges_checked and (w, v) not in edges_checked :
                if callable(do_edge) : 
                    do_edge( (v, w) )
                edges_checked.add( (v, w) )
            if w not in checked : 
                schedule.append(w)
                checked.add(w)
                tree.add_edge(v, w)
    return tree

def DepthFirstSearch(G, start, do_vertex = None, do_edge = None):
    tree = Graph(G.vertices, {})         # 各点に最初に到達した時の道の辺をまとめた木
    visited = set()         # 訪問済みの点
    path = deque()      # 訪問履歴の列（末尾がわからスタックとして利用）
    edges_checked = set()
    
    if callable(do_vertex) : 
        do_vertex(start)    # v を訪問．先がけ順での実行
    path.append( start )    # 訪問済みの点を path に push
    visited.add(start)
    while path :  # while history is not empty
        print(f'path = {path}')
        v = path[-1]    # 訪問履歴の最後の要素を見る（削除はしない）
        nx = None   # 次に訪問する点
        for w in sorted(G.adjacent_points(v)) :
            if (v, w) not in edges_checked and (w, v) not in edges_checked:
                if callable(do_edge) : 
                    do_edge( (v, w) )
                edges_checked.add( (v, w) )
            if w in visited :
                continue
            nx = w
            break
        if nx != None :
            # 未訪問の隣接点
            if callable(do_vertex) : 
                do_vertex(nx)    # v を訪問．先がけ順での実行
            visited.add(nx)      # v は訪問済み
            path.append(nx)
            tree.add_edge(v, nx)
        else:
            path.pop()
                        
    return tree

#"{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}" "{('a','c'), ('a', 'e'), ('a', 'd'), ('b', 'c'), ('b', 'h'), ('c', 'd'), ('c', 'h'), ('d', 'h'), ('e', 'f'), ('e', 'g'), ('e', 'h')}" "'a'"
# "{'s', 'a', 'b', 'c', 'd', 'e', 'f', 'g'}" "{('s','a'), ('s', 'c'), ('a', 'b'), ('c', 'd'), ('c', 'e'), ('d', 'e'), ('d', 'f'), ('e', 'f'), ('e', 'g'), ('f', 'g')}" "'s'"

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

#計算し，得られた木を表示
print('\nBreadth First Search:')
print('BFS Tree =', BreadthFirstSearch(G, s, do_vertex=lambda v: print(f'visiting {v}'), do_edge=lambda e: print(f'{e}')))
print('\nDepth First Search:')
print('DFS Tree =', DepthFirstSearch(G, s, do_vertex=lambda v: print(f'visiting {v}'), do_edge=lambda e: print(f'{e}')))
