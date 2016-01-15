#include <stdio.h>
#include <stdlib.h>

void read_double_from(FILE *file, char *file_path, double *d, size_t size) {
	if (fread(d, sizeof(double), size, file) != size) {
		printf("[Cannot read from file %s]", file_path);
		exit(0);
	}
}
