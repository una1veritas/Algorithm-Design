import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline
import rdp
import math

def rdp_abstraction(x, y : np.array, epsilon):
    xy = np.vstack((x,y)).T
    xy_rdp = rdp.rdp(xy, epsilon=epsilon)
    print(xy_rdp)
    return (xy_rdp[:,0], xy_rdp[:,1])

def diff_vec(p0, p1):
    return (p1[0]-p0[0], p1[1]-p0[1])

def inner_prod(v0, v1):
    return v0[0]*v1[0] + v1[0]*v1[1]

def norm(v):
    return math.sqrt(v[0]*v[0]+v[1]*v[1])
    
def abstraction(x,y,param):
    stk = list()
    ix = 2
    for i in range(ix):
        stk.append( (x[i], y[i]) )
    while ix < len(x):
        stk.append( (x[ix],y[ix]) ) 
        # last two vectors
        p0 = stk[-3]
        p1 = stk[-2]
        v0 = (p1[0] - p0[0], p1[1] - p0[1])
        p2 = stk[-1]
        v1 = (p2[0] - p1[0], p2[1] - p1[1])
        
        
        ix += 1
        
    
    return (x,y)

if __name__ == '__main__':
    
    tbl = np.genfromtxt('2023-06-22_16_48_37.csv', delimiter=',', skip_header=1, missing_values='', dtype=str)
    dt = np.datetime_as_string(tbl[:,3].astype(np.datetime64), timezone='UTC')
    dt = dt.astype(np.datetime64)
    latitude =tbl[:,0].astype(np.float64)
    longitude =tbl[:,1].astype(np.float64)
    pnum = len(dt)
    print(f'{pnum} points.')
    #print(dt)
    
    x = np.array([])
    y = np.array([])
    diff = list()
    last_datetime = None
    for i in range(len(tbl)):
        if last_datetime is None:
            last_datetime = dt[i]
            x = np.append(x,longitude[i])
            y = np.append(y, -latitude[i])
            continue
        past = dt[i] - last_datetime
        if past.item().total_seconds() >= 30 :
            last_datetime = dt[i]
            x = np.append(x,longitude[i])
            y = np.append(y, -latitude[i])
    y = y * 10
    
    x, y = rdp_abstraction(x, y, 0.0005)
    print(len(x))
            
    ctrlparam = np.linspace(0,1,num=len(x),endpoint=True)
    spl = make_interp_spline(ctrlparam, np.c_[x, y])

    drawparam = np.linspace(0, 1, len(x)*4)
    x_new, y_new = spl(drawparam).T
    # for i in range(len(x_new)):
    #     print(x_new[i], y_new[i])
    
    plt.plot(x, y, '.')
    plt.plot(x_new, y_new, '-')
    plt.legend(['Points', 'Interpolated B-spline', 'True'],loc='best')
    plt.title('B-Spline interpolation')
    plt.show()
