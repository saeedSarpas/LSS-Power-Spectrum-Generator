#include <stdio.h>
#include <stdlib.h>

#include "./../../global_structs/particle_data_struct.h"

void read_particle_data_struct_from(FILE * file, particle_data * p,
									size_t size, char * file_path) {
	if (fread(p, sizeof(particle_data), size, file) != size) {
		printf("[Cannot read from file %s]", file_path);
		exit(0);
	}
}
