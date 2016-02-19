#include <cgreen/cgreen.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/modes_struct.h"

#include "./../../../global_functions/memory/allocate.h"
#include "./../../../global_functions/grid/three_to_one.h"

#include "./../../src/include/load_modes_into.h"

Describe(load_modes_into);

#define NUM_OF_GRIDS 4

static config_struct conf;
static modes_struct *modes_array;

BeforeEach(load_modes_into) {
	conf.run_params.num_of_axis_grids = NUM_OF_GRIDS;
	allocate((void **)&modes_array, pow(NUM_OF_GRIDS, 3), sizeof(modes_struct));
}

AfterEach(load_modes_into) {
	free(modes_array);
}

Ensure(load_modes_into, accumulate_all_modes) {
	load_modes_into(modes_array, &conf);

	int hgbs = conf.run_params.num_of_axis_grids / 2;
	double len;

	int index, i, j, k;
	for (i = 0; i < NUM_OF_GRIDS; i++) {
		for (j = 0; j < NUM_OF_GRIDS; j++) {
			for (k = 0; k < NUM_OF_GRIDS; k++) {
				index = three_to_one(i, j, k, &conf);

				assert_that(modes_array[index].index, is_equal_to(index));
				assert_that(modes_array[index].kx, is_equal_to(i - hgbs));
				assert_that(modes_array[index].ky, is_equal_to(j - hgbs));
				assert_that(modes_array[index].kz, is_equal_to(k - hgbs));

				len = sqrt(pow(i - hgbs, 2) + pow(j - hgbs, 2) +
						   pow(k - hgbs, 2));

				assert_that(modes_array[index].modulus, is_equal_to(len));
			}
		}
	}
}

TestSuite *load_modes_into_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, load_modes_into, accumulate_all_modes);
	return suite;
}
