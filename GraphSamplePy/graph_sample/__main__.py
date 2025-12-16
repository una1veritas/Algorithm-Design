'''
Created on 2025/12/15

@author: sin
'''
import sys

if __name__ == '__main__':
    V = set()
    E = set()
    if len(sys.argv) == 3 :
        V = set(eval(sys.argv[1]))
        E = set(eval(sys.argv[2]))
    
    '''check'''
    for e in E:
        try :
            (u, v) = e
        except:
            raise ValueError('not a pair of vertices: {e}')
        
        if u not in V or v not in V :
            raise ValueError('an edge has non-vertex end-point(s): ({u}, {v})')
    
    G = (V, E)
    print(G)
    