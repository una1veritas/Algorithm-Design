import sys
from decimal import *
from fractions import Fraction
#import math

#ライプニッツの式は π/4 を求めるものである．
#ここでは i 番目の pi4 とその直前の値 prev の平均の 4 倍（和の2倍）としてπを求める
def pi(prec):
    prec = Decimal(prec/2)
    pi4 = Decimal('1')
    prev = Decimal('0')
    i = 1
    while abs(prev - pi4) > prec:
        prev = pi4
        pi4 -= Decimal('1')/((i<<1)+1)
        i += 1
        prev = pi4
        pi4 += Decimal('1')/((i<<1)+1)
        i += 1
    return 2*(prev + pi4)

#ネイピア数 e をテイラー展開で求める．
#剰余項の幅を定数の誤差範囲として評価する. 
def napier(prec):
    prec = Decimal(prec)
    esum = Decimal('1')
    fac = Decimal('1')
    i = 1
    while True :
        esum += 1/fac
        i += 1
        fac *= i
        if (esum/(fac - 1) - 1/fac) <= prec :
            break
    return esum

#黄金比，フィボナッチ数列の前後二項の比を求める．
#動的計画法的？にもとめる．
def goldenratio(prec):
    f_0 = 1
    f_1 = 1
    f_2 = 2
    while abs(Fraction(f_1,f_0) - Fraction(f_2,f_1)) > prec:
        f_0 = f_1
        f_1 = f_2
        f_2 = f_0 + f_1
    return float(f_2)/f_1

if len(sys.argv) > 1 and sys.argv[1] == 'pi' :
    prec = 0.01
    if len(sys.argv) == 3 :
        prec = pow(10, -int(sys.argv[2]))
    print(pi(prec))
elif len(sys.argv) > 1 and sys.argv[1] == 'napier' :
    prec = pow(10, -3)
    if len(sys.argv) == 3 :
        prec = pow(10, -int(sys.argv[2]))
    print(napier(prec))
elif len(sys.argv) > 1 and sys.argv[1] == 'goldenratio' :
    prec = pow(10, -3)
    if len(sys.argv) == 3 :
        prec = pow(10, -int(sys.argv[2]))
    print(goldenratio(prec))
    
print('finished.')