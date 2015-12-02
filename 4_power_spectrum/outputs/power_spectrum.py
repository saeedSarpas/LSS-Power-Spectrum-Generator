"""Drawing power spectrum plots"""
import plots as p
import os

#------------------------------------------------------------------------------
#   POWER SPECTRUM
#------------------------------------------------------------------------------

PS = [f for f in os.listdir("./") if f.startswith("power-spectrum-")]

PS_PLOTS = {}

for dat in PS:
    PS_PLOTS[dat] = p.Plot()
    PS_PLOTS[dat].read_power_spectrum(dat)
    PS_PLOTS[dat].draw_power_spectrum(color="#5b7c7d", ecolor="#fe5e31",
                                      linestyle="solid",
                                      xmin=0, xmax=2, yerr='true')
    PS_PLOTS[dat].save(os.path.splitext(dat)[0],
                       xlabel="$\\log k$", ylabel="$P$")
