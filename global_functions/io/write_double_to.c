#include <stdio.h>
#include <stdlib.h>

void write_double_to(FILE *file, double *d, size_t nmemb, char *file_path) {
	if (fwrite(d, sizeof(double), nmemb, file) != nmemb) {
		printf("[Cannot write to file %s]\n", file_path);
		exit(0);
	}
}
