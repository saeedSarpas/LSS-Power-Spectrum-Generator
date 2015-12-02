"""Drawing density plots"""
import plots as p
import os

#------------------------------------------------------------------------------
#   DENSITY
#------------------------------------------------------------------------------

PLOTS_NAME = [f for f in os.listdir("./") if
              f.startswith("ascii-density-contrast-grid")]

PLOTS = {}

for dat in PLOTS_NAME:
    PLOTS[dat] = p.Plot()
    PLOTS[dat].read_density(dat)
    PLOTS[dat].draw_density(cMap=True, zShift=1)
    PLOTS[dat].save(os.path.splitext(dat)[0])
