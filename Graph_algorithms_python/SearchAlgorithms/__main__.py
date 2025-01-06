'''
Created on 2019/12/23

@author: sin
'''
# Breadth First Search example program
# example execution:
# python3 BreadthFirstSearch.py "{1, 2, 3, 4, 5, 6}" "{(1, 2), (2, 3), (1, 4), (3, 4), (4, 5), (2,6), (3, 6)}" 1
import sys

def adjacent_points(G, point):
    (V, E) = G
    N = set()
    for (v, w) in E:
        if v == point :
            N.add(w) # the other (2nd) end point
        elif w == point :
            N.add(v)  # the 1st end point
    return sorted(list(N))

def BreadthFirstSearch(G, start, show = False):
    (V, E) = G
    E_T = set()
    Q = [ start ]  # the initial front line
    U = set() 
    if start in V :
        U.add(start)
    # print(d, que)
    while len(Q) != 0 :
        if show: print('Q = '+str(Q) + ', U = '+str(U)) # show the current front line 
        v = Q.pop(0)
        for w in adjacent_points(G, v) :
            # print( (v, w) )
            if w in U : 
                continue
            U.add(w)
            Q.append(w)
            E_T.add( (v,w) )
    return (V, E_T)

def DepthFirstSearch(G, start, do_vertex = None, do_edge = None):
    (V, E) = G
    E_T = set()         #最初に訪問した時のパスをまとめた木
    visited = set()     # 訪問済みの点の集合
    S = [ start ]       # 探索パスを表す列（スタック）
    if start not in V :
        return None     # エラー
    while len(S) != 0 :
        v = S[-1] # 訪問する点を v として参照
        if v not in visited and callable(do_vertex) : 
            do_vertex(v)
        visited.add(v)
        for w in adjacent_points(G, v):
            if (v,w) not in E_T and (w,v) not in E_T :
                if callable(do_edge) : 
                    do_edge( (v, w) )
            if w not in visited :
                S.append(w)
                E_T.add( (v,w) )
        if S[-1] == v :
            S.pop()
    return (V, E_T)

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
G = (V, E)
#確認のためグラフを表示
print('G='+str(G)+', start = ' + str(s))

def prn(v):
    print(v)
#計算し，得られた木を表示
print('\nDepth First Search:')
print('DFS Tree =', DepthFirstSearch(G, s, do_vertex=lambda v: print('visited ', v), do_edge=lambda e: print('checked', e)))
