#include <stdio.h>

#include "./../../global_structs/config_struct.h"

int grid_boundry_checker (int pos, config_struct *conf) {
	if (pos > conf->run_params.num_of_axis_grids - 1) {
		return pos - conf->run_params.num_of_axis_grids;
	} else if (pos < 0) {
		return pos + conf->run_params.num_of_axis_grids;
	} else {
		return pos;
	}
}
