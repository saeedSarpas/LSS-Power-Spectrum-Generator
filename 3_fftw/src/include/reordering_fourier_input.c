#include <complex.h>
#include <fftw3.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/grid/one_to_three.h"

void reordering_fourier_input(fftw_complex *delta_complex,
		config_struct *conf) {
	// This function reorders the Fourier input in a way that the zero-th
	// element lies at the center of the output array

	unsigned int i;
	int pos[3];
	size_t tot_num_of_grids = pow(conf->run_params.num_of_axis_grids, 3);

	for (i = 0; i < tot_num_of_grids; i++) {
		one_to_three(i, pos, conf);
		if ((pos[0] + pos[1] + pos[2]) % 2 != 0) {
			delta_complex[i] = -1 * delta_complex[i];
		}
	}
}
