#include <cgreen/cgreen.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/grid/three_to_one.h"

#include "./../../src/include/convert_real_delta_to_complex.h"

Describe(convert_real_delta_to_complex);

#define NUM_OF_GRIDS 2
#define TOT_NUM_OF_GRIDS 8
#define DELTA 1.2

static config_struct conf;
static double delta_real[TOT_NUM_OF_GRIDS];
static fftw_complex delta_complex[TOT_NUM_OF_GRIDS];

BeforeEach(convert_real_delta_to_complex) {
	conf.params.numOfAxisGrids = NUM_OF_GRIDS;

	int i;
	for (i = 0; i < TOT_NUM_OF_GRIDS; i++)
		delta_real[i] = DELTA;
}
AfterEach(convert_real_delta_to_complex) {}

Ensure(convert_real_delta_to_complex, puts_zero_in_the_imaginary_part) {
	convert_real_delta_to_complex(delta_real, delta_complex, &conf);

	int i, j, k;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			for (k = 0; k < 2; k++) {
				int index = three_to_one(i, j, k, &conf);
				assert_that(creal(delta_complex[index]), is_equal_to(1.2));
				assert_that(cimag(delta_complex[index]), is_equal_to(0.0));
			}
		}
	}
}

TestSuite *convert_real_delta_to_complex_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, convert_real_delta_to_complex,
						  puts_zero_in_the_imaginary_part);
	return suite;
}
