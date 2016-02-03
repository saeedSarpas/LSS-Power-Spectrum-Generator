"""Drawing power spectrum plots"""
import plots as p
import os

#------------------------------------------------------------------------------
#   POWER SPECTRUM
#------------------------------------------------------------------------------

PS = [f for f in os.listdir("./output/") if f.startswith("power-spectrum-")]

PS_PLOTS = {}

for dat in PS:
    PS_PLOTS[dat] = p.Plot()
    PS_PLOTS[dat].read_power_spectrum("./output/" + dat, skiprows=1)
    PS_PLOTS[dat].draw_power_spectrum(color="#5b7c7d", ecolor="#fe5e31",
                                      linestyle="solid", shaded='true',
                                      xerr='true', yerr='true',
                                      xmin=1e-3, xmax=10,
                                      ymin=1e5, ymax=1e11,
                                      xaxislog='log', yaxislog='log')
    PS_PLOTS[dat].save("./plots/" + os.path.splitext(dat)[0],
                       xlabel="$\\log k$", ylabel="$P$")