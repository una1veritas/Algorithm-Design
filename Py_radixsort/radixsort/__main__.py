'''
Created on 2020/06/04

@author: sin
'''
import sys

array = [int(val) for val in sys.argv[1:]]

print('input array = ', end='')
print(array)

for bpos in range(0, 15):
    bit = 1<<bpos
    zeros = list()
    ones = list()
    for i in range(len(array)):
        if (array[i] & bit) == 0 :
            zeros.append(array[i])
        else:
            ones.append(array[i])
    for i in range(len(zeros)):
        array[i] = zeros[i]
    for i in range(len(ones)):
        array[len(zeros)+i] = ones[i]
    print(bit, array)

print('fin.')