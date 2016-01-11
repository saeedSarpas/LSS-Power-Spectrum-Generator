#include <stdio.h>
#include <stdlib.h>

#include "./../../global_structs/particle_data_struct.h"

void write_particle_data_struct_to(FILE * file, particle_data * p,
								   size_t nmemb, char * file_path) {
	if (fwrite(p, sizeof(particle_data), nmemb, file) != nmemb) {
		printf("[Cannot write to file %s]\n", file_path);
		exit(0);
	}
}
