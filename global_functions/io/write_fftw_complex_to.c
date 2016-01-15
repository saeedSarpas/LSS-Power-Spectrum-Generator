#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <fftw3.h>

void write_fftw_complex_to(FILE *file, char *path, fftw_complex *f,
		size_t size) {
	if (fwrite(f, sizeof(fftw_complex), size, file) != size) {
		printf("[Cannot write to file %s]", path);
		exit(0);
	}
}
