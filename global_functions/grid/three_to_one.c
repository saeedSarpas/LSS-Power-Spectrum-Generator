#include <math.h>

#include "./grid_boundry_checker.h"

#include "./../../global_structs/config_struct.h"

int three_to_one (int i, int j, int k, config_struct *conf) {
	i = grid_boundry_checker(i, conf);
	j = grid_boundry_checker(j, conf);
	k = grid_boundry_checker(k, conf);

	// It should be row major (since FFTW is using row major)
	return (i * pow(conf->run_params.num_of_axis_grids, 2)) +
		(j * conf->run_params.num_of_axis_grids) + k;
}
