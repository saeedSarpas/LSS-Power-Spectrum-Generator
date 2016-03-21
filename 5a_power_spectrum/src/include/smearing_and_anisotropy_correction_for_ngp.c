#include <math.h>
#include <complex.h>
#include <fftw3.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/grid/one_to_three.h"

void smearing_and_anisotropy_correction_for_ngp(fftw_complex *delta_fourier,
												config_struct *conf) {
	int N = pow(conf->params.numOfAxisGrids, 3);
	int k_Nyquist = conf->params.numOfAxisGrids / 2;

	int i, index, k[3];
	double W_k, phi;

	for (index = 0; index < N; index++) {
		W_k = 1.0;

		one_to_three(index, k, conf);

		for (i = 0; i < 3; i++) {
			k[i] -= conf->params.numOfAxisGrids / 2;
			phi = (M_PI * k[i]) / (2.0 * k_Nyquist);

			W_k = (phi == 0.0) ? 1.0 : W_k * sin(phi) / phi;
		}

		delta_fourier[index] /= W_k;
	}
}
