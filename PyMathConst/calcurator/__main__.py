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
    
print('finished.')