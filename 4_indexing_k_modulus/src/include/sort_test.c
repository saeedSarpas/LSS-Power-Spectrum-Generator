#include <cgreen/cgreen.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/modes_struct.h"

#include "./../../../global_functions/memory/allocate_modes_struct.h"
#include "./../../../global_functions/grid/three_to_one.h"

#include "./../../src/include/load_modes_into.h"
#include "./../../src/include/sort.h"

Describe(sort);
BeforeEach(sort) {}
AfterEach(sort) {}

Ensure(sort, sort_modes_array_in_ascending) {
	config conf;
	conf.num_of_grids_in_each_axis = 4;

	int ng = conf.num_of_grids_in_each_axis;
	int ngs = pow(ng, 3);

	modes *modes_array;
	allocate_modes_struct(&modes_array, ngs);
	load_modes_into(modes_array, &conf);

	sort(modes_array, &conf);

	int i;
	for (i = 0; i < ngs - 1; i++) {
		assert_true(modes_array[i].modulus <= modes_array[i+1].modulus);
	}
}

TestSuite *sort_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, sort, sort_modes_array_in_ascending);
	return suite;
}
