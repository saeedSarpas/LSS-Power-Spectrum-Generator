#include <stdio.h>

#include "./str_concat.h"

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/input_file_info.h"

void append_power_spectrum_filename(char *input_alias, char *algorithm_alias,
		config_struct *conf, input_info_struct *info, char **path) {

	char num_of_grids_in_each_axis[16];
	sprintf(num_of_grids_in_each_axis, "%d", conf->num_of_grids_in_each_axis);

	char num_of_parts[16];
	sprintf(num_of_parts, "%d", info->num_of_parts);

	char * strings[] = {"power-spectrum-", algorithm_alias, "-",
		num_of_grids_in_each_axis, "-", input_alias, "-", num_of_parts, ".dat"};

	str_concat(strings, 9, path);
}

