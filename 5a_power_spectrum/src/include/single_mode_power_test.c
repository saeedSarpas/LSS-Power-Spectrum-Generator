#include <cgreen/cgreen.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/memory/allocate_fftw_complex.h"
#include "./../../../global_functions/memory/allocate_modes_struct.h"

#include "./../../src/struct/single_mode_power_result.h"

#include "./../../src/include/single_mode_power.h"
#include "./../../src/include/generate_logarithmic_bins.h"

#define BINS_MIN_MODE 5
#define NUM_OF_GRIDS 128

Describe(single_mode_power);
BeforeEach(single_mode_power) {}
AfterEach(single_mode_power) {}

Ensure(single_mode_power, returns_right_results_for_a_trivial_input) {
	config conf;
	conf.min_num_of_modes_in_bins = BINS_MIN_MODE;
	conf.num_of_grids_in_each_axis = NUM_OF_GRIDS;

	int tot_num_of_grids = pow(conf.num_of_grids_in_each_axis, 3);

	fftw_complex *delta_fourier;
	allocate_fftw_complex(&delta_fourier, tot_num_of_grids);

	// DC mode
	delta_fourier[0] = tot_num_of_grids + tot_num_of_grids * I;

	int i;
	for(i = 1; i < tot_num_of_grids; i++)
		delta_fourier[i] = 1.0 + 1.0 * I;

	modes *indexed_mode_modulus;
	allocate_modes_struct(&indexed_mode_modulus, pow(NUM_OF_GRIDS, 3));

	for (i = 0; i < tot_num_of_grids; i++)
		indexed_mode_modulus[i].length = i;

	single_mode_power_result result;
	result = single_mode_power(0, 100, 10000, delta_fourier,
			indexed_mode_modulus, &conf);

	assert_that(result.mode_power, is_equal_to(sqrt(2)));
	assert_that(result.error, is_equal_to(0));
	assert_that(result.num_of_found_modes, is_equal_to(10000));
}

TestSuite *single_mode_power_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, single_mode_power,
			returns_right_results_for_a_trivial_input);
	return suite;
}
