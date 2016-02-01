#include <cgreen/cgreen.h>

#include "./../../../global_structs/input_file_info.h"
#include "./../../../global_structs/config_struct.h"

#include "./../../src/include/density_contrast.h"

Describe(density_contrast);
BeforeEach(density_contrast) {}
AfterEach(density_contrast) {}

Ensure(density_contrast, returns_right_value_for_a_trivial_case) {
	input_info_struct info;
	info.box_length = 1;

	config_struct conf;
	conf.num_of_grids_in_each_axis = 2;

	double mass[8] = {2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0};
	double delta[8] = {-1.23, -1.23, -1.23, -1.23, -1.23, -1.23, -1.23, -1.23};

	density_contrast(mass, &info, &conf, delta);

	int i;
	for (i = 0; i < 8; i++) {
		assert_that(delta[i], is_equal_to(0));
	}
}

TestSuite *density_contrast_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, density_contrast, returns_right_value_for_a_trivial_case);
	return suite;
}
