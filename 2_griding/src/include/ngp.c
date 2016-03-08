#include "./../../../global_functions/grid/three_to_one.h"

#include "./../../../global_structs/particle_struct.h"
#include "./../../../global_structs/info_strcut.h"
#include "./../../../global_structs/config_struct.h"

void ngp (particle_struct *P, double *grid_mass, info_struct *info,
		  config_struct *conf) {

	int i, j, k, n;

	double grid_length = info->boxLength / conf->params.numOfAxisGrids;

	for (n = 1; n < info->numOfParts; n++) {
		i = P[n].Pos[0] / grid_length;
		j = P[n].Pos[1] / grid_length;
		k = P[n].Pos[2] / grid_length;

		int index = three_to_one(i, j, k, conf);

		grid_mass[index] += P->Mass;
	}
}
