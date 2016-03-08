#include <stdlib.h>
#include <math.h>

#include "./../../../global_structs/info_strcut.h"
#include "./../../../global_structs/config_struct.h"

void density_contrast(double *grid_mass, info_struct *info,
		config_struct *conf, double *grid_delta) {

	unsigned int n;
	size_t total_num_of_grids = pow(conf->params.numOfAxisGrids, 3);

	double grid_length = info->boxLength / conf->params.numOfAxisGrids;
	double grid_block_volume = pow(grid_length, 3);

	double total_mass = 0.0;

	for (n = 0; n < total_num_of_grids; n++) {
		total_mass += grid_mass[n];
	}

	double mean_density = total_mass / pow(info->boxLength, 3);

	for (n = 0; n < total_num_of_grids; n++) {
		grid_delta[n] = ((grid_mass[n] / grid_block_volume) / mean_density) - 1;
	}
}
