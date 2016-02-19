#include <cgreen/cgreen.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/modes_struct.h"

#include "./../../../global_functions/memory/allocate.h"
#include "./../../../global_functions/grid/three_to_one.h"

#include "./../../src/include/load_modes_into.h"
#include "./../../src/include/sort.h"

Describe(sort);

#define NUM_OF_GRIDS 4

static config_struct conf;
static modes_struct *modes_array;

BeforeEach(sort) {
	conf.run_params.num_of_axis_grids = NUM_OF_GRIDS;

	allocate((void **)&modes_array, pow(NUM_OF_GRIDS, 3), sizeof(modes_struct));
	load_modes_into(modes_array, &conf);
}

AfterEach(sort) {
	free(modes_array);
}

Ensure(sort, sort_modes_array_in_ascending) {
	sort(modes_array, &conf);

	int i, tot_num_of_grids = pow(conf.run_params.num_of_axis_grids, 3);

	for (i = 0; i < tot_num_of_grids - 1; i++)
		assert_true(modes_array[i].modulus <= modes_array[i+1].modulus);
}

TestSuite *sort_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, sort, sort_modes_array_in_ascending);
	return suite;
}
