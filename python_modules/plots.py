"""This module contains Plot class, a set of tools to generate different plots
(e.g. density and power spectrum plots)"""

import matplotlib.colors as mcolors
import matplotlib.pyplot as plt
import numpy as np

#------------------------------------------------------------------------------
#   GRID PLOT CLASS
#------------------------------------------------------------------------------
class Plot:
    def __init__(self):
        self.__x = []
        self.__y = []
        self.__z = []
        self.__ldx = []
        self.__rdx = []
        self.__dy = []
        self.__dz = []

        cdict = {'red':   [(0.0, 0.0, 0.3568627450980392),
                        (0.25, 0.4470588235294118, 0.4470588235294118),
                        (0.50, 0.996078431372549, 0.996078431372549),
                        (0.75, 0.996078431372549, 0.996078431372549),
                        (1, 0.996078431372549, 0.996078431372549)],

        'green': [(0.0, 0.0, 0.48627450980392156),
                (0.25, 0.7215686274509804, 0.7215686274509804),
                (0.50, 0.8274509803921568, 0.8274509803921568),
                (0.75, 0.5647058823529412, 0.5647058823529412),
                (1, 0.3686274509803922, 0.3686274509803922)],

        'blue':  [(0.0, 0.0, 0.4901960784313725),
                (0.25, 0.788235294117647, 0.788235294117647),
                (0.50, 0.6470588235294118, 0.6470588235294118),
                (0.75, 0.0039215686274510, 0.0039215686274510),
                (1, 0.1921568627450980, 0.1921568627450980)]}

        self.__cm = mcolors.LinearSegmentedColormap('CustomMap', cdict)

    def read_density(self, filename, **kwargs):
        """Reading density files"""
        k = kwargs.get
        skip_header = k('skip_header') if 'skip_header' in kwargs else 0
        skip_footer = k('skip_footer') if 'skip_footer' in kwargs else 0

        self.__x, self.__y, self.__z = np.genfromtxt(filename, unpack='true',
                                                        skip_header=skip_header,
                                                        skip_footer=skip_footer)

        __n = int(len(self.__z)**.5)
        self.__z = self.__z.reshape(__n, __n)

    def read_power_spectrum(self, filename, **kwargs):
        """Reading power spectrum files"""
        k = kwargs.get
        skiprows = k('skiprows') if 'skiprows' in kwargs else 0
        self.__x, self.__ldx, self.__rdx, self.__y, self.__dy, __N = np.loadtxt(
            filename, unpack='true', skiprows=skiprows)

    def draw_density(self, **kwargs):
        """Ploting density"""
        k = kwargs.get

        if 'zShift' in kwargs:
            self.__z = self.__z + k('zShift')

        cmap_min = k('vmin') if 'vmin' in kwargs else np.amin(self.__z)
        cmap_max = k('vmax') if 'vmax' in kwargs else np.amax(self.__z)

        x_min = k('xmin') if 'xmin' in kwargs else 0
        x_max = k('xmax') if 'xmax' in kwargs else np.amax(self.__x)
        y_min = k('ymin') if 'ymin' in kwargs else 0
        y_max = k('ymax') if 'ymax' in kwargs else np.amax(self.__y)

        plt.imshow(self.__z, cmap=self.__cm, vmin=cmap_min, vmax=cmap_max,
                extent=[x_min, x_max, y_min, y_max])

        if 'cMap' in kwargs and k('cMap') == True:
            plt.colorbar()

    def draw_power_spectrum(self, **kwargs):
        """Ploting power spectrum"""
        k = kwargs.get

        color = k("color") if 'color' in kwargs else '#000000'
        linestyle = k("linestyle") if 'linestyle' in kwargs else 'solid'
        label = k("label") if 'label' in kwargs else ''

        xoffset = 0.05 * abs(self.__x[-1] - self.__x[0])
        yoffset = 0.05 * abs(self.__y[-1] - self.__y[0])

        if 'xmin' in kwargs:
            plt.gca().set_xlim(left=k('xmin'))

        if 'xmax' in kwargs:
            plt.gca().set_xlim(right=k('xmax'))

        if 'ymin' in kwargs:
            plt.gca().set_ylim(bottom=k('ymin'))

        if 'ymax' in kwargs:
            plt.gca().set_ylim(top=k('ymax'))

        if 'xerr' not in kwargs or 'xerr' in kwargs and k('xerr') != 'true':
            __dx = None
        else:
            __dx = [self.__ldx, self.__rdx]

        if 'yerr' not in kwargs or 'yerr' in kwargs and k('yerr') != 'true':
            self.__dy = None

        if 'xaxislog' in kwargs:
            plt.xscale(k('xaxislog'))

        if 'yaxislog' in kwargs:
            plt.yscale(k('yaxislog'))

        ecolor = k('ecolor') if 'ecolor' in kwargs else "#febb00"
        plt.errorbar(self.__x, self.__y, xerr=__dx, yerr=self.__dy,
                     color=color, ecolor=ecolor, linestyle=linestyle,
                     label=label)

        if 'shaded' in kwargs and k('shaded') == 'true':
            if 'yerr' in kwargs:
                __fc = k('facecolor') if 'facecolor' in kwargs else "#fef4ea"
                plt.fill_between(self.__x, self.__y - self.__dy, self.__y +
                                self.__dy, facecolor=__fc, edgecolor=__fc,
                                interpolate='true')

    def save(self, name, **kwargs):
        """Save plots"""
        k = kwargs.get

        if 'xlabel' in kwargs:
            plt.xlabel(k('xlabel'), fontsize=16)

        if 'ylabel' in kwargs:
            plt.ylabel(k('ylabel'), fontsize=16)

        path = "./plots/" + name + ".png"
        plt.savefig(path)

        plt.close()
