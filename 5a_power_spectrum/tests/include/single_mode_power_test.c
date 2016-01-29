#include <math.h>
#include <complex.h>
#include <fftw3.h>
#include <cgreen/cgreen.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/grid/three_to_one.h"

#include "./../../src/include/single_mode_power.h"

Describe(single_mode_power);

BeforeEach(single_mode_power) {
}

AfterEach(single_mode_power) {
}

Ensure(single_mode_power, mirrors_specific_elements) {
	int dummy = 1;
	assert_that(dummy, is_equal_to(0));
}

TestSuite *single_mode_power_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, single_mode_power,
			mirrors_specific_elements);
	return suite;
}
