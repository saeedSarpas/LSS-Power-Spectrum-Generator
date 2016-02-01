#include <stdlib.h>
#include <math.h>

#include "./../../../global_structs/input_file_info.h"
#include "./../../../global_structs/config_struct.h"

void density_contrast(double *grid_mass, input_info_struct *info,
		config_struct *conf, double *grid_delta) {

	unsigned int n;
	size_t total_num_of_grids = pow(conf->num_of_grids_in_each_axis, 3);

	double grid_length = info->box_length / conf->num_of_grids_in_each_axis;
	double grid_block_volume = pow(grid_length, 3);

	double total_mass = 0.0;

	for (n = 0; n < total_num_of_grids; n++) {
		total_mass += grid_mass[n];
	}

	double mean_density = total_mass / pow(info->box_length, 3);

	for (n = 0; n < total_num_of_grids; n++) {
		grid_delta[n] = ((grid_mass[n] / grid_block_volume) / mean_density) - 1;
	}
}
