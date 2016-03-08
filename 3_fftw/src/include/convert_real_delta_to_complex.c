#include <complex.h>
#include <fftw3.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"

void convert_real_delta_to_complex(double *delta_real,
		fftw_complex *delta_complex, config_struct *conf) {

	size_t tot_num_of_grids = pow(conf->params.numOfAxisGrids, 3);

	unsigned int i;
	for (i = 0; i < tot_num_of_grids; i++) {
		delta_complex[i] = delta_real[i] + 0.0 * I;
	}
}
