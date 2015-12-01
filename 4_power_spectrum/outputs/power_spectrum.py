"""Drawing power spectrum plots"""
import plots as p

#------------------------------------------------------------------------------
#   POWER SPECTRUM
#------------------------------------------------------------------------------
PS_RANDOM_CIC = p.Plot()
PS_RANDOM_CIC.read_power_spectrum("./power_spectrum-cic-256-HaloTab-35289.dat")
PS_RANDOM_CIC.draw_power_spectrum(color="#885511", linestyle="solid",
                                  label="cic", ymin=0, ymax=3e10,
                                  yerr='true', xmin=-0.1, xmax=2.5)
PS_RANDOM_CIC.save("ps-cic", xlabel="$k$", ylabel="$P$")
