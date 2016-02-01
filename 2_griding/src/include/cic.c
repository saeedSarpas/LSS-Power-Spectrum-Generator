#include <math.h>

#include "./../../../global_functions/grid/three_to_one.h"

#include "./../../../global_structs/particle_data_struct.h"
#include "./../../../global_structs/input_file_info.h"
#include "./../../../global_structs/config_struct.h"

void cic_weigth (int * d_index, double overlap, double * weight,
		double grid_length) {

	double grid_half_size = grid_length / 2.0;

	if (overlap > grid_half_size) {
		*weight = 1 - (overlap / grid_length) + 0.5;
		*d_index = +1;
	} else {
		*weight = (overlap / grid_length) + 0.5;
		*d_index = -1;
	}
}

void cic (particle_data_struct P[], double *grid_mass, input_info_struct *info,
		  config_struct *conf) {

	int i, j, k, n, index;
	int di, dj, dk;

	double i_weight, j_weight, k_weight, overlap;
	double grid_length = info->box_length / conf->num_of_grids_in_each_axis;

	for (n = 0; n < info->num_of_parts; n++) {
		i = P[n].Pos[0] / grid_length;
		overlap = fmodf(P[n].Pos[0], grid_length);
		cic_weigth(&di, overlap, &i_weight, grid_length);

		j = P[n].Pos[1] / grid_length;
		overlap = fmodf(P[n].Pos[1], grid_length);
		cic_weigth(&dj, overlap, &j_weight, grid_length);

		k = P[n].Pos[2] / grid_length;
		overlap = fmodf(P[n].Pos[2], grid_length);
		cic_weigth(&dk, overlap, &k_weight, grid_length);

		index = three_to_one(i, j, k, conf);
		grid_mass[index] += i_weight * j_weight * k_weight * P[n].Mass;

		index = three_to_one(i+di, j, k, conf);
		grid_mass[index] += (1 - i_weight) * j_weight * k_weight * P[n].Mass;

		index = three_to_one(i, j+dj, k, conf);
		grid_mass[index] += i_weight * (1 - j_weight) * k_weight * P[n].Mass;

		index = three_to_one(i, j, k+dk, conf);
		grid_mass[index] += i_weight * j_weight * (1 - k_weight) * P[n].Mass;

		index = three_to_one(i+di, j+dj, k, conf);
		grid_mass[index] += (1 - i_weight) * (1 - j_weight) * k_weight * P[n].Mass;

		index = three_to_one(i, j+dj, k+dk, conf);
		grid_mass[index] += i_weight * (1 - j_weight) * (1 - k_weight) * P[n].Mass;

		index = three_to_one(i+di, j, k+dk, conf);
		grid_mass[index] += (1 - i_weight) * j_weight * (1 - k_weight) * P[n].Mass;

		index = three_to_one(i+di, j+dj, k+dk, conf);
		grid_mass[index] += (1 - i_weight) * (1 - j_weight) * (1 - k_weight) * P[n].Mass;
	}
}
