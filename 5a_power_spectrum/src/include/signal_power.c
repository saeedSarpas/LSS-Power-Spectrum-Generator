#include <stdlib.h>
#include <complex.h>
#include <fftw3.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/vector_struct.h"
#include "./../../../global_structs/modes_struct.h"

#include "./../../../global_functions/vector/vector.h"

#include "./../../../global_functions/modes/get_modes_in_range.h"
#include "./../../../global_functions/grid/three_to_one.h"

#include "./../struct/signal_power_result.h"

#include "./../include/generate_logarithmic_bins.h"

typedef struct {
	double mode_power;
	double error;
} variance_result_struct;

static variance_result_struct variance(vector_struct *powers_vector) {

	variance_result_struct result;
	result.mode_power = 0.0;
	result.error = 0.0;

	unsigned int i;
	double power;
	for (i = 0; i < powers_vector->log_length; i++) {
		vector_get_elem(powers_vector, i, &power);
		result.mode_power += power;
	}

	result.mode_power /= powers_vector->log_length;

	int tot_num_of_powers = powers_vector->log_length;

	double error = 0.0;
	while (powers_vector->log_length > 0) {
		vector_pop(powers_vector, &power);
		error += pow(power - result.mode_power, 2);
	}

	result.error = sqrt(error) / tot_num_of_powers;

	return result;
}

signal_power_result_struct signal_power (double k_min, double k_max,
		fftw_complex *delta_fourier, modes_struct *indexed_mode_modulus,
		config_struct *conf) {

	signal_power_result_struct result;

	size_t tot_num_of_grids = pow(conf->params.numOfAxisGrids, 3);

	vector_struct modes_vector;
	vector_new(&modes_vector, sizeof(struct modes), tot_num_of_grids);

	get_modes_in_range(k_min, k_max, indexed_mode_modulus, conf, &modes_vector);
	result.num_of_found_modes = modes_vector.log_length;

	vector_struct powers_vector;
	vector_new(&powers_vector, sizeof(double), modes_vector.log_length);

	modes_struct mode;
	double power;
	while (modes_vector.log_length > 0) {
		vector_pop(&modes_vector, &mode);

		power = pow(creal(delta_fourier[mode.index]), 2) +
			pow(cimag(delta_fourier[mode.index]), 2);

		vector_push(&powers_vector, &power);
	}

	if (result.num_of_found_modes == 0) {
		printf("\n[Found no point in this shell: %f <= k < %f]\n", k_min, k_max);
		vector_dispose(&modes_vector);
		vector_dispose(&powers_vector);
		exit(0);
	} else {
		variance_result_struct variance_result = variance(&powers_vector);
		result.mode_power = variance_result.mode_power;
		result.error = variance_result.error;
	}

	vector_dispose(&modes_vector);
	vector_dispose(&powers_vector);

	return result;
}
