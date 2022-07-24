'''
Created on 2022/07/24

@author: Sin Shimozono
'''
import sys
from math import log2, ceil, floor

def logstar(n : int):
    result = 0
    while ceil(log2(n)) >= 1:
        result += 1
        n = ceil(log2(n))
    return result
    
if __name__ == '__main__':
    n = int(eval(sys.argv[1]))
    print(floor(log2(n)))
    print(n, logstar(n))