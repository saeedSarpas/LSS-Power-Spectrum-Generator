#include <cgreen/cgreen.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/bins_struct.h"

#include "./../../../global_functions/vector/vector.h"
#include "./../../../global_functions/memory/allocate.h"

#include "./../../src/include/generate_logarithmic_bins.h"

Describe(generate_logarithmic_bins);

#define NUM_OF_GRIDS 128

static config_struct conf;
static modes_struct *indexed_mode_modulus;
static int tot_num_of_grids;
static double jump;
static vector_struct bins_vector;

static void fill_indexed_mode_modulus();

BeforeEach(generate_logarithmic_bins) {
	conf.run_params.num_of_axis_grids = NUM_OF_GRIDS;

	allocate((void **)&indexed_mode_modulus, pow(NUM_OF_GRIDS, 3),
			 sizeof(modes_struct));

	fill_indexed_mode_modulus();
	double max_of_first_bin = indexed_mode_modulus[18].modulus;
	jump = sqrt(max_of_first_bin);

	tot_num_of_grids = pow(conf.run_params.num_of_axis_grids, 3);

	vector_new(&bins_vector, sizeof(struct bins_struct_tag), 10);

}

AfterEach(generate_logarithmic_bins) {
	free(indexed_mode_modulus);
	vector_dispose(&bins_vector);
}

Ensure(generate_logarithmic_bins, sets_bins_boundries_correct) {
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
