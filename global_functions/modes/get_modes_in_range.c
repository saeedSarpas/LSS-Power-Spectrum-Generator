#include <math.h>

#include "./../../global_structs/modes_struct.h"
#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/vector_struct.h"

#include "./../../global_functions/vector/vector.h"

void get_modes_in_range (double min, double max, modes_struct *indexed_mode_modulus,
		config_struct *conf, vector_struct *modes_vector) {

	int tot_num_of_grids = pow(conf->run_params.num_of_axis_grids, 3);
	int pointer = tot_num_of_grids / 2;
	int jump_size = tot_num_of_grids / 4;

	while (jump_size > 2) {
		pointer = (indexed_mode_modulus[pointer].modulus > min) ? pointer - jump_size :
			pointer + jump_size;
		jump_size /= 2;
	}

	while (1) {
		if (pointer < 4) {
			pointer = 0;
			break;
		} else {
			pointer -= 4;
		}
		if (indexed_mode_modulus[pointer].modulus < min) break;
	}

	do {
		if (indexed_mode_modulus[pointer].modulus >= min &&
				indexed_mode_modulus[pointer].modulus < max) {
			vector_push(modes_vector, &indexed_mode_modulus[pointer]);
		}
		if (pointer < tot_num_of_grids) {
			pointer++;
		} else {
			break;
		}
	} while (indexed_mode_modulus[pointer].modulus <= max);
}
