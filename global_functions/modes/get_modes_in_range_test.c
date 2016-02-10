#include <cgreen/cgreen.h>
#include <math.h>
#include <string.h>

#include "./../../global_structs/modes_struct.h"
#include "./../../global_structs/config_struct.h"

#include "./../../global_functions/vector/vector.h"
#include "./../../global_functions/memory/allocate_modes_struct.h"

#include "./get_modes_in_range.h"

#define NUM_OF_GRIDS 16

Describe(get_mode_in_range);
BeforeEach(get_mode_in_range) {}
AfterEach(get_mode_in_range) {}

Ensure(get_mode_in_range, returns_right_results_for_a_trivial_input) {
	config_struct conf;
	conf.num_of_grids_in_each_axis = NUM_OF_GRIDS;

	int tot_num_of_grids = pow(NUM_OF_GRIDS, 3);

	modes_struct *indexed_mode_modulus;
	allocate_modes_struct(&indexed_mode_modulus, tot_num_of_grids);

	int i;
	for (i = 0; i < tot_num_of_grids; i++)
		indexed_mode_modulus[i].modulus = i;

	vector_struct modes_vector;
	vector_new(&modes_vector, sizeof(struct modes_struct_tag), 1000);

	get_modes_in_range(100, 1000, indexed_mode_modulus, &conf, &modes_vector);
	modes_struct mode;
	assert_that(modes_vector.log_length, is_equal_to(900));
	vector_get_elem(&modes_vector, 0, &mode);
	assert_that(mode.modulus, is_equal_to(100));
	vector_get_elem(&modes_vector, 899, &mode);
	assert_that(mode.modulus, is_equal_to(999));

	vector_dispose(&modes_vector);
	vector_new(&modes_vector, sizeof(struct modes_struct_tag), 10);

	get_modes_in_range(0, 10, indexed_mode_modulus, &conf, &modes_vector);
	vector_get_elem(&modes_vector, 0, &mode);
	assert_that(mode.modulus, is_equal_to(0));

	vector_dispose(&modes_vector);
	vector_struct new_modes_vector;
	vector_new(&new_modes_vector, sizeof(struct modes_struct_tag), 10);

	get_modes_in_range(tot_num_of_grids - 11, tot_num_of_grids - 1,
			indexed_mode_modulus, &conf, &new_modes_vector);
	vector_get_elem(&new_modes_vector, 9, &mode);
	assert_that(mode.modulus, is_equal_to(tot_num_of_grids - 2));

	vector_dispose(&modes_vector);
}

TestSuite *get_mode_in_range_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, get_mode_in_range,
			returns_right_results_for_a_trivial_input);
	return suite;
}
