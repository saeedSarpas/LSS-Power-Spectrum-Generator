/**
 * find_first_mode_greater_than_or_equal_to.c
 * @test_file find_first_mode_greater_than_or_equal_to_test.c
 *
 * Using half-interval search algorithm to find the first mode with mode modulus
 * greater than or equal to target value
 * @see https://en.wikipedia.org/wiki/Binary_search_algorithm
 *
 * @param value Target value
 * @param sorted_array Sorted array of modes
 * @param array_length Logical length of the array
 *
 * @return The index of the first mode with mode modulus greater than or equal
 * to the target value. If there is no mode greater than target value, the
 * function will return the NOT_FOUND constant.
 *
 * TODO: Making a generic version of this function.
 *
 * @author Saeed Sarpas
 */

#include <math.h>

#include "./../../global_structs/modes_struct.h"

#define NOT_FOUND (-1)

int find_first_mode_greater_than_or_equal_to (
    double value, modes_struct *sorted_array, int array_length) {

    int min = 0, max = array_length - 1;
    int pointer = array_length >> 1;

    while (min + 1 < max) {
        if (sorted_array[pointer].modulus < value)
            min = pointer + 1;
        else
            max = pointer;

        pointer = (max + min) >> 1;
    }

    /* In some cases the algorithm would be stuch in the previous element of
       the expected one */
    pointer = (sorted_array[max - 1].modulus >= value) ? max - 1 : max;

    if (sorted_array[pointer].modulus >= value)
        return pointer;
    else
        return NOT_FOUND;
}
