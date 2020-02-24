'''
Created on 2020/01/14

@author: sin
'''

import sys

vertices = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l']
edges = [('a', 'b'), ('a', 'e'), ('a', 'i'), ('b', 'c'), ('b', 'f'), ('c', 'd'), ('c', 'f'), ('c', 'g'), ('d', 'h'), ('e', 'f'), ('e', 'i'), ('f', 'g'), ('f', 'j'), ('g', 'h'), ('g', 'k'), ('g', 'l'), ('h', 'l'), ('i', 'j'), ('j', 'k'), ('k', 'l')]
eweight = {('a', 'e'): 17, ('a', 'b'): 5, ('a', 'i'): 19, ('b', 'c'): 11, ('b', 'f'): 10, ('c', 'f'): 6, ('c', 'd'): 15, ('c', 'g'): 9, ('d', 'h'): 4, ('e', 'f'): 16, ('e', 'i'): 28, ('f', 'g'): 1, ('f', 'j'): 18, ('g', 'h'): 13, ('g', 'k'): 26, ('g', 'l'): 27, ('h', 'l'): 12, ('i', 'j'): 8, ('j', 'k'): 2, ('k', 'l'): 24}

def adjacents(G, point):
    E = G[1]
    neighbors = set()
    for (v, w) in E:
        if v == point :
            neighbors.add(w) # the other (2nd) end point
        elif w == point :
            neighbors.add(v)  # the 1st end point
    return neighbors

#入力を集合として解釈
#V = set(eval(sys.argv[1]))
V = set(vertices)
print(V)
#E = set(eval(sys.argv[2]))
E = set(edges)
print(E)
#w = dict(eval(sys.argv[3]))
w = eweight
print(w)
#s = eval(sys.argv[4])
#g = eval(sys.argv[5])

#グラフを定義（G に (V, E) を代入）
G = (V, E)
print('G='+str(G))
elist = sorted(w.items(), key=lambda e:e[1])
print(elist)
#計算し，得られた木を表示

# ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'],
# [('a', 'b'), ('a', 'e'), ('a', 'i'), ('b', 'c'), ('b', 'f'), ('c', 'd'), ('c', 'f'), ('c', 'g'), ('d', 'h'), ('e', 'f'), ('e', 'i'), ('f', 'g'), ('f', 'j'), ('g', 'h'), ('g', 'k'), ('g', 'l'), ('h', 'l'), ('i', 'j'), ('j', 'k'), ('k', 'l')], 
# {('a', 'e'): 17, ('a', 'b'): 5, ('a', 'i'): 19, ('b', 'c'): 11, ('b', 'f'): 10, ('c', 'f'): 6, ('c', 'd'): 15, ('c', 'g'): 9, ('d', 'h'): 4, ('e', 'f'): 16, ('e', 'i'): 28, ('f', 'g'): 1, ('f', 'j'): 18, ('g', 'h'): 13, ('g', 'k'): 26, ('g', 'l'): 27, ('h', 'l'): 12, ('i', 'j'): 8, ('j', 'k'): 2, ('k', 'l'): 24})
