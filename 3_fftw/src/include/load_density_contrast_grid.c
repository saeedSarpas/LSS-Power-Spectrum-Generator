#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/open_file.h"
#include "./../../../global_functions/io/read_double_from.h"

void load_density_contrast_grid(char *path, double *grid_delta,
		config_struct *conf) {

	FILE *file;
	open_file(&file, path, "rb");

	size_t tot_num_of_grids = pow(conf->num_of_grids_in_each_axis, 3);

	read_double_from(file, path, grid_delta, tot_num_of_grids);

	fclose(file);
}
