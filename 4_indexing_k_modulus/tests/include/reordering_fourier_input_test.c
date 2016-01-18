#include <math.h>
#include <complex.h>
#include <fftw3.h>
#include <cgreen/cgreen.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/grid/three_to_one.h"

#include "./../../src/include/reordering_fourier_input.h"

Describe(reordering_fourier_input);

BeforeEach(reordering_fourier_input) {
}

AfterEach(reordering_fourier_input) {
}

Ensure(reordering_fourier_input, mirrors_specific_elements) {
	config conf;
	conf.num_of_grids_in_each_axis = 2;

	fftw_complex delta_complex[8] = {
		1.2 + 3.4 * I,
		1.2 + 3.4 * I,
		1.2 + 3.4 * I,
		1.2 + 3.4 * I,
		1.2 + 3.4 * I,
		1.2 + 3.4 * I,
		1.2 + 3.4 * I,
		1.2 + 3.4 * I
	};

	reordering_fourier_input(delta_complex, &conf);

	int i, j, k;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			for (k = 0; k < 2; k++) {
				int s = pow(-1, (i + j + k));
				int index = three_to_one(i, j, k, &conf);
				assert_that(creal(delta_complex[index]), is_equal_to(s * 1.2));
				assert_that(cimag(delta_complex[index]), is_equal_to(s * 3.4));
			}
		}
	}
}

TestSuite *reordering_fourier_input_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, reordering_fourier_input, mirrors_specific_elements);
	return suite;
}
