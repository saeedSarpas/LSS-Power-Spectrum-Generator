/**
 * signal_power_test.c
 * @test_for signal_power.c
 *
 * @author Saeed Sarpas
 */

#include <cgreen/cgreen.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/memory/allocate.h"
#include "./../../../global_functions/grid/three_to_one.h"
#include "./../../../global_functions/modes/sort_modes.h"

#include "./../../src/struct/signal_power_result.h"

#include "./../../src/include/signal_power.h"
#include "./../../src/include/generate_logarithmic_bins.h"

Describe(signal_power);

#define NUM_OF_GRIDS 128
#define DELTA_FOURIER_REAL_PART 1.0
#define DELTA_FOURIER_IMAG_PART 1.0

static config_struct conf;
static fftw_complex *delta_fourier;
static modes_struct *indexed_mode_modulus;
static int tot_num_of_grids;
static void fill_delta_fourier();
static void fill_indexed_mode_modulus();

BeforeEach(signal_power) {
    conf.params.numOfAxisGrids = NUM_OF_GRIDS;
    tot_num_of_grids = pow(conf.params.numOfAxisGrids, 3);
    allocate((void **)&delta_fourier, tot_num_of_grids, sizeof(fftw_complex));
    allocate((void **)&indexed_mode_modulus, pow(NUM_OF_GRIDS, 3),
             sizeof(modes_struct));
}

AfterEach(signal_power) {
    free(delta_fourier);
    free(indexed_mode_modulus);
}

Ensure(signal_power, returns_right_results_for_a_trivial_input) {
    fill_delta_fourier();
    fill_indexed_mode_modulus();

    signal_power_result_struct result;
    result = signal_power(0.5, 10000.5, delta_fourier,
                          indexed_mode_modulus, &conf);

    double power = pow(DELTA_FOURIER_REAL_PART, 2) +
        pow(DELTA_FOURIER_IMAG_PART, 2);

    assert_that(result.mode_power, is_equal_to(power));
    assert_that(result.error, is_equal_to(0));
    assert_that(result.num_of_found_modes, is_equal_to(9999));
}

TestSuite *signal_power_tests() {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, signal_power,
                          returns_right_results_for_a_trivial_input);
    return suite;
}

void fill_delta_fourier() {
    int i;
    for(i = 0; i < tot_num_of_grids; i++)
        delta_fourier[i] = DELTA_FOURIER_REAL_PART + DELTA_FOURIER_IMAG_PART * I;
}

void fill_indexed_mode_modulus() {
    int index, i, j, k;
    for (i = 0; i < NUM_OF_GRIDS; i++) {
        for (j = 0; j < NUM_OF_GRIDS; j++) {
            for (k = 0; k < NUM_OF_GRIDS; k++) {
                index = three_to_one(i, j, k, &conf);
                indexed_mode_modulus[index].index = index;
                indexed_mode_modulus[index].kx = i - (NUM_OF_GRIDS / 2);
                indexed_mode_modulus[index].ky = j - (NUM_OF_GRIDS / 2);
                indexed_mode_modulus[index].kz = k - (NUM_OF_GRIDS / 2);
                indexed_mode_modulus[index].modulus = index;
            }
        }
    }

    sort_modes(indexed_mode_modulus, &conf);
}
