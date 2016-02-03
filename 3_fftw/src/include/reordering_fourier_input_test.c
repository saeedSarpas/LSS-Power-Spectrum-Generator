#include <cgreen/cgreen.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/grid/three_to_one.h"

#include "./reordering_fourier_input.h"

Describe(reordering_fourier_input);
BeforeEach(reordering_fourier_input) {}
AfterEach(reordering_fourier_input) {}

Ensure(reordering_fourier_input, mirrors_specific_elements) {
	config_struct conf;
	conf.num_of_grids_in_each_axis = 2;

	fftw_complex delta_complex[8];
	int i;
	for (i = 0; i < 8; i ++)
		delta_complex[i] = 1.2 + 3.4 * I;

	reordering_fourier_input(delta_complex, &conf);

	int j, k;
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

Ensure(reordering_fourier_input, puts_dc_component_at_the_center_of_delta_dourier) {
	config_struct conf;
	conf.num_of_grids_in_each_axis = 4;

	int rank[3] = {4, 4, 4};
	fftw_complex delta_complex[64];
	fftw_complex delta_fourier[64];

	fftw_plan p;
	p = fftw_plan_dft(3, rank, delta_complex, delta_fourier, FFTW_FORWARD,
						FFTW_MEASURE);

	int i;
	for (i = 0; i < 64; i ++)
		delta_complex[i] = 1.2 + 3.4 * I;

	fftw_execute(p);
	fftw_complex dc = delta_fourier[0];

	reordering_fourier_input(delta_complex, &conf);

	fftw_execute(p);


	int index = three_to_one(2, 2, 2, &conf);
	assert_that(creal(delta_fourier[index]), is_equal_to(creal(dc)));
	assert_that(cimag(delta_fourier[index]), is_equal_to(cimag(dc)));

	fftw_destroy_plan(p);
}

TestSuite *reordering_fourier_input_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, reordering_fourier_input, mirrors_specific_elements);
	add_test_with_context(suite, reordering_fourier_input, puts_dc_component_at_the_center_of_delta_dourier);
	return suite;
}
