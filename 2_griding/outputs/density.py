"""Drawing density plots"""
import plots as p

#------------------------------------------------------------------------------
#   DENSITY
#------------------------------------------------------------------------------
DENSITY_CIC = p.Plot()
DENSITY_CIC.read_density(
    "./ascii-density-contrast-grid-cic-256-HaloTab-35289.dat")
DENSITY_CIC.draw_density(cMap=True, zShift=1)
DENSITY_CIC.save("density-cic")
