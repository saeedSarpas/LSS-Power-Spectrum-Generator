"""Drawing density plots"""
import plots as p
import os

#------------------------------------------------------------------------------
#   DENSITY
#------------------------------------------------------------------------------

PLOTS_NAME = [f for f in os.listdir("./output/") if
              f.startswith("ascii-density-contrast-grid")]

PLOTS = {}

for pl in PLOTS_NAME:
    plot_path = "./plots/" + os.path.splitext(pl)[0]
    PLOTS[pl] = p.DensityPlot()
    PLOTS[pl].read_density("./output/" + pl)
    PLOTS[pl].draw_density(cMap=True, zShift=1)
    p.save(plot_path.replace("ascii-", "", 1))
