#include <math.h>

#include "./../../../global_structs/modes_struct.h"
#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/grid/three_to_one.h"

void load_modes_into(modes *modes_array, config *conf) {
	int index, i, j, k;
	int half_grid_box_size = conf->num_of_grids_in_each_axis / 2;

	for (i = 0; i < conf->num_of_grids_in_each_axis; i++) {
		for (j = 0; j < conf->num_of_grids_in_each_axis; j++) {
			for (k = 0; k < conf->num_of_grids_in_each_axis; k++) {
				index = three_to_one(i, j, k, conf);
				modes_array[index].index = index;
				modes_array[index].i = i;
				modes_array[index].j = j;
				modes_array[index].k = k;
				modes_array[index].length = sqrt(
						pow(i - half_grid_box_size, 2)
						+ pow(j - half_grid_box_size, 2)
						+ pow(k - half_grid_box_size, 2));
			}
		}
	}
}
