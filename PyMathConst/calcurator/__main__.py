import sys
#import math

#ライプニッツの式は π/4 を求めるものである．
#ここでは i 番目の pi4 とその直前の値 prev の平均の 4 倍（和の2倍）としてπを求める
def pi(err = 0.01):
    piquarter = 1
    sgn = -1
    prev = 0
    i = 1
    while abs(prev - piquarter) * 2 > err:
        prev = piquarter
        piquarter += sgn/(2*i+1)
        sgn = -sgn
        i += 1
    return 2*(prev + piquarter)

#ネイピア数 e をテイラー展開で求める．
#剰余項の幅を定数の誤差範囲として評価する. 
def napier(err = 0.01):
    esum = 1
    fac = 1
    i = 1
    while True :
        esum += 1/fac
        i += 1
        fac *= i
        if (esum/(fac - 1) - 1/fac) <= err :
            break
    return esum

#黄金比，フィボナッチ数列の前後二項の比を求める．
#動的計画法的？にもとめる．
def goldenratio(err = 0.0001):
    f_0 = 1
    f_1 = 1
    f_2 = 2
    r_pre = f_1 / f_0
    while abs(f_1/f_0 - f_2/f_1) > err:
        f_0 = f_1
        f_1 = f_2
        f_2 = f_0 + f_1
    return f_2/f_1

if len(sys.argv) > 1 and sys.argv[1] == 'pi' :
    err = 0.01
    if len(sys.argv) == 3 :
        err = float(sys.argv[2])
    print(pi(err))
elif len(sys.argv) > 1 and sys.argv[1] == 'napier' :
    err = 0.01
    if len(sys.argv) == 3 :
        err = float(sys.argv[2])
    print(napier(err))
elif len(sys.argv) > 1 and sys.argv[1] == 'goldenratio' :
#    err = 0.01
#    if len(sys.argv) == 3 :
#        err = float(sys.argv[2])
    print(goldenratio(0.0000000000000001))
    
print('finished.')