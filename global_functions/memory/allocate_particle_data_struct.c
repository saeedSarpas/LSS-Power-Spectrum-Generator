#include <stdio.h>
#include <stdlib.h>

#include "./allocation_failing_message.h"
#include "./../../global_structs/particle_data_struct.h"

void allocate_particle_data_struct (particle_data_struct ** p, size_t size) {
	if ( !(*p = calloc(size, sizeof(struct particle_data_struct_tag)))) {
		allocation_failing_message("struct particle data", size);
		exit(0);
	}
}
