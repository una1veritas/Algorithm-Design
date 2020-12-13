'''
Created on 2020/01/14

@author: sin
'''

import sys

def adjacents(G, point):
    (V, E) = G
    neighbors = set()
    for (v, w) in E:
        if v == point :
            neighbors.add(w) # the other (2nd) end point
        elif w == point :
            neighbors.add(v)  # the 1st end point
    return neighbors

#入力を集合として解釈

if len(sys.argv) == 4 : 
    #引数から入力を得る場合
    vertices = set(eval(sys.argv[1]))
    edges = set(eval(sys.argv[2]))
    weights = dict(eval(sys.argv[3]))
else:
    #プログラム内（ココ）で与える場合
    vertices = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l']
    edges = [('a', 'b'), ('a', 'e'), ('a', 'i'), ('b', 'c'), ('b', 'f'), ('c', 'd'), ('c', 'f'), ('c', 'g'), ('d', 'h'), ('e', 'f'), ('e', 'i'), ('f', 'g'), ('f', 'j'), ('g', 'h'), ('g', 'k'), ('g', 'l'), ('h', 'l'), ('i', 'j'), ('j', 'k'), ('k', 'l')]
    weight = {('a', 'e'): 17, ('a', 'b'): 5, ('a', 'i'): 19, ('b', 'c'): 11, ('b', 'f'): 10, ('c', 'f'): 6, ('c', 'd'): 15, ('c', 'g'): 9, ('d', 'h'): 4, ('e', 'f'): 16, ('e', 'i'): 28, ('f', 'g'): 1, ('f', 'j'): 18, ('g', 'h'): 13, ('g', 'k'): 26, ('g', 'l'): 27, ('h', 'l'): 12, ('i', 'j'): 8, ('j', 'k'): 2, ('k', 'l'): 24}

#グラフを定義（G に (V, E) を代入）
G = (vertices, edges)
print('G =',G)
print('w =',weight)

# 重みの昇順でソート
q = sorted(weight.items(), key=lambda elem:elem[1])

#最小領域木を計算
ccompos = dict()
for i in vertices:
    ccompos[i] = i
tedges = set()
for (anedge, aweight) in q:
    (u, v) = anedge
    if ccompos[u] != ccompos[v] :
        tedges.add(anedge)
        if ccompos[u] > ccompos[v] :
            (u, v) = (v, u)
        print(u,v)
        vrep = ccompos[v]
        for i in vertices:
            if ccompos[i] == vrep:
                ccompos[i] = ccompos[u]
        print(ccompos)
