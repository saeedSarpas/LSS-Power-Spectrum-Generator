#include <stdio.h>
#include <stdlib.h>

#include "./../../../global_structs/particle_struct.h"
#include "./../../../global_structs/info_strcut.h"

#include "./../../../global_functions/io/open_file.h"
#include "./../../../global_functions/io/read_from.h"

void load_input(particle_struct *P, char *input_path, info_struct *info) {

	FILE *input_file;
	open_file(&input_file, input_path, "rb");

	read_from(input_file, info->numOfParts, sizeof(struct particle),
			  (void *)P);

	fclose(input_file);
}
