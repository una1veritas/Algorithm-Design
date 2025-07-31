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

def abstraction(x,y,param):
    path = list()
    ix = 2
    for i in range(ix):
        path.append( (x[i], y[i]) )
    while ix < len(x):
        currpoint =  np.array([x[ix-1], y[ix-1]])
        prevpoint =  np.array([x[ix-2], y[ix-2]])
        nextpoint = np.array([x[ix], y[ix]])
        v_pc = diff_vec(prevpoint,currpoint)
        v_cn = diff_vec(currpoint,nextpoint)
        print(currpoint,prevpoint,nextpoint,v_pc,v_cn)
        print(outer_prod_norm(v_pc, v_cn), distance_to_line(prevpoint, currpoint,nextpoint))
        print()
        ix += 1
    
    if path[-1] != (x[-1],y[-1]) :
        path.append((x[-1],y[-1]))
    return (x,y)
'''
[130.34680449 -33.59433694] [130.34643064 -33.59438019] [130.34717437 -33.59437509] [3.73849645e-04 4.32422385e-05] [ 3.69876623e-04 -3.81460413e-05]
-3.025517716438429e-08 0.10872903378191999

[130.34717437 -33.59437509] [130.34680449 -33.59433694] [130.34757566 -33.59432562] [ 3.69876623e-04 -3.81460413e-05] [4.01291996e-04 4.94699925e-05]
3.360549485782847e-08 0.11799463393082653

[130.34757566 -33.59432562] [130.34717437 -33.59437509] [130.34790472 -33.59431959] [4.01291996e-04 4.94699925e-05] [3.29056755e-04 6.02658838e-06]
-1.3860013511547907e-08 0.04685151160193921

[130.34790472 -33.59431959] [130.34757566 -33.59432562] [130.34821946 -33.59435583] [3.29056755e-04 6.02658838e-06] [ 3.14740464e-04 -3.62349674e-05]
-1.3820172006795417e-08 0.06529304473802645

[130.34821946 -33.59435583] [130.34790472 -33.59431959] [130.34858979 -33.5943425 ] [ 3.14740464e-04 -3.62349674e-05] [3.70329246e-04 1.33272260e-05]
1.7613485465983608e-08 0.08137467757518727

[130.34858979 -33.5943425 ] [130.34821946 -33.59435583] [130.34898754 -33.59434802] [3.70329246e-04 1.33272260e-05] [ 3.97754833e-04 -5.51529228e-06]
-7.343442601213891e-09 0.025807384989097532

[130.34898754 -33.59434802] [130.34858979 -33.5943425 ] [130.34936503 -33.59437273] [ 3.97754833e-04 -5.51529228e-06] [ 3.77487391e-04 -2.47182325e-05]
-7.749843132276714e-09 0.025119167501418245

[130.34936503 -33.59437273] [130.34898754 -33.59434802] [130.34979311 -33.59441615] [ 3.77487391e-04 -2.47182325e-05] [ 4.28082959e-04 -4.34127077e-05]
-5.806295690527742e-09 0.01898867766497508

[130.34979311 -33.59441615] [130.34936503 -33.59437273] [130.35022431 -33.59441852] [ 4.28082959e-04 -4.34127077e-05] [ 4.31196227e-04 -2.37762934e-06]
1.7701573164226558e-08 0.04786399601644937
'''
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
    
    abstraction(x, y, 1)
    x, y = rdp_abstraction(x, y, 0.000125)
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
