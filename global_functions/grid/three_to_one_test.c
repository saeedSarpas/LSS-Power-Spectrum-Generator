#include <cgreen/cgreen.h>
#include <math.h>

#include "./../../global_structs/config_struct.h"

#include "./three_to_one.h"

#define NUM_OF_GRIDS 64

Describe (three_to_one);

BeforeEach (three_to_one) {}
AfterEach (three_to_one) {}

Ensure (three_to_one, returns_right_results_for_a_trivial_input) {
	config_struct conf;
	conf.params.numOfAxisGrids = NUM_OF_GRIDS;

	int grids_squared = pow(NUM_OF_GRIDS, 2);

	int index = three_to_one(0, 0, 0, &conf);
	assert_that(index, is_equal_to(0));

	index = three_to_one(1, 0, 0, &conf);
	assert_that(index, is_equal_to(grids_squared));

	index = three_to_one(1, 1, 0, &conf);
	assert_that(index, is_equal_to(grids_squared + NUM_OF_GRIDS));

	index = three_to_one(1, 1, 1, &conf);
	assert_that(index, is_equal_to(grids_squared + NUM_OF_GRIDS + 1));

	index = three_to_one(-1, 0, 0, &conf);
	assert_that(index, is_equal_to(grids_squared * (NUM_OF_GRIDS - 1)));

	index = three_to_one(-1, -1, 0, &conf);
	assert_that(index, is_equal_to(grids_squared * (NUM_OF_GRIDS - 1) +
								   (NUM_OF_GRIDS * (NUM_OF_GRIDS -1))));

	index = three_to_one(-1, -1, -1, &conf);
	assert_that(index, is_equal_to(grids_squared * (NUM_OF_GRIDS - 1) +
								   (NUM_OF_GRIDS * (NUM_OF_GRIDS -1)) +
								   (NUM_OF_GRIDS - 1)));

	index = three_to_one(-NUM_OF_GRIDS/2, -NUM_OF_GRIDS/2, -NUM_OF_GRIDS/2, &conf);
	assert_that(index, is_equal_to(grids_squared * (NUM_OF_GRIDS/2) +
								   (NUM_OF_GRIDS * (NUM_OF_GRIDS/2)) +
								   (NUM_OF_GRIDS/2)));

	index = three_to_one(NUM_OF_GRIDS - 1, NUM_OF_GRIDS - 1, NUM_OF_GRIDS, &conf);
	assert_that(index, is_equal_to(grids_squared * (NUM_OF_GRIDS - 1) +
								   (NUM_OF_GRIDS * (NUM_OF_GRIDS - 1)) + 0));
}

TestSuite *three_to_one_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, three_to_one,
						  returns_right_results_for_a_trivial_input);
	return suite;
}
