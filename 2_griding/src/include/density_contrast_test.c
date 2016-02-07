#include <cgreen/cgreen.h>

#include "./../../../global_structs/input_file_info.h"
#include "./../../../global_structs/config_struct.h"

#include "./density_contrast.h"

Describe(density_contrast);

#define NUM_OF_GRIDS 2
#define TOT_NUM_OF_GRIDS 8
#define BOX_LENGTH 1
#define MASS 2.0
#define RANDOM -1.234567

static config_struct conf;
static input_info_struct info;
static double mass[TOT_NUM_OF_GRIDS];
static double delta[TOT_NUM_OF_GRIDS];

BeforeEach(density_contrast) {
	conf.num_of_grids_in_each_axis = NUM_OF_GRIDS;
	info.box_length = BOX_LENGTH;

	int i;
	for (i = 0; i < TOT_NUM_OF_GRIDS; i++) {
		mass[i] = MASS;
		delta[i] = RANDOM;
	}
}

AfterEach(density_contrast) {}

Ensure(density_contrast, returns_right_value_for_a_trivial_case) {
	density_contrast(mass, &info, &conf, delta);

	int i;
	for (i = 0; i < TOT_NUM_OF_GRIDS; i++)
		assert_that(delta[i], is_equal_to(0));
}

TestSuite *density_contrast_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, density_contrast,
						  returns_right_value_for_a_trivial_case);
	return suite;
}
