#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <fftw3.h>

void read_fftw_comlex_from(FILE *file, char *path, fftw_complex *f,
						   size_t size) {
	if (fread(f, sizeof(fftw_complex), size, file) != size) {
		printf("[Cannot read from file %s]\n", path);
		exit(0);
	}
}
