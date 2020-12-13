'''
Created on 2020/01/14

@author: sin
'''

import sys

def cc_root(ccparent, v):
    # find the root and update the parent = the root
    parent = ccparent[v]
    while ccparent[parent] != parent :
        parent = ccparent[parent]
    else:
        ccparent[v] = parent
    return parent

def cc_connect(ccparent, u, v):
    if cc_root(ccparent, u) < cc_root(ccparent, v) :
        ccparent[ccparent[v]] = ccparent[u]
    else:
        ccparent[ccparent[u]] = ccparent[v]
#入力を点集合と重み付き辺（辞書）として解釈
if len(sys.argv) == 4 : 
    #引数から入力を得る場合
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
G = (vertices, edges)
print('G =',G)
print('w =',weight)

# 重みの昇順でソート
q = sorted(weight.items(), key=lambda elem:elem[1])

#最小領域木を計算
ccparent = dict()
for i in vertices:
    ccparent[i] = i  # the root is itself
treeedges = set()
for (anedge, aweight) in q:
    (u, v) = anedge
    # check wether u and v are in the same connected components
    if cc_root(ccparent, u) != cc_root(ccparent, v) :
        treeedges.add(anedge)
        #merge the components
        cc_connect(ccparent, u, v)
        print(ccparent)

print("Et = ", treeedges)
