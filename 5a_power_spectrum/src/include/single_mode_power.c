#include <stdlib.h>
#include <complex.h>
#include <fftw3.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/vector_struct.h"
#include "./../../../global_structs/modes_struct.h"

#include "./../../../global_functions/memory/allocate_double_array.h"
#include "./../../../global_functions/memory/allocate_fftw_complex.h"
#include "./../../../global_functions/vector/vector.h"

#include "./../../../global_functions/modes/get_modes_in_range.h"
#include "./../../../global_functions/grid/three_to_one.h"

#include "./../struct/single_mode_power_result.h"

#include "./../include/generate_logarithmic_bins.h"

typedef struct {
	double mode_power;
	double error;
} variance_result;

static variance_result variance(vector *power_double_vector) {

	variance_result result;
	result.mode_power = 0.0;
	result.error = 0.0;

	int i;
	double power;
	for (i = 0; i < power_double_vector->log_length; i++) {
		vector_get_elem(power_double_vector, i, &power);
		result.mode_power += power;
	}

	result.mode_power /= power_double_vector->log_length;

	int tot_num_of_powers = power_double_vector->log_length;

	double error = 0.0;
	while (power_double_vector->log_length > 0) {
		vector_pop(power_double_vector, &power);
		error += pow(power - result.mode_power, 2);
	}

	result.error = sqrt(error) / tot_num_of_powers;

	return result;
}

single_mode_power_result single_mode_power (double k_min, double k, double k_max,
		fftw_complex *delta_fourier, modes *indexed_mode_modulus, config *conf) {

	single_mode_power_result result;

	size_t tot_num_of_grids = pow(conf->num_of_grids_in_each_axis, 3);

	vector modes_vector;
	vector_new(&modes_vector, sizeof(modes), tot_num_of_grids);

	get_modes_in_range(k_min, k_max, indexed_mode_modulus, conf, &modes_vector);
	result.num_of_found_modes = modes_vector.log_length;

	vector power_double_vector;
	vector_new(&power_double_vector, sizeof(double), modes_vector.log_length);

	modes mode;
	double power;
	while (modes_vector.log_length > 0) {
		vector_pop(&modes_vector, &mode);

		power = pow(creal(delta_fourier[mode.index]), 2) +
			pow(cimag(delta_fourier[mode.index]), 2);

		vector_push(&power_double_vector, &power);
	}

	if (power_double_vector.log_length == 0) {
		printf("\n[Found no point in this shell: %f < k < %f]\n", k_min, k_max);
		vector_dispose(&modes_vector);
		vector_dispose(&power_double_vector);
		exit(0);
	} else {
		variance_result power = variance(&power_double_vector);
		result.mode_power = power.mode_power;
		result.error = power.error;
	}

	vector_dispose(&modes_vector);
	vector_dispose(&power_double_vector);

	return result;
}
