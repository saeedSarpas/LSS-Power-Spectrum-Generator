#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/io/open_file.h"
#include "./../../../global_functions/io/read_from.h"

void load_density_contrast_grid(char *path, double *grid_delta,
		config_struct *conf) {

	FILE *file;
	open_file(&file, path, "rb");

	size_t tot_num_of_grids = pow(conf->params.numOfAxisGrids, 3);

	read_from(file, tot_num_of_grids, sizeof(double), (void *)grid_delta);

	fclose(file);
}
