import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline
import rdp
import math
from pyproj import Proj

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

def simplify_RDP(xy : np.array, epsilon):
    xy_rdp = rdp.rdp(xy, epsilon=epsilon)
    return xy_rdp

def simplify_test(xy, dist, rot):
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
def simplify_shortest(xy : np.array, tolerance : float):
    n = len(xy)
    smpl = dict()
    for gap in range(n):
        for fix in range(n):
            tix = fix + gap
            if not (tix < n) :
                break
            if fix == tix :
                smpl[(fix, tix)] = (1, fix)
            elif fix + 1 == tix :
                smpl[(fix, tix)] = (2, fix)
            else:
                for mix in range(fix+1, tix):
                    dist = distance_to_line(xy[fix], xy[tix], xy[mix])
                    if dist > tolerance :
                        if (fix, tix) not in smpl \
                        or smpl[(fix, tix)][0] > smpl[(fix, mix)][0] - 1 + smpl[(mix, tix)][0] :
                            smpl[(fix, tix)] = (smpl[(fix, mix)][0] - 1 + smpl[(mix, tix)][0], mix)
                if (fix, tix) not in smpl :
                    smpl[(fix, tix)] = (2, fix)
    
    # for rix in range(n):
    #     for cix in range(n):
    #         if (rix,cix) in smpl :
    #             print(f'{smpl[(rix,cix)][0]:3} ', end='')
    #         else:
    #             print('    ', end='')
    #     print()
    # print()
    #
    # for rix in range(midix.shape[0]):
    #     for cix in range(midix.shape[1]):
    #         print(f'{midix[rix,cix]:3} ', end='')
    #     print()
    # print()
    
    def find_path(i, j):
        if smpl[(i,j)][0] == 1 :
            #print([i])
            return [i]
        elif smpl[(i,j)][0] == 2 :
            #print([i,j])
            return [i,j]
        else:
            mix = smpl[(i,j)][1]
            return find_path(i,mix)[:-1] + find_path(mix, j)
    path_ix = find_path(0,len(xy)-1)
    #print(path_ix)
    return np.array([xy[i] for i in path_ix])


if __name__ == '__main__':
    tbl = np.genfromtxt('2023-06-22_16_48_37.csv', delimiter=',', skip_header=1, missing_values='', dtype=str)
    dt = np.datetime_as_string(tbl[:,3].astype(np.datetime64), timezone='UTC')
    dt = dt.astype(np.datetime64)
    latitude = tbl[:,0].astype(np.float64)
    longitude = tbl[:,1].astype(np.float64)
    center = (np.mean(longitude), np.mean(latitude))
    print(f'center = {center}')
    pnum = len(dt)
    print(f'{pnum} points.')
    #print(dt)
    
    proj = Proj(proj='aeqd', lat_0=center[1], lon_0=center[0], datum='WGS84')
    xy = list()
    diff = list()
    last_datetime = None
    for i in range(len(tbl)):
        if last_datetime is None:
            last_datetime = dt[i]
            x, y = proj(longitude[i], latitude[i])
            xy.append((x, y))
            continue
        past = dt[i] - last_datetime
        if past.item().total_seconds() >= 10 :
            last_datetime = dt[i]
            x, y = proj(longitude[i], latitude[i])
            xy.append((x, y))
    xy = np.array(xy)
    
    print(xy)
    print(len(xy))
    simplified_xy = simplify_shortest(xy, 0.1)
    
    
    #xy = simplify_RDP(xy, 0.000125)
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
    plt.plot(sx, sy, 'b.-')
    plt.plot(x_new, y_new, '-')
    plt.legend(['Input points', 'Selected points', 'Interpolated B-spline', 'True'],loc='best')
    plt.title('B-Spline interpolation')
    plt.show()
