#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./../../global_structs/modes_struct.h"

void read_modes_struct_from(FILE *file, char *path, modes *indexed_modes,
		size_t size) {
	if (fread(indexed_modes, sizeof(modes), size, file) != size) {
		printf("[Cannot read from file %s]", path);
		exit(0);
	};
}
