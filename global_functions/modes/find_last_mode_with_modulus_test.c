/**
 * find_last_mode_with_modulus_test.c
 * @test_for find_last_mode_with_modulus.c
 *
 * @author Saeed Sarpas
 */

#include <cgreen/cgreen.h>
#include <math.h>
#include <string.h>

#include "./../../global_structs/modes_struct.h"
#include "./../../global_structs/config_struct.h"

#include "./find_last_mode_with_modulus.h"
#include "./sort_modes.h"

Describe(find_last_mode_with_modulus);

#define NUM_OF_AXIS_GRIDS (64)
#define ARRAY_LENGTH (64 * 64 * 64)
#define NUM_OF_OCCURANCE (10)
#define MAX_VALUE (100000)

static modes_struct modes_array[ARRAY_LENGTH];
static void create_an_ordered_array ();
static void fill_array_with_random_numbers ();

BeforeEach(find_last_mode_with_modulus) {}

AfterEach(find_last_mode_with_modulus) {}

Ensure(find_last_mode_with_modulus, returns_right_results_in_a_random_array) {

    fill_array_with_random_numbers();

    int i, index, end_point = 0;
    for (i = ARRAY_LENGTH - 2; i > 0; i--)
        if (modes_array[i +1].modulus > modes_array[i].modulus) {
            end_point = i + 1;
            break;
        }

    double value;

    for (i = 0; i < end_point; i += end_point / 20) {
        value = modes_array[i].modulus;
        index = find_last_mode_with_modulus(value, modes_array, ARRAY_LENGTH);
        assert_that(modes_array[index].modulus, is_equal_to(value));
        assert_true(modes_array[index + 1].modulus > value);
    }

    value = modes_array[ARRAY_LENGTH - 1].modulus;
    index = find_last_mode_with_modulus(value, modes_array, ARRAY_LENGTH);
    assert_that(index, is_equal_to(ARRAY_LENGTH - 1));
}

Ensure(find_last_mode_with_modulus,
       returns_correct_results_for_an_ordered_array) {

    create_an_ordered_array();

    int end_point = (ARRAY_LENGTH / NUM_OF_OCCURANCE) - NUM_OF_OCCURANCE;
    int i, index;
    double value;

    for (i = 0; i < end_point; i += end_point / 20) {
        index = find_last_mode_with_modulus(i, modes_array, ARRAY_LENGTH);
        assert_that(modes_array[index].modulus, is_equal_to(i));
        assert_true(modes_array[index + 1].modulus > i);
    }

    value = modes_array[ARRAY_LENGTH - 1].modulus;
    index = find_last_mode_with_modulus(value, modes_array, ARRAY_LENGTH);
    assert_that(index, is_equal_to(ARRAY_LENGTH - 1));
}

TestSuite *find_last_mode_with_modulus_tests() {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, find_last_mode_with_modulus,
                          returns_right_results_in_a_random_array);
    add_test_with_context(suite, find_last_mode_with_modulus,
                          returns_correct_results_for_an_ordered_array);
    return suite;
}

static void create_an_ordered_array () {
    int i;
    for (i = 0; i < ARRAY_LENGTH; i++)
        modes_array[i].modulus = i / NUM_OF_OCCURANCE;
}

static void fill_array_with_random_numbers () {
    int i;
    double random_number;
    for (i = 0; i < ARRAY_LENGTH; i++) {
        random_number = (double)rand()/(double)RAND_MAX * MAX_VALUE;
        modes_array[i].modulus = random_number;
    }

    config_struct conf = {.params.numOfAxisGrids = NUM_OF_AXIS_GRIDS};
    sort_modes(modes_array, &conf);
}
