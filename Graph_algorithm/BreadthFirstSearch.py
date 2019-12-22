# Breadth First Search example program
# example execution:
# python3 BreadthFirstSearch.py "{1, 2, 3, 4, 5, 6}" "{(1, 2), (2, 3), (1, 4), (3, 4), (4, 5), (2,6), (3, 6)}" 1
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

def BreadthFirstSearch(G, start, show = False):
    (V, E) = G
    if not start in V :
        print('Error: the starting point '+str(start)+' is not in G.')
        return ()
    E_T = set()
    Q = [ start ]  # the initial front line
    U = set() 
    U.add(start)
    # print(d, que)
    while len(Q) != 0 :
        if show: print('Q = '+str(Q) + ', U = '+str(U)) # show the current front line 
        v = Q.pop()
        for w in adjacent_points(G, v) :
            # print( (v, w) )
            if w in U : 
                continue
            U.add(w)
            Q.append(w)
            E_T.add( (v,w) )
    return (V, E_T)

V = eval(sys.argv[1])
E = eval(sys.argv[2])
if len(sys.argv) > 3 :
    start_point = eval(sys.argv[3])
else:
    start_point = sorted(list(V))[0]
G = (V, E)

print('G='+str(G)+', '+'start = ' + str(start_point))

print('Spanning Tree =' + str(BreadthFirstSearch(G, start_point, True)) )
