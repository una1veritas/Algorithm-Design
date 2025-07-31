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

def diff_vec(orig, dest : np.array): 
    return dest - orig

def norm(v : np.array):
    return np.lialg.norm(v)

def outer_prod_norm(v0, v1 : np.array):
    return v0[0]*v1[1] - v0[1]*v1[0]

def distance_to_line(orig, dest, pt):
    v_orig_dest = diff_vec(orig, dest)
    v_orig_pt = diff_vec(orig, pt)
    return abs(outer_prod_norm(v_orig_pt, v_orig_dest))/np.dot(v_orig_dest,v_orig_pt)
    
'''
double gpspoint::distanceTo(const gpspoint &q1, const gpspoint &q2) const {
    if ( inner_prod(q1, q2, *this) < epsilon ) { // < 0.0
        return q1.distanceTo(*this);
    }
    if ( inner_prod(q2, q1, *this) < epsilon ) { // < 0.0
        return q2.distanceTo(*this);
    }
    return ABS(norm_outer_prod(q1, q2, *this)) / q1.distanceTo(q2);
}
'''

def abstraction(x, y, distance, rotation):
    path = list()
    ix = 2
    for i in range(ix):
        path.append( np.array([x[i], y[i]]) )
    while ix < len(x):
        prev = path[-2]
        curr = path[-1]
        next = np.array([x[ix],y[ix]])
        outer_prod = outer_prod_norm(diff_vec(prev,curr),diff_vec(curr,next))
        dist = distance_to_line(prev, curr, next)
        print(outer_prod)
        if dist >= distance or outer_prod >= rotation :
            path.append( np.array([x[ix],y[ix]]) )
        ix += 1
        
    if tuple(path[-1]) != ([x[-1], y[-1]]) :
        path.append( np.array([x[-1], y[-1]]))
    return (np.array([e[0] for e in path]), np.array([e[1] for e in path]))

if __name__ == '__main__':
    1
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
    
    x, y = abstraction(x, y, 0.2, 1e-8)
    #x, y = rdp_abstraction(x, y, 0.000125)

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
