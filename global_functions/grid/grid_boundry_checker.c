#include <stdio.h>

#include "./../../global_structs/config_struct.h"

int grid_boundry_checker (int pos, config_struct *conf) {
	if (pos > conf->num_of_grids_in_each_axis - 1) {
		return pos - conf->num_of_grids_in_each_axis;
	} else if (pos < 0) {
		return pos + conf->num_of_grids_in_each_axis;
	} else {
		return pos;
	}
}
