#!/usr/bin/env python
import sys
import matplotlib
from pylab import *

def main():
    print "Starting to plot the circles"
    import matplotlib.pyplot as plt
    import numpy as np

    def xy(r,phi):
	      return r*np.cos(phi), r*np.sin(phi)

    fig = plt.figure()
    ax = fig.add_subplot(111,aspect='equal')  

    phis=np.arange(0,6.28,0.01)
    r =1.
    ax.plot( *xy(r,phis), c='r',ls='-' )
    plt.show()


if __name__ == '__main__':
    ret = main()
    if ret:
        sys.exit(0)

    sys.exit(1)
