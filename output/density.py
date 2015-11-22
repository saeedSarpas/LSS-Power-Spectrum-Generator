"""Drawing density plots"""
import plots as p

#------------------------------------------------------------------------------
#   DENSITY
#------------------------------------------------------------------------------
DENSITY_TSC = p.Plot()
DENSITY_TSC.read_density("./raw_data/griding-tsc.dat")
DENSITY_TSC.draw_density(cMap=True, zShift=1, vmin=0, vmax=5000)
DENSITY_TSC.save("density-tsc")

DENSITY_CIC = p.Plot()
DENSITY_CIC.read_density("./raw_data/griding-cic.dat")
DENSITY_CIC.draw_density(cMap=True, zShift=1, vmin=0, vmax=5000)
DENSITY_CIC.save("density-cic")

DENSITY_NGP = p.Plot()
DENSITY_NGP.read_density("./raw_data/griding-ngp.dat")
DENSITY_NGP.draw_density(cMap=True, zShift=1, vmin=0, vmax=5000)
DENSITY_NGP.save("density-ngp")
