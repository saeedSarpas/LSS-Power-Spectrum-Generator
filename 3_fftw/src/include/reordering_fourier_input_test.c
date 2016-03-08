#include <cgreen/cgreen.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/grid/three_to_one.h"

#include "./reordering_fourier_input.h"

Describe(reordering_fourier_input);

#define NUM_OF_GRIDS 4
#define TOT_NUM_OF_GRIDS 64
#define REAL_PART 1.2
#define IMAG_PART 3.4

static config_struct conf;
static fftw_complex delta_complex[TOT_NUM_OF_GRIDS];
static void fill_delta_complex(fftw_complex*);

BeforeEach(reordering_fourier_input) {
	conf.params.numOfAxisGrids = NUM_OF_GRIDS;
	fill_delta_complex(delta_complex);
}

AfterEach(reordering_fourier_input) {}

Ensure(reordering_fourier_input, mirrors_right_elements) {
	reordering_fourier_input(delta_complex, &conf);

	int i, j, k;
	for (i = 0; i < conf.params.numOfAxisGrids; i++) {
		for (j = 0; j < conf.params.numOfAxisGrids; j++) {
			for (k = 0; k < conf.params.numOfAxisGrids; k++) {
				int s = pow(-1, (i + j + k));
				int index = three_to_one(i, j, k, &conf);
				assert_that(creal(delta_complex[index]),
							is_equal_to(s * REAL_PART));
				assert_that(cimag(delta_complex[index]),
							is_equal_to(s * IMAG_PART));
			}
		}
	}
}

Ensure(reordering_fourier_input,
	   puts_dc_component_at_the_center_of_delta_fourier) {
	fftw_complex delta_fourier[TOT_NUM_OF_GRIDS];
	int rank[3] = {NUM_OF_GRIDS, NUM_OF_GRIDS, NUM_OF_GRIDS};
	fftw_plan plan = fftw_plan_dft(3, rank, delta_complex, delta_fourier,
								   FFTW_FORWARD, FFTW_MEASURE);

	fill_delta_complex(delta_complex);

	reordering_fourier_input(delta_complex, &conf);
	fftw_execute(plan);

	fftw_complex dc = TOT_NUM_OF_GRIDS * (REAL_PART + IMAG_PART * I);

	int index = three_to_one(NUM_OF_GRIDS/2, NUM_OF_GRIDS/2, NUM_OF_GRIDS/2,
							 &conf);
	assert_that(creal(delta_fourier[index]), is_equal_to(creal(dc)));
	assert_that(cimag(delta_fourier[index]), is_equal_to(cimag(dc)));

	fftw_destroy_plan(plan);
}

TestSuite *reordering_fourier_input_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, reordering_fourier_input,
						  mirrors_right_elements);
	add_test_with_context(suite, reordering_fourier_input,
						  puts_dc_component_at_the_center_of_delta_fourier);
	return suite;
}

void fill_delta_complex(fftw_complex *d) {
	int i;
	for (i = 0; i < TOT_NUM_OF_GRIDS; i++)
		d[i] = REAL_PART + IMAG_PART * I;
}
