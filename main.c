#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>
#include <fftw3.h>
#include "include/constants.h"
#include "include/global_functions.h"
#include "include/load_input.h"
#include "include/griding.h"

int main(int argc, char *argv[]) {

	fprintf(stdout, "Reading input file...");
	loadInputFromFile();
	fprintf(stdout, "[done]\n");

	double * grid_mass_ptr;
	grid_mass_ptr = calloc(pow(gridLength, 3), sizeof(double));

	char algorithm;
	fprintf(stdout, "Choose griding algorithm, [n for NGP (defualt), c for CIC, t for TSC]: ");
	fscanf(stdin, "%c", &algorithm);

	int n;
	if (algorithm == 'c') {
		fprintf(stdout, "Griding using cloud in cell (CIC) algorithm... ");
		for (n = 0; n < numPart; n++) {CIC(P[n], grid_mass_ptr); }
		fprintf(stdout, "[done]\n");
	} else if (algorithm == 't') {
		fprintf(stdout, "Griding using triangular shaped cloud (TSC) algorithm... ");
		for (n = 0; n < numPart; n++) { TSC(P[n], grid_mass_ptr); }
		fprintf(stdout, "[done]\n");
	} else {
		fprintf(stdout, "Griding using nearest grid points (NGP) algorithm... ");
		for (n = 0; n < numPart; n++) { NGP(P[n], grid_mass_ptr); }
		fprintf(stdout, "[done]\n");
	}

	int numGridBlocks = pow(gridLength, 3);
	double gridBlockVolume = pow(gridSize, 3);
	fprintf(stdout, "Dividing grid mass by the volume of grid blocks... ");
	for (n = 0; n < numGridBlocks; n++) {
		grid_mass_ptr[n] /= gridBlockVolume;
	}
	fprintf(stdout, "[done]\n");

	fftw_complex * grid_fourier_ptr;
	fftw_plan p;
	grid_fourier_ptr = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * gridLength * gridLength * (gridLength /2 + 1));
	int rank[3] = {gridLength, gridLength, gridLength};

	fprintf(stdout, "Starting Fourier transform... ");
	p = fftw_plan_dft_r2c(3, rank, grid_mass_ptr, grid_fourier_ptr, FFTW_MEASURE);
	fftw_execute(p);
	fprintf(stdout, "[done]\n");

	fftw_destroy_plan(p);

	fftw_free(grid_fourier_ptr);
	free(grid_mass_ptr);
	return 0;
}
