import sys
import math
import cmath

def fft(varray):
    n = len(varray)
    f = list()
    for t in range(0, n):
        s = 0
        for x in range(0, n):
            s += varray[x] * cmath.exp(-1j * 2*math.pi/n * t * x)
        f.append(s/math.sqrt(n))
    return f

if len(sys.argv) != 2 :
    exit

data = list()
with open(sys.argv[1]) as f:
    for aline in f:
        data.append(float(aline))

n = 2 ** math.ceil(math.log(len(data),2))
for i in range(len(data), n):
    data.append(0)

print()
for val in fft(data):
    print(round(abs(val),4))
