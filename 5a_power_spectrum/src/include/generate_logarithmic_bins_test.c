#include <cgreen/cgreen.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/bins_struct.h"

#include "./../../../global_functions/vector/vector.h"
#include "./../../../global_functions/memory/allocate_modes_struct.h"

#include "./../../src/include/generate_logarithmic_bins.h"

Describe(generate_logarithmic_bins);

#define BINS_MIN_MODE 5
#define NUM_OF_GRIDS 128

static config_struct conf;
static modes_struct *indexed_mode_modulus;
static int tot_num_of_grids;
static double jump;
static vector_struct bins_vector;
static void fill_indexed_mode_modulus();

BeforeEach(generate_logarithmic_bins) {
	conf.min_num_of_modes_in_bins = BINS_MIN_MODE;
	conf.num_of_grids_in_each_axis = NUM_OF_GRIDS;

	allocate_modes_struct(&indexed_mode_modulus, pow(NUM_OF_GRIDS, 3));

	double first_bin_max =
		indexed_mode_modulus[conf.min_num_of_modes_in_bins + 1].modulus;
	jump = sqrt(first_bin_max);

	tot_num_of_grids = pow(conf.num_of_grids_in_each_axis, 3);

	vector_new(&bins_vector, sizeof(struct bins_struct_tag), 10);

}

AfterEach(generate_logarithmic_bins) {
	free(indexed_mode_modulus);
	vector_dispose(&bins_vector);
}

Ensure(generate_logarithmic_bins, sets_bins_boundries_correct) {
	fill_indexed_mode_modulus();

	generate_logarithmic_bins(&bins_vector, indexed_mode_modulus, &conf);

	bins_struct bin;
	while (bins_vector.log_length > 0) {
		vector_pop(&bins_vector, &bin);

		assert_that(bin.k_min, is_equal_to(pow(jump, 2 * bins_vector.log_length)));
		assert_that(bin.k, is_equal_to(pow(jump, 2 * bins_vector.log_length + 1)));
		assert_that(bin.k_max, is_equal_to(pow(jump, 2 * bins_vector.log_length + 2)));
	}

}

TestSuite *generate_logarithmic_bins_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, generate_logarithmic_bins,
			sets_bins_boundries_correct);
	return suite;
}

void fill_indexed_mode_modulus() {
	int i;
	for (i = 0; i < tot_num_of_grids; i++)
		indexed_mode_modulus[i].modulus = i;
}
