#include "./../../../global_functions/grid/three_to_one.h"

#include "./../../../global_structs/particle_data_struct.h"
#include "./../../../global_structs/input_file_info.h"
#include "./../../../global_structs/config_struct.h"

void ngp (particle_data_struct *P, double *grid_mass, input_info_struct *info,
		  config_struct *conf) {

	int i, j, k, n;

	double grid_length = info->box_length / conf->num_of_grids_in_each_axis;

	for (n = 1; n < info->num_of_parts; n++) {
		i = P[n].Pos[0] / grid_length;
		j = P[n].Pos[1] / grid_length;
		k = P[n].Pos[2] / grid_length;

		int index = three_to_one(i, j, k, conf);

		grid_mass[index] += P->Mass;
	}
}
