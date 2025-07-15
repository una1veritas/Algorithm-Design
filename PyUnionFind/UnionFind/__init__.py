'''
Created on 2025/07/15

@author: sin
'''

class UnionFindN(object):
    '''
    classdocs
    '''


    def __init__(self, n = None):
        '''
        Constructor
        '''
        self.parent = list()
        if not isinstance(n, int):
            return
        for i in range(n):
            self.parent.append(i)
        return
    
    def __len__(self):
        return len(self.parent)
    
    def __str__(self):
        ostr = 'UnionFindN('
        for i in range(len(self)):
            if i == self.find(i):
                ostr += '{' + f'{i}'
                for j in range(i+1,len(self)):
                    if i == self.find(j) :
                        ostr += f', {j}'
                ostr += '}, '
        ostr += str(self.parent)
        ostr += ') '
        return ostr
    
    def add(self, elem):
        if not isinstance(elem, int):
            return
        for i in range(len(self), elem) :
            self.parent.append(i)
        
    def find(self, x):
        while x != self.parent[x] :
            x = self.parent[x]
        return x
    
    def union(self, a, b):
        a = self.find(a)
        b = self.find(b)
        if b > a :
            self.parent[b] = a
            return a
        else:
            self.parent[a] = b
            return b


class UnionFindH(UnionFindN):
    '''
    classdocs
    '''    
    def find(self, x):
        while x != self.parent[x] :
            child = x
            x = self.parent[x]
            self.parent[child] = self.parent[x]
        return x

class UnionFindC(UnionFindN):
    '''
    classdoxcs
    '''
    
    def find(self, x):
        root = x
        while root != self.parent[root]:
            root = self.parent[root]
        while x != self.parent[x] :
            t = x
            x = self.parent[x]
            self.parent[t] = root
        return x

class UnionFindR(UnionFindC):
    '''
    classdocs
    '''

    def __init__(self, n = None):
        '''
        Constructor
        '''
        self.parent = list()
        self.rank = list()
        if not isinstance(n, int):
            return
        for i in range(n):
            self.parent.append(i)
            self.rank.append(0)
        return
    
    def __str__(self):
        ostr = 'UnionFindR('
        setdict = dict()
        for x in range(len(self)):
            ix = self.find(x)
            if ix not in setdict: 
                setdict[ix] = list()
            setdict[ix].append(x) 
        for key, val in sorted(setdict.items()):
            ostr += '{' + ', '.join([str(e) for e in val]) + '}, ' 
        ostr += ') '
        return ostr
    
    def add(self, elem):
        if not isinstance(elem, int):
            return
        for i in range(len(self), elem) :
            self.parent.append(i)
            self.rank.append(0)
        
    def union(self, x, y):
        x = self.find(x)
        y = self.find(y)
        if self.rank[x] < self.rank[y] :
            self.parent[x] = y
            return y
        elif self.rank[x] > self.rank[y] :
            self.parent[y] = x
            return x
        else:
            self.parent[y] = x
            self.rank[x] += 1
            return x
    