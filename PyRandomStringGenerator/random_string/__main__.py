'''
Created on 2025/07/24

@author: sin
'''
import random
import string

def random_string(length=8):
    letters = string.ascii_uppercase + string.digits
    return ''.join(random.choices(letters, k=length))

if __name__ == '__main__':
    l = list()
    for i in range(10):
        l.append( (random_string(6), i) )
    
    for e in l:
        print(e)
    print()
    
    for e in sorted(l):
        print(e)
    