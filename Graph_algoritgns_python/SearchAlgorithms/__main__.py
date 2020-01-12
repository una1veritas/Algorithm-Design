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

def DepthFirstSearch(G, start, show = False):
    (V, E) = G
    E_T = set()
    U = set()
    S = [ start ]
    if start in V :
        U.add(start)
    while len(S) != 0 :
        if show: print('S = '+str(S) + ', U = '+str(U)) # show the current front line 
        v = S[-1] # pop the last element
        for w in adjacent_points(G, v):
            if w not in U :
                U.add(w)
                S.append(w)
                print( (v, w) )
                E_T.add( (v,w) )
                break
        else:
            S.pop()
    return (V, E_T)

#入力を集合として解釈
V = eval(sys.argv[1])
E = eval(sys.argv[2])
if len(sys.argv) > 3 :
    s = eval(sys.argv[3])
else:
    s = sorted(list(V))[0]
#グラフを定義（G に (V, E) を代入）
G = (V, E)

#確認のためグラフを表示
print('G='+str(G)+', start = ' + str(s))

#計算し，得られた木を表示
print('\nDepth First Search:')
print('DFS Tree =', DepthFirstSearch(G, s, True))
print('\nBreadth First Search:')
print('BFS Tree =', BreadthFirstSearch(G, s, True))
