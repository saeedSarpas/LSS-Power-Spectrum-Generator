#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./../../global_structs/modes_struct.h"
#include "./../../global_structs/config_struct.h"

void read_modes_struct_from(FILE *file, char *path, modes *modes,
		size_t size, config *conf) {
	int tot_num_of_grids = pow(conf->num_of_grids_in_each_axis, 3);
	if ( fread(modes, sizeof(modes), tot_num_of_grids, file)
			!= tot_num_of_grids) {
		printf("[Cannot read from file %s]", path);
		exit(0);
	};
}
