'''
Created on 2020/01/14

@author: sin
'''

import sys

def unionfind_init(vertices):
    parent = dict()
    for v in vertices:
        parent[v] = v
    return parent
    
def unionfind_find(parent, v):
    # find the root and update the parent = the root
    while parent[v] != parent[parent[v]] :
        parent[v] = parent[parent[v]]
        v = parent[v]
    return parent[v]

def unionfind_union(parent, u, v):
    urep = unionfind_find(parent, u)
    vrep = unionfind_find(parent, v) 
    if urep < vrep :
        parent[vrep] = parent[urep]
    else:
        parent[urep] = parent[vrep]

#入力を点集合と重み付き辺（辞書）として解釈
if len(sys.argv) == 3 : 
    #引数から入力を得る場合
    print('reading arg vales.')
    vstr = sys.argv[1]
    westr = sys.argv[2]
else:
    #プログラム内（ココ）で与える場合
    vstr = "['a', 'b', 'c', 'd', 'e', 'f', 'g']"
    westr = "{('a', 'e'): 10, ('a', 'b'): 3, ('b', 'e'): 6, ('b', 'c'): 5, ('c', 'd'): 4, ('c', 'g'): 7, ('d', 'e'): 2, ('d', 'f'): 1, ('e', 'f'): 2, ('f', 'g'): 4}"

vertices = eval(vstr)
weight = eval(westr)
edges = set(weight.keys())

#グラフを定義（G に (V, E) を代入）
a_graph = (vertices, edges)
print('G =', a_graph)
print('w =', weight)

# 重みの昇順でソート
q = sorted(weight.items(), key=lambda elem:elem[1])

#最小領域木を計算
ufparent = unionfind_init(vertices)
tree_edges = set()
for (anedge, aweight) in q:
    (u, v) = anedge
    # check wether u and v are in the same connected components
    if unionfind_find(ufparent, u) != unionfind_find(ufparent, v) :
        tree_edges.add(anedge)
        print(anedge)
        #merge the components
        unionfind_union(ufparent, u, v)
        print(ufparent)

print("Et = ", tree_edges)
