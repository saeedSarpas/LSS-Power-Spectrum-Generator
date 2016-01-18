#include <stdio.h>

#include "./../../global_structs/config_struct.h"

#include "./str_concat.h"

void append_indexed_modes_filename(char **return_path, config *conf) {

	char num_of_grids_in_each_axis[3];
	sprintf(num_of_grids_in_each_axis, "%d", conf->num_of_grids_in_each_axis);

  char * strings[] = {"indexed-modes-", num_of_grids_in_each_axis, ".dat"};

  str_concat(strings, 3, return_path);
}

