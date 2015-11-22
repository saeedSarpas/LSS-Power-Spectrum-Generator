"""This module contains Plot class, a set of tools to generate different plots
(e.g. density and power spectrum plots)"""

import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import matplotlib.cm as cm
import numpy as np

#------------------------------------------------------------------------------
#   GRID PLOT CLASS
#------------------------------------------------------------------------------
class Plot:
    def __init__(self):
        self.__x = []
        self.__y = []
        self.__z = []
        self.__dx = []
        self.__dy = []
        self.__dz = []

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
        self.__x, self.__dx, self.__y = np.loadtxt(filename, unpack='true',
                                                   skiprows=skiprows)

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

        plt.imshow(self.__z, cmap=cm.jet, vmin=cmap_min, vmax=cmap_max,
                   extent=[x_min, x_max, y_min, y_max])

        if 'cMap' in kwargs and k('cMap') == True:
            plt.colorbar()

    def draw_power_spectrum(self, **kwargs):
        """Ploting power spectrum"""
        k = kwargs.get

        color = k("color") if 'color' in kwargs else '#000000'
        linestyle = k("linestyle") if 'linestyle' in kwargs else 'solid'
        label = k("label") if 'label' in kwargs else ''

        if "xmin" or "xmax" in kwargs:
            xmin = k('xmin') if 'xmin' in kwargs else np.amin(self.__x)
            xmax = k('xmax') if 'xmax' in kwargs else np.amax(self.__x)
            plt.xlim(xmin, xmax)

        if "ymin" or "ymax" in kwargs:
            ymin = k('ymin') if 'ymin' in kwargs else np.amin(self.__y)
            ymax = k('ymax') if 'ymax' in kwargs else np.amax(self.__y)
            plt.ylim(ymin, ymax)

        plt.plot(self.__x, self.__y, color=color, linestyle=linestyle,
                 label=label)

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
