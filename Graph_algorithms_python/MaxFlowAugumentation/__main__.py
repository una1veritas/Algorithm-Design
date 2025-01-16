'''
Created on 2025/01/11

@author: sin
'''
import sys

'''グラフを表すデータ構造（クラス） Graph, DiGraph の定義 '''
class Graph:
    def __init__(self, vertices={}, edges={}):
        '''辺は点の組 tuple で表す．\
        点と辺それぞれの集合は、集合型（ハッシュテーブル）で表す．'''
        self.vertices = set(vertices)
        self.edges = set([tuple(e) for e in edges])
    
    def add_edge(self, u, v):
        self.vertices.add(u)
        self.vertices.add(v)
        self.edges.add( (u, v) )

    def adjacent(self, u, v):
        ''' (u, v) と (v, u) は一般にハッシュ値が異なる'''
        return (u,v) in self.edges or (v,u) in self.edges
        
    def adjacent_points(self, v):
        adjs = list()
        '''全探索'''
        for u in self.vertices:
            if self.adjacent(u, v) :
                adjs.append(u)
        return adjs
    
    def __str__(self):
        return 'Graph(' + str(self.vertices) + ', ' + str(self.edges) + ') '

'''Graph のサブクラスとして有向グラフ directed graphのクラスを定義する'''
class DiGraph(Graph):
    def direction(self, u, v):
        if (u,v) in self.edges : return 1
        if (v,u) in self.edges : return -1
        return 0
    
    def __str__(self):
        res = 'DiGraph(' + str(self.vertices) + ', {'
        cnt = 0
        for e in self.edges:
            res +=  '(' + str(e[0]) + ' -> ' + str(e[1]) + ')'
            cnt += 1
            if cnt < len(self.edges):
                res += ', '
        res += '}) '
        return res
    
'''digraph と capacity について, flow に残余がある辺からなる source から sink への道を一つみつけ\
道と通しでの残余値の組を返す．深さ優先探索'''
def find_aug_path(digraph, capacity, source, sink, flow):
    stack = [(source, float('inf'))]
    augpath = list()
    while len(stack) != 0 :
        if len(augpath) > 0 and augpath[-1] == stack[-1][0] :
            '''バックトラック'''
            stack.pop()
            augpath.pop()
            continue
        v, c = stack[-1]
        augpath.append(v)
        if augpath[-1] == sink :
            stack.clear()
            return (augpath, c)
        else:
            for dst in digraph.adjacent_points(v) :
                if dst in augpath : 
                    ''' 点 dst はすでにパスが通過済み '''
                    '''めんどうなので線形探索になっている．\
                    augpathの点の集合を別に持てば多少高速化'''
                    continue
                if digraph.direction(v, dst) > 0 and capa[(v, dst)] > flow[(v,dst)] :
                    '''順辺'''
                    stack.append( (dst, min(c, capa[(v, dst)] - flow[(v,dst)]) ) )
                elif digraph.direction(v, dst) < 0 and flow[(dst, v)] > 0 :
                    '''逆辺'''
                    stack.append( (dst, min(c, flow[(dst,v)])) )
    return None

def maxflow(dg, capa, src, snk):    
    ''' 自明なフローを定義 '''
    flow = dict()
    for e in capa:
        flow[e] = 0
    ''' 残余ネットワーク residual network 上の道の探索と flow の更新 '''
    while (aug := find_aug_path(dg, capa, src, snk, flow)) != None:
        ''' 返値を道 path と増分 aug にわける'''
        path, augval = aug
        '''道の各辺の流量を aug だけ変更 '''
        for i in range(len(path) - 1):
            if dg.direction(path[i], path[i+1]) > 0 :
                flow[(path[i], path[i+1])] += augval
            elif dg.direction(path[i], path[i+1]) < 0 :
                print(path)
                flow[(path[i+1], path[i])] -= augval
        print('augumented '+str(augval)+' on path = ', path)
    return flow

if __name__ == '__main__':
    # "{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}" "{('a','c'):3, ('a', 'e'):4, ('a', 'd'):2, ('b', 'c'):6, ('b', 'h'):1, ('c', 'd'):5, ('c', 'h'):3, ('d', 'h'):2, ('e', 'f'):8, ('e', 'g'):4, ('e', 'h'):1}" "'a'" "'h'" 
    # "{'s', 'u', 'v', 'w', 'x', 'y', 'z', 't'}" "{('s','u'):5, ('s', 'v'):6, ('s', 'w'):2, ('u', 'x'):3, ('u', 'y'):2, ('v', 'x'):4, ('v', 'z'):3, ('w', 'y'):3, ('w', 'z'):1, ('x', 't'):3, ('y', 't'):2, ('z', 't'):5}" "'s'" "'t'"
    if len(sys.argv) > 4 :
        V = eval(sys.argv[1])
        Ew = eval(sys.argv[2])
        E = set(Ew.keys())
        capa = dict(Ew)
        print(V, E)
        print(capa)
        s = eval(sys.argv[3])
        t = eval(sys.argv[4])
    else:
        print('error.')
        print("usage: python3 MaxFlowAugumentation \"{'s', 'u', 'v', 'w', 'x', 'y', 'z', 't'}\" \"{('s','u'):5, ('s', 'v'):6, ('s', 'w'):2, ('u', 'x'):3, ('u', 'y'):2, ('v', 'x'):4, ('v', 'z'):3, ('w', 'y'):3, ('w', 'z'):1, ('x', 't'):3, ('y', 't'):2, ('z', 't'):5}\" \"'s'\" \"'t'\"")
        exit(1)
    
    #グラフを定義（G に (V, E) を代入）
    g = DiGraph(V, E)
    #確認のためグラフを表示
    print('G='+str(g))
    print('capacity func = ' + str(capa))
    print('source = ' + str(s) + ', sink = ' + str(t))
    flow = maxflow(g, capa, s, t)
    print('max flow = ' )
    for e in flow:
        if flow[e] > 0 :
            print(e, flow[e])