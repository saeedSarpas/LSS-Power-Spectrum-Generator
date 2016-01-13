#include <math.h>

#include "./grid_boundry_checker.h"

#include "./../../global_structs/config_struct.h"

int three_to_one (int i, int j, int k, config *conf) {
	i = grid_boundry_checker(i, conf);
	j = grid_boundry_checker(j, conf);
	k = grid_boundry_checker(k, conf);

	// It should be row major (since FFTW is using row major)
	return (i * pow(conf->num_of_grids_in_each_axis, 2)) +
		(j * conf->num_of_grids_in_each_axis) + k;
}
