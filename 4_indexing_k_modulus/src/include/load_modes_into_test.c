#include <cgreen/cgreen.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/modes_struct.h"

#include "./../../../global_functions/memory/allocate_modes_struct.h"
#include "./../../../global_functions/grid/three_to_one.h"

#include "./../../src/include/load_modes_into.h"

Describe(load_modes_into);
BeforeEach(load_modes_into) {}
AfterEach(load_modes_into) {}

Ensure(load_modes_into, accumulate_all_modes) {
	config conf;
	int ng = conf.num_of_grids_in_each_axis = 4;

	modes *modes_array;
	allocate_modes_struct(&modes_array, pow(ng, 3));

	load_modes_into(modes_array, &conf);

	int hgbs = conf.num_of_grids_in_each_axis / 2;
	int i, j, k, index;
	double len;
	for (i = 0; i < ng; i++) {
		for (j = 0; j < ng; j++) {
			for (k = 0; k < ng; k++) {
				index = three_to_one(i, j, k, &conf);
				assert_that(modes_array[index].index, is_equal_to(index));
				assert_that(modes_array[index].i, is_equal_to(i));
				assert_that(modes_array[index].j, is_equal_to(j));
				assert_that(modes_array[index].k, is_equal_to(k));
				len = sqrt(pow(i - hgbs, 2) + pow(j - hgbs, 2) + pow(k - hgbs, 2));
				assert_that(modes_array[index].length, is_equal_to(len));
			}
		}
	}
}

TestSuite *load_modes_into_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, load_modes_into, accumulate_all_modes);
	return suite;
}
