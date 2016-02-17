#include <stdio.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/input_file_info.h"

#include "./str_concat.h"

void append_fourier_transformed_filename(char *input_alias,
		char *algorithm_alias, input_info_struct *info, config_struct *conf,
		char **path) {

	char num_of_grids_in_each_axis[16];
	sprintf(num_of_grids_in_each_axis, "%d", conf->run_params.num_of_axis_grids);

	char num_of_parts[16];
	sprintf(num_of_parts, "%d", info->num_of_parts);

	char *strings[] = {"fourier-transformed-grid-", algorithm_alias, "-",
		num_of_grids_in_each_axis, "-", input_alias, "-", num_of_parts, ".dat"};

	str_concat(strings, 9, path);
}

