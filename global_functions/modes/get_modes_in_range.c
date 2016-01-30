#include <math.h>

#include "./../../global_structs/modes_struct.h"
#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/vector_struct.h"

#include "./../../global_functions/vector/vector.h"

void get_modes_in_range (double min, double max, modes *indexed_mode_modulus,
		config *conf, vector *modes_vector) {

	int total_num_of_grids = pow(conf->num_of_grids_in_each_axis, 3);
	int pointer = total_num_of_grids / 2;
	int jump_size = total_num_of_grids / 4;

	while (jump_size > 2) {
		pointer = (indexed_mode_modulus[pointer].length > min) ? pointer - jump_size :
			pointer + jump_size;
		jump_size /= 2;
	}

	while (1) {
		pointer -= 4;
		if (indexed_mode_modulus[pointer].length < min) break;
	}

	do {
		pointer++;
		if (indexed_mode_modulus[pointer].length > min &&
				indexed_mode_modulus[pointer].length <= max) {
			vector_push(modes_vector, &indexed_mode_modulus[pointer]);
		}
	} while (indexed_mode_modulus[pointer].length <= max);
}
