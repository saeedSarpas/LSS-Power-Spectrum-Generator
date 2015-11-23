"""Drawing power spectrum plots"""
import plots as p

#------------------------------------------------------------------------------
#   POWER SPECTRUM
#------------------------------------------------------------------------------
PS_RANDOM_TSC = p.Plot()
PS_RANDOM_TSC.read_power_spectrum("./raw_data/power-spectrum-tsc.dat")
PS_RANDOM_TSC.draw_power_spectrum(color="#473F7F", linestyle="solid",
                                  label="ngp", ymin=-1e10, ymax=4e12,
                                  yerr='true', xmin=-0.1, xmax=2.5)
PS_RANDOM_TSC.save("ps-tsc", xlabel="$k$", ylabel="$P$")

PS_RANDOM_CIC = p.Plot()
PS_RANDOM_CIC.read_power_spectrum("./raw_data/power-spectrum-cic.dat")
PS_RANDOM_CIC.draw_power_spectrum(color="#885511", linestyle="solid",
                                  label="cic", ymin=-1e10, ymax=4e12,
                                  yerr='true', xmin=-0.1, xmax=2.5)
PS_RANDOM_CIC.save("ps-cic", xlabel="$k$", ylabel="$P$")

PS_RANDOM_NGP = p.Plot()
PS_RANDOM_NGP.read_power_spectrum("./raw_data/power-spectrum-ngp.dat")
PS_RANDOM_NGP.draw_power_spectrum(color="#885511", linestyle="solid",
                                  label="ngp", ymin=-1e10, ymax=4e12,
                                  yerr='true', xmin=-0.1, xmax=2.5)
PS_RANDOM_NGP.save("ps-ngp", xlabel="$k$", ylabel="$P$")
