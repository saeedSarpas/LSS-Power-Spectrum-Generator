#include <math.h>

#include "./../../../global_structs/modes_struct.h"
#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/grid/three_to_one.h"

void load_modes_into(modes_struct *modes_array, config_struct *conf) {
	int index, i, j, k;
	int half_grid_box_size = conf->run_params.num_of_axis_grids / 2;

	for (i = 0; i < conf->run_params.num_of_axis_grids; i++) {
		for (j = 0; j < conf->run_params.num_of_axis_grids; j++) {
			for (k = 0; k < conf->run_params.num_of_axis_grids; k++) {
				index = three_to_one(i, j, k, conf);
				modes_array[index].index = index;
				modes_array[index].kx = i - half_grid_box_size;
				modes_array[index].ky = j - half_grid_box_size;
				modes_array[index].kz = k - half_grid_box_size;
				modes_array[index].modulus = sqrt(
						pow(i - half_grid_box_size, 2)
						+ pow(j - half_grid_box_size, 2)
						+ pow(k - half_grid_box_size, 2));
			}
		}
	}
}
