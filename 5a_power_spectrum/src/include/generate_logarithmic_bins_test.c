#include <cgreen/cgreen.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/bins_struct.h"

#include "./../../../global_functions/vector/vector.h"
#include "./../../../global_functions/memory/allocate_modes_struct.h"

#include "./../../src/include/generate_logarithmic_bins.h"

#define BINS_MIN_MODE 5
#define NUM_OF_GRIDS 128

Describe(generate_logarithmic_bins);
BeforeEach(generate_logarithmic_bins) {}
AfterEach(generate_logarithmic_bins) {}

Ensure(generate_logarithmic_bins, sets_bins_boundries_correct) {
	config conf;
	conf.min_num_of_modes_in_bins = BINS_MIN_MODE;
	conf.num_of_grids_in_each_axis = NUM_OF_GRIDS;

	modes *indexed_mode_modulus;
	allocate_modes_struct(&indexed_mode_modulus, pow(NUM_OF_GRIDS, 3));

	int i;
	for (i = 0; i < pow(NUM_OF_GRIDS, 3); i++)
		indexed_mode_modulus[i].modulus = i;

	double first_bin_max = indexed_mode_modulus[conf.min_num_of_modes_in_bins].modulus;
	double jump = sqrt(first_bin_max);

	vector bins_vector;
	vector_new(&bins_vector, sizeof(bins), 10);

	generate_logarithmic_bins(&bins_vector, indexed_mode_modulus, &conf);

	bins bin;

	while (bins_vector.log_length > 0) {
		vector_pop(&bins_vector, &bin);

		assert_that(bin.k_min, is_equal_to(pow(jump, 2 * bins_vector.log_length)));
		assert_that(bin.k, is_equal_to(pow(jump, 2 * bins_vector.log_length + 1)));
		assert_that(bin.k_max, is_equal_to(pow(jump, 2 * bins_vector.log_length + 2)));
	}

	vector_dispose(&bins_vector);
}

TestSuite *generate_logarithmic_bins_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, generate_logarithmic_bins,
			sets_bins_boundries_correct);
	return suite;
}
