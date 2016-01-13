#include <stdio.h>
#include <stdlib.h>

#include "./../../../global_structs/particle_data_struct.h"
#include "./../../../global_structs/input_file_infos.h"

#include "./../../../global_functions/open_file.h"
#include "./../../../global_functions/io/read_particle_data_struct_from.h"

void load_input(particle_data P[], char *input_path, input_file_infos *info) {

	FILE * input_file;

	open_file(&input_file, input_path, "rb");

	read_particle_data_struct_from(input_file, P, info->num_of_parts, input_path);

	fclose(input_file);
}
