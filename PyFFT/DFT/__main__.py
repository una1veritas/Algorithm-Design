import sys
import math
import cmath

def dft(varray):
    n = len(varray)
    f = list()
    for t in range(0, n):
        s = 0
        for x in range(0, n):
            s += varray[x] * cmath.exp(-1j * 2*math.pi/n * t * x)
        f.append(s)
    return f

def invdft(varray):
    n = len(varray)
    f = list()
    for t in range(0, n):
        s = 0
        for x in range(0, n):
            s += varray[x] * cmath.exp(1j * 2*math.pi/n * t * x)
        f.append(s/n)
    return f

if len(sys.argv) != 2 :
    exit

print(sys.argv[1])

data = list()
with open(sys.argv[1]) as f:
    for aline in f:
        print(aline.strip())
        data.append(float(aline))

n = 2 ** math.ceil(math.log(len(data),2))
for i in range(len(data), n):
    data.append(0)

print()
tdata = dft(data)
for val in tdata:
    print(round(abs(val),4))

#print(invfft(tdata))