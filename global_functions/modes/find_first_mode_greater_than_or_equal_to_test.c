/**
 * find_first_mode_greater_than_or_equal_to_test.c
 * @test_for find_first_mode_greater_than_or_equal_to.c
 *
 * @author Saeed Sarpas
 */

#include <cgreen/cgreen.h>
#include <math.h>
#include <string.h>

#include "./../../global_structs/modes_struct.h"
#include "./../../global_structs/config_struct.h"

#include "./find_first_mode_greater_than_or_equal_to.h"
#include "./sort_modes.h"

Describe(find_first_mode_greater_than_or_equal_to);

#define NUM_OF_AXIS_GRIDS (64)
#define ARRAY_LENGTH (64 * 64 * 64)
#define NUM_OF_OCCURANCE (10)
#define MAX_VALUE (100000)
#define NOT_FOUND (-1)

static modes_struct modes_array[ARRAY_LENGTH];
static void create_an_ordered_array ();
static void fill_array_with_random_numbers ();

BeforeEach(find_first_mode_greater_than_or_equal_to) {}

AfterEach(find_first_mode_greater_than_or_equal_to) {}

Ensure(find_first_mode_greater_than_or_equal_to,
       returns_right_results_in_a_random_array) {

    fill_array_with_random_numbers();

    int i, index, start_point = ARRAY_LENGTH;
    for (i = 1; i < ARRAY_LENGTH; i++) {
        if (modes_array[i - 1].modulus != modes_array[i].modulus) {
            start_point = i - 1;
            break;
        }
    }

    double value;

    value = modes_array[0].modulus;
    index = find_first_mode_greater_than_or_equal_to(value, modes_array,
                                                     ARRAY_LENGTH);
    assert_that(index, is_equal_to(start_point));


    for (i = start_point; i < ARRAY_LENGTH; i += ARRAY_LENGTH / 20) {
        value = floor(modes_array[i].modulus);
        index = find_first_mode_greater_than_or_equal_to(value, modes_array, ARRAY_LENGTH);
        assert_true(modes_array[index - 1].modulus <= value);
        assert_true(modes_array[index].modulus > value);
        assert_true(modes_array[index + 1].modulus > value);
    }

    value = modes_array[ARRAY_LENGTH - 1].modulus + 1;
    index = find_first_mode_greater_than_or_equal_to(value, modes_array,
                                                     ARRAY_LENGTH);
    assert_that(index, is_equal_to(NOT_FOUND));
}

Ensure(find_first_mode_greater_than_or_equal_to,
       returns_correct_results_for_an_ordered_array) {

    create_an_ordered_array();

    int i, index, max_value = ARRAY_LENGTH / NUM_OF_OCCURANCE;
    double value;

    value = modes_array[0].modulus;
    index = find_first_mode_greater_than_or_equal_to(value, modes_array,
                                                     ARRAY_LENGTH);
    assert_that(index, is_equal_to(0));

    for (i = NUM_OF_OCCURANCE; i < max_value; i += max_value / 20) {
        value = i / NUM_OF_OCCURANCE + .5;
        index = find_first_mode_greater_than_or_equal_to(value, modes_array,
                                                         ARRAY_LENGTH);
        assert_true(modes_array[index + 1].modulus > value);
        assert_true(modes_array[index].modulus >= value);
        assert_true(modes_array[index - 1].modulus < value);
    }

    value = modes_array[ARRAY_LENGTH - 1].modulus + 1;
    index = find_first_mode_greater_than_or_equal_to(value, modes_array,
                                                     ARRAY_LENGTH);
    assert_that(index, is_equal_to(NOT_FOUND));
}

TestSuite *find_first_mode_greater_than_or_equal_to_tests() {
    TestSuite *suite = create_test_suite();
    add_test_with_context(suite, find_first_mode_greater_than_or_equal_to,
                          returns_right_results_in_a_random_array);
    add_test_with_context(suite, find_first_mode_greater_than_or_equal_to,
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
