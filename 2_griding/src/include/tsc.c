#include <math.h>

#include "./../../../global_structs/particle_data_struct.h"
#include "./../../../global_structs/input_file_info.h"
#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/grid/move_along_grid_axis.h"
#include "./../../../global_functions/grid/three_to_one.h"

void tsc (particle_data_struct *P, double *grid_mass, input_info_struct *info,
		  config_struct *conf) {

	int i, n, a, b, c, index, pos[3], neighbor_pos[3];
	double overlap, weight[3][3];
	double grid_length = info->box_length / conf->run_params.num_of_axis_grids;

	for (n = 0; n < info->num_of_parts; n++) {
		for (i = 0; i < 3; i++) {
			pos[i] = P[n].Pos[i] / grid_length;
			overlap = fmodf(P[n].Pos[i], grid_length);

			double overlap_ratio = overlap/grid_length;

			weight[i][0] = 0.5  * pow((1 - overlap_ratio), 2);
			weight[i][1] = 0.75 - pow((overlap_ratio - 0.5), 2);
			weight[i][2] = 0.5  * pow(overlap_ratio, 2);
		}

		for (a = 0; a < 3; a++) {
			for (b = 0; b < 3; b++) {
				for (c = 0; c < 3; c++) {
					neighbor_pos[0] = move_along_grid_axis(pos[0], a - 1, conf);
					neighbor_pos[1] = move_along_grid_axis(pos[1], b - 1, conf);
					neighbor_pos[2] = move_along_grid_axis(pos[2], c - 1, conf);

					index = three_to_one(neighbor_pos[0], neighbor_pos[1],
										 neighbor_pos[2], conf);
					grid_mass[index] += weight[0][a] * weight[1][b] * weight[2][c]
						* P[n].Mass;
				}
			}
		}
	}
}
