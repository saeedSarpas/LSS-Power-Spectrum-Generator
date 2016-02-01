#include <stdio.h>
#include <stdlib.h>

#include "./../../global_structs/modes_struct.h"

void write_modes_struct_to(FILE *file, modes_struct *m, size_t nmemb,
		char *file_path) {
	if (fwrite(m, sizeof(struct modes_struct_tag), nmemb, file) != nmemb) {
		printf("[Cannot write to file %s]\n", file_path);
		exit(0);
	}
}

