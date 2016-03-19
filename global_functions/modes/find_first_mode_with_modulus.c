/**
 * find_first_mode_with_modulus.c
 * @test_file find_first_mode_with_modulus_test.c
 *
 * Using half-interval search algorithm to find the first occurance of a value
 * within a sorted array.
 * @see https://en.wikipedia.org/wiki/Binary_search_algorithm
 *
 * @param sorted_array Sorted array of modes
 * @param value Target value
 * @param array_length Logical length of the array
 *
 * @return The index of the first occurance of the target value. If the target
 * value does not exist in the array, it will return NOT_FOUND constant.
 *
 * TODO: Making a generic version of this function.
 *
 * @author Saeed Sarpas
 */

#include <math.h>

#include "./../../global_structs/modes_struct.h"

#define NOT_FOUND (-1)

int find_first_mode_with_modulus (modes_struct *sorted_array, double value,
                         int array_length) {

    int min = 0, max = array_length;
    int pointer = array_length >> 1;

    while (min < max) {
        if (sorted_array[pointer].modulus < value)
            min = pointer + 1;
        else
            max = pointer - 1;

        pointer = (max + min) >> 1;
    }

    /* In some cases the algorithm would be stuch in the previous element of
       the expected one */
    pointer = (sorted_array[min].modulus == value) ? min : min + 1;

    if (min == max && sorted_array[pointer].modulus == value)
        return pointer;
    else
        return NOT_FOUND;
}
