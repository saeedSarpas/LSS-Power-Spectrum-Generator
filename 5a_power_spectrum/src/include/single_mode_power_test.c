#include <cgreen/cgreen.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/memory/allocate_fftw_complex.h"
#include "./../../../global_functions/memory/allocate_modes_struct.h"
#include "./../../../global_functions/grid/three_to_one.h"

#include "./../../../4_indexing_k_modulus/src/include/sort.h"

#include "./../../src/struct/single_mode_power_result.h"

#include "./../../src/include/single_mode_power.h"
#include "./../../src/include/generate_logarithmic_bins.h"

#define BINS_MIN_MODE 5
#define NUM_OF_GRIDS 128

Describe(single_mode_power);
BeforeEach(single_mode_power) {}
AfterEach(single_mode_power) {}

Ensure(single_mode_power, returns_right_results_for_a_trivial_input) {
	config_struct conf;
	conf.min_num_of_modes_in_bins = BINS_MIN_MODE;
	conf.num_of_grids_in_each_axis = NUM_OF_GRIDS;

	int tot_num_of_grids = pow(conf.num_of_grids_in_each_axis, 3);

	fftw_complex *delta_fourier;
	allocate_fftw_complex(&delta_fourier, tot_num_of_grids);

	int i;
	for(i = 0; i < tot_num_of_grids; i++)
		delta_fourier[i] = 1.0 + 1.0 * I;

	// DC mode
	int index = three_to_one(conf.num_of_grids_in_each_axis /2,
			conf.num_of_grids_in_each_axis / 2,
			conf.num_of_grids_in_each_axis / 2,
			&conf);
	delta_fourier[index] = tot_num_of_grids + tot_num_of_grids * I;


	modes_struct *indexed_mode_modulus;
	allocate_modes_struct(&indexed_mode_modulus, pow(NUM_OF_GRIDS, 3));
	int j, k;
	for (i = 0; i < NUM_OF_GRIDS; i++) {
		for (j = 0; j < NUM_OF_GRIDS; j++) {
			for (k = 0; k < NUM_OF_GRIDS; k++) {
				index = three_to_one(i, j, k, &conf);
				indexed_mode_modulus[index].index = index;
				indexed_mode_modulus[index].kx = i - (NUM_OF_GRIDS / 2);
				indexed_mode_modulus[index].ky = j - (NUM_OF_GRIDS / 2);
				indexed_mode_modulus[index].kz = k - (NUM_OF_GRIDS / 2);
				indexed_mode_modulus[index].modulus = index;
			}
		}
	}
	sort(indexed_mode_modulus, &conf);

	single_mode_power_result_struct result;
	result = single_mode_power(0, 10000, delta_fourier,
			indexed_mode_modulus, &conf);

	assert_that(result.mode_power, is_equal_to(2));
	assert_that(result.error, is_equal_to(0));
	assert_that(result.num_of_found_modes, is_equal_to(10000));
}

TestSuite *single_mode_power_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, single_mode_power,
			returns_right_results_for_a_trivial_input);
	return suite;
}
