import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline

if __name__ == '__main__':
    
    tbl = np.genfromtxt('2023-06-22_16_48_37.csv', delimiter=',', skip_header=1, missing_values='', dtype=str)
    dt = np.datetime_as_string(tbl[:,3].astype(np.datetime64), timezone='UTC')
    dt = dt.astype(np.datetime64)
    latitude =tbl[:,0].astype(np.float64)
    longitude =tbl[:,1].astype(np.float64)
    pnum = len(dt)
    print(f'{pnum} points.')
    print(dt)
    
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
