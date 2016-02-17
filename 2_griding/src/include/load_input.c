#include <stdio.h>
#include <stdlib.h>

#include "./../../../global_structs/particle_data_struct.h"
#include "./../../../global_structs/input_file_info.h"

#include "./../../../global_functions/io/open_file.h"
#include "./../../../global_functions/io/read_from.h"

void load_input(particle_data_struct *P, char *input_path,
		input_info_struct *info) {

	FILE *input_file;
	open_file(&input_file, input_path, "rb");

	read_from(input_file, info->num_of_parts, sizeof(particle_data_struct),
			  (void *)P);

	fclose(input_file);
}
