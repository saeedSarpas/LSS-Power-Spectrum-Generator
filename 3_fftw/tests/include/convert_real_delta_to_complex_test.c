#include <cgreen/cgreen.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/memory/allocate_fftw_complex.h"
#include "./../../../global_functions/grid/three_to_one.h"

#include "./../../src/include/convert_real_delta_to_complex.h"

Describe(convert_real_delta_to_complex);

BeforeEach(convert_real_delta_to_complex) {
}

AfterEach(convert_real_delta_to_complex) {
}

Ensure(convert_real_delta_to_complex, puts_zero_in_the_imaginary_part) {
	config conf;
	conf.num_of_grids_in_each_axis = 2;

	double delta_real[8] = {1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2, 1.2};
	fftw_complex *delta_complex;
	allocate_fftw_complex(&delta_complex, 8);

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
	add_test_with_context(suite, convert_real_delta_to_complex, puts_zero_in_the_imaginary_part);
	return suite;
}
