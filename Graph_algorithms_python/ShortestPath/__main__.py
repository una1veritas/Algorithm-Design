'''
Created on 2020/01/14

@author: sin
'''

import sys

def adjacents(G, point):
    E = G[1]
    neighbors = set()
    for (v, w) in E:
        if v == point :
            neighbors.add(w) # the other (2nd) end point
        elif w == point :
            neighbors.add(v)  # the 1st end point
    return neighbors

def Dijkstra(G, weight, start, goal, show = True):
    V = G[0]
    ell = dict()
    for v in V:
        ell[v] = sys.maxsize
    ell[start] = 0
    P = set()
    while ( len(V - P) > 0 ):
        u = min(V-P, key=lambda v: ell[v])
        P.add(u)
        for v in adjacents(G, u) & (V-P):
            if (u,v) in weight :
                e = (u,v)
            else:
                e = (v, u)
            if ell[v] > ell[u] + weight[e] :
                ell[v] = ell[u] + weight[e]
    print("ell="+str(sorted(ell.items())))
    spath = list()
    spath.append(goal)
    while spath[0] != start:
        v = spath[0]
        for u in adjacents(G, v):
            if ell[u] > ell[v]:
                continue
            if (u, v) in weight :
                e = (u, v)
            else:
                e = (v, u)
            if ell[v] == ell[u] + weight[e] :
                spath = [u] + spath
                break
        else:
            print("error")
            return []
    return spath
        
#入力を集合として解釈
V = set(eval(sys.argv[1]))
print(V)
E = set(eval(sys.argv[2]))
print(E)
w = dict(eval(sys.argv[3]))
print(w)
s = eval(sys.argv[4])
g = eval(sys.argv[5])

#グラフを定義（G に (V, E) を代入）
G = (V, E)

#確認のためグラフを表示
print('G='+str(G)+',\nstart = ' + str(s))

#計算し，得られた木を表示
shortestpath = Dijkstra(G,w,s,g)
print("shortest path = " + str(shortestpath))

#"{1,2,3,4,5,6}" "{(1,2), (1,3), (2,3), (2,4), (2,5), (3,5), (4,5), (4,6), (5,6)}" "{(1,2):5, (1,3):1, (2,3):3, (2,4):4, (2,5):2, (3,5):6, (4,5):3, (4,6):2, (5,6):1}" 1 6
#{1, 2, 3, 4, 5, 6}
#{(2, 4), (1, 2), (4, 6), (2, 3), (4, 5), (5, 6), (2, 5), (1, 3), (3, 5)}
#{(1, 2): 5, (1, 3): 1, (2, 3): 3, (2, 4): 4, (2, 5): 2, (3, 5): 6, (4, 5): 3, (4, 6): 2, (5, 6): 1}
#G=({1, 2, 3, 4, 5, 6}, {(2, 4), (1, 2), (4, 6), (2, 3), (4, 5), (5, 6), (2, 5), (1, 3), (3, 5)}), start = 1
#ell={1: 0, 2: 4, 3: 1, 4: 8, 5: 6, 6: 7}
#shortest path = [1, 3, 2, 5, 6]

"['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l']"
"[('a', 'b'), ('a', 'e'), ('a', 'i'), ('b', 'c'), ('b', 'f'), ('c', 'd'), ('c', 'f'), ('c', 'g'), ('d', 'h'), ('e', 'f'), ('e', 'i'), ('f', 'g'), ('f', 'j'), ('g', 'h'), ('g', 'k'), ('g', 'l'), ('h', 'l'), ('i', 'j'), ('j', 'k'), ('k', 'l')]"
"{('a', 'e'): 17, ('a', 'b'): 5, ('a', 'i'): 19, ('b', 'c'): 11, ('b', 'f'): 20, ('c', 'f'): 6, ('c', 'd'): 15, ('c', 'g'): 9, ('d', 'h'): 4, ('e', 'f'): 16, ('e', 'i'): 28, ('f', 'g'): 1, ('f', 'j'): 3, ('g', 'h'): 13, ('g', 'k'): 26, ('g', 'l'): 7, ('h', 'l'): 12, ('i', 'j'): 9, ('j', 'k'): 2, ('k', 'l'): 24}"
"'a'"
"'k'"
