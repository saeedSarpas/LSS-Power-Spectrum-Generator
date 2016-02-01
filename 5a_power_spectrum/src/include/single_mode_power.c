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
} variance_result_struct;

static variance_result_struct variance(vector_struct *power_double_vector) {

	variance_result_struct result;
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

single_mode_power_result_struct single_mode_power (double k_min, double k_max,
		fftw_complex *delta_fourier, modes_struct *indexed_mode_modulus,
		config_struct *conf) {

	single_mode_power_result_struct result;

	size_t tot_num_of_grids = pow(conf->num_of_grids_in_each_axis, 3);

	vector_struct modes_vector;
	vector_new(&modes_vector, sizeof(struct modes_struct_tag), tot_num_of_grids);

	get_modes_in_range(k_min, k_max, indexed_mode_modulus, conf, &modes_vector);
	result.num_of_found_modes = modes_vector.log_length;

	vector_struct power_double_vector;
	vector_new(&power_double_vector, sizeof(double), modes_vector.log_length);

	modes_struct mode;
	double power;
	while (modes_vector.log_length > 0) {
		vector_pop(&modes_vector, &mode);

		power = pow(creal(delta_fourier[mode.index]), 2) +
			pow(cimag(delta_fourier[mode.index]), 2);

		vector_push(&power_double_vector, &power);
	}

	if (power_double_vector.log_length == 0) {
		printf("\n[Found no point in this shell: %f <= k < %f]\n", k_min, k_max);
		vector_dispose(&modes_vector);
		vector_dispose(&power_double_vector);
		exit(0);
	} else {
		variance_result_struct variance_result = variance(&power_double_vector);
		result.mode_power = variance_result.mode_power;
		result.error = variance_result.error;
	}

	vector_dispose(&modes_vector);
	vector_dispose(&power_double_vector);

	return result;
}
