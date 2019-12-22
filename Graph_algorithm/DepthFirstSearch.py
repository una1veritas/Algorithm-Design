# Depth First Search example program
# example execution:
# python3 DepthFirstSearch.py "{1, 2, 3, 4, 5, 6}" "{(1, 2), (2, 3), (1, 4), (3, 4), (4, 5), (2,6), (3, 6)}" 1
import sys

def adjacent_points(G, point):
    (V, E) = G
    neighbors = set()
    for (v, w) in E:
        if v == point :
            neighbors.add(w) # the other (2nd) end point
        elif w == point :
            neighbors.add(v)  # the 1st end point
    return neighbors

def DepthFirstSearch(G, start, show = False):
    (V, E) = G
    if not start in V :
        print('Error: the starting point '+str(start)+' is not in G.')
        return ()
    E_T = set()
    U = set()
    S = [ start ]
    U.add(start)
    while len(S) != 0 :
        if show: print('S = '+str(S) + ', U = '+str(U)) # show the current front line 
        v = S[-1]
        for w in adjacent_points(G, v):
            if w not in U :
                U.add(w)
                S.append(w)
                E_T.add( (v,w) )
                break
        else:
            S.pop()
    return (V, E_T)

#入力を集合として解釈
V = eval(sys.argv[1])
E = eval(sys.argv[2])
if len(sys.argv) > 3 :
    start_point = eval(sys.argv[3])
else:
    start_point = sorted(list(V))[0]
#グラフを定義（G に (V, E) を代入）
G = (V, E)

#確認のためグラフを表示
print('G='+str(G)+', start = ' + str(start_point))

#計算し，得られた木を表示
print('T =', DepthFirstSearch(G, start_point, True))
