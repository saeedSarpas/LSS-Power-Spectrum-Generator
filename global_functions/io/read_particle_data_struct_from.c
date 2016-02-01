#include <stdio.h>
#include <stdlib.h>

#include "./../../global_structs/particle_data_struct.h"

void read_particle_data_struct_from(FILE * file, particle_data_struct * p,
									size_t size, char * file_path) {
	if (fread(p, sizeof(struct particle_data_struct_tag), size, file) != size) {
		printf("[Cannot read from file %s]", file_path);
		exit(0);
	}
}
