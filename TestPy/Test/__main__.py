'''
Created on 2024/06/21

@author: sin
'''
import sys
from datetime import datetime

# global constant 
M = 23
N = 19

def xy2v(x : int, y: int) -> int :
    if 0 <= x < M and 0 <= y < N :
        return y * M + x
    return None


def v2xy(v : int) -> int:
        if 0 <= v < M * N :
            return (v % M, v // M)
        return (None, None)

def enum_moves(v : int) -> int:
    result = list()
    for dx, dy in ((-2,+1), (-2,-1), (-1,-2), (+1, -2)) :
        x, y = v2xy(v)
        if x == None or y == None: continue
        dst = xy2v(x + dx, y + dy)
        if dst == None : continue
        result.append(dst)
    return result

def f(v: int) -> int:
    f2.counter += 1
    moves = enum_moves(v)
    nv = 0
    for mv in moves :
        n_mv = f(mv) + 1
        if n_mv > nv :
            nv = n_mv
    return nv

def f2(v: int, s : set = None) -> int:
    f2.counter += 1
    if s == None : s = set()
    if v in s:
        return -1
    s.add(v)
    moves = enum_moves(v)
    nv = 0
    for mv in moves :
        if mv in s: 
            continue
        n_mv = f2(mv, s) + 1
        if n_mv > nv :
            nv = n_mv
    return nv

if __name__ == '__main__':
    f2.counter = 0

    print(sys.argv)
    x = int(sys.argv[1])
    y = int(sys.argv[2])
    
    print("xy2v(x,y) = ", xy2v(x,y))
    start = datetime.now()
    print("f(xy2v(x,y)) = ", f(xy2v(x,y)))
    print(f2.counter)
    td = (datetime.now() - start)
    print(td.total_seconds())