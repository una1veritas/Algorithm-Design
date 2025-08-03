import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline
import rdp
import math

def rdp_simplify(xy : np.array, epsilon):
    xy_rdp = rdp.rdp(xy, epsilon=epsilon)
    return xy_rdp

def diff_vec(orig, dest : np.array): 
    return dest - orig

def norm(v : np.array):
    return np.lialg.norm(v)

def outer_prod_norm(v0, v1 : np.array):
    return v0[0]*v1[1] - v0[1]*v1[0]

def distance_to_line(orig, dest, pt):
    v_orig_dest = diff_vec(orig, dest)
    v_orig_pt = diff_vec(orig, pt)
    return abs(outer_prod_norm(v_orig_pt, v_orig_dest)/np.dot(v_orig_dest,v_orig_pt))
    
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

def test_simplify(xy, dist, rot):
    path = list()
    ix = 2
    for i in range(ix):
        path.append( np.array([xy[i]]) )
    while ix < len(xy):
        prev = path[-2]
        curr = path[-1]
        next = np.array(xy[ix])
        outer_prod = outer_prod_norm(diff_vec(prev,curr),diff_vec(curr,next))
        dist = distance_to_line(prev, curr, next)
        print(outer_prod)
        if dist >= distance or outer_prod >= rotation :
            path.append( next )
        ix += 1
        
    if tuple(path[-1]) != tuple(xy[-1]) :
        path.append(xy[-1])
    return path

'''  '''
def min_simplify(xy : np.array, tolerance : float):
    tbl = [[float('inf') for j in range(len(xy))] for i in range(len(xy))]
    for from_ix in range(len(tbl)):
        for to_ix in range(from_ix+1, len(tbl[from_ix])):
            if from_ix == to_ix :
                tbl[from_ix][to_ix] = 0 
            elif from_ix + 1 == to_ix :
                tbl[from_ix][to_ix] = 0
            else:
                max_ix = from_ix
                max_dist = -float('inf')
                for ix in range(from_ix+1, to_ix):
                    ix_dist = distance_to_line(xy[from_ix], xy[to_ix], xy[ix])
                    if ix_dist > max_dist :
                        max_dist = ix_dist
                        max_ix = ix
                tbl[from_ix][to_ix] = max_dist #if max_dist <= tolerance else float('inf')
                #print(from_ix, to_ix, max_ix, max_dist)
        
    # for rx in range(len(tbl)):
    #     for cx in range(len(tbl[rx])):
    #         if tbl[rx][cx] == float('inf') :
    #             srep = ''
    #         else:
    #             srep = f'{tbl[rx][cx]:3.2f}'
    #         print(f'{srep:6} ', end='')
    #     print()
    # print()
    
    path = list()
    ix = len(xy) - 1
    path.append(ix)
    while ix > 0 :
        dst = ix
        for dx in range(0,ix):
            if tbl[dx][ix] <= tolerance :
                dst = dx
                break
        if dst == ix :
            print('error')
            return
        ix = dst
        path.append(ix)
    path.reverse()
    print(path)
    newxy = np.array([xy[i] for i in path])
    #print(newxy)
    return newxy


if __name__ == '__main__':
    tbl = np.genfromtxt('2023-06-22_16_48_37.csv', delimiter=',', skip_header=1, missing_values='', dtype=str)
    dt = np.datetime_as_string(tbl[:,3].astype(np.datetime64), timezone='UTC')
    dt = dt.astype(np.datetime64)
    latitude =tbl[:,0].astype(np.float64)
    longitude =tbl[:,1].astype(np.float64)
    pnum = len(dt)
    print(f'{pnum} points.')
    #print(dt)
    
    xy = list()
    diff = list()
    last_datetime = None
    for i in range(len(tbl)):
        if last_datetime is None:
            last_datetime = dt[i]
            xy.append(np.array([longitude[i], -latitude[i]]))
            continue
        past = dt[i] - last_datetime
        if past.item().total_seconds() >= 10 :
            last_datetime = dt[i]
            xy.append(np.array([longitude[i], -latitude[i]]))
    xy = np.array(xy)
    
    print(len(xy))
    simplified_xy = min_simplify(xy, 0.1)
    
    #xy = rdp_simplify(xy, 0.000125)
    print(len(simplified_xy))
    
    #exit()
    x, y = xy[:,0], xy[:,1]
    sx, sy = simplified_xy[:,0], simplified_xy[:,1]     
    ctrlparam = np.linspace(0,1,num=len(sx),endpoint=True)
    spl = make_interp_spline(ctrlparam, np.c_[sx, sy])

    drawparam = np.linspace(0, 1, len(sx)*8)
    x_new, y_new = spl(drawparam).T
    # for i in range(len(x_new)):
    #     print(x_new[i], y_new[i])
    
    plt.plot(x, y, '.', lw=0.1, alpha=0.5)
    plt.plot(sx, sy, '-')
    plt.plot(x_new, y_new, '-')
    plt.legend(['Input points', 'Selected points', 'Interpolated B-spline', 'True'],loc='best')
    plt.title('B-Spline interpolation')
    plt.show()
