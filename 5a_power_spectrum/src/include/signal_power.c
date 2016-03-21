/**
 * signal_power.c
 * @test_file signal_power_test.c
 *
 * Calculating the power of a signal (or more accurately all the signals within
 * k_min <= mode_modulus < k_max).
 *
 * @param k_min Minimum of the mode modulus
 * @param k_max Maximum of the mode modulus
 * @param delta_fourier Fourier density contrast array
 * @param sorted_modes_array Sorted array of modes
 * @param conf Configurations
 *
 * @return signal_power_result_struct which contains the power of the signal and
 * its error (the error is calculated using the standard deviation of the
 * powers)
 *
 * @author Saeed Sarpas
 */

#include <stdlib.h>
#include <complex.h>
#include <fftw3.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/vector_struct.h"
#include "./../../../global_structs/modes_struct.h"

#include "./../../../global_functions/vector/vector.h"

#include "./../../../global_functions/modes/find_first_mode_greater_than_or_equal_to.h"
#include "./../../../global_functions/grid/three_to_one.h"

#include "./../struct/signal_power_result.h"

#include "./../include/generate_logarithmic_bins.h"

typedef struct {
    double mode_power;
    double error;
} variance_result_struct;

static variance_result_struct variance(vector_struct *powers_vector) {

    variance_result_struct result;
    result.mode_power = 0.0;
    result.error = 0.0;

    unsigned int i;
    double power;
    for (i = 0; i < powers_vector->log_length; i++) {
        vector_get_elem(powers_vector, i, &power);
        result.mode_power += power;
    }

    result.mode_power /= powers_vector->log_length;

    int tot_num_of_powers = powers_vector->log_length;

    double error = 0.0;
    while (powers_vector->log_length > 0) {
        vector_pop(powers_vector, &power);
        error += pow(power - result.mode_power, 2);
    }

    result.error = sqrt(error) / tot_num_of_powers;

    return result;
}

signal_power_result_struct signal_power (double k_min, double k_max,
                                         fftw_complex *delta_fourier,
                                         modes_struct *sorted_modes_array,
                                         config_struct *conf) {

    signal_power_result_struct result;

    size_t tot_num_of_grids = pow(conf->params.numOfAxisGrids, 3);

    int min_index = find_first_mode_greater_than_or_equal_to(
        k_min, sorted_modes_array, tot_num_of_grids);
    int max_index = find_first_mode_greater_than_or_equal_to(
        k_max, sorted_modes_array, tot_num_of_grids);

    vector_struct powers_vector;
    vector_new(&powers_vector, sizeof(double), max_index - min_index + 1);

    double power;
    int i;
    for (i = min_index; i < max_index; i++) {
        power = pow(creal(delta_fourier[sorted_modes_array[i].index]), 2) +
            pow(cimag(delta_fourier[sorted_modes_array[i].index]), 2);

        vector_push(&powers_vector, &power);
    }

    result.num_of_found_modes = max_index - min_index - 1;

    if (result.num_of_found_modes == 0) {
        /* There is a memory leak here! Exiting before disposing powers vector*/
        printf("\n[Found no point in this shell: %f <= k < %f]\n", k_min, k_max);
        exit(EXIT_FAILURE);
    } else {
        variance_result_struct variance_result = variance(&powers_vector);
        result.mode_power = variance_result.mode_power;
        result.error = variance_result.error;
    }

    vector_dispose(&powers_vector);

    return result;
}
