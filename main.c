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
#include "include/power_spectrum.h"

int main(int argc, char *argv[]) {
	int counter, i, j, k;

	fprintf(stdout, "Reading input file...");
	loadInputFromFile();
	fprintf(stdout, "[done]\n");

	char algorithm;
	fprintf(stdout, "Choose griding algorithm, [n for NGP (defualt), c for CIC, t for TSC]: ");
	fscanf(stdin, "%c", &algorithm);

	fprintf(stdout, "Creating FFTW plan... ");
	double * grid_mass_ptr;
	grid_mass_ptr = calloc(pow(gridLength, 3), sizeof(double));
	fftw_complex * grid_fourier_ptr;
	grid_fourier_ptr = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * fourierGridLength);
	fftw_plan p;
	int rank[3] = {gridLength, gridLength, gridLength};
	p = fftw_plan_dft_r2c(3, rank, grid_mass_ptr, grid_fourier_ptr, FFTW_MEASURE);
	fprintf(stdout, "[done]\n");

	int n;
	if (algorithm == 'c') {
		fprintf(stdout, "Griding using cloud in cell (CIC) algorithm... ");
		for (n = 0; n < numPart; n++) { CIC(P[n], grid_mass_ptr); }
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
	fprintf(stdout, "Dividing grid mass by the volume of the grid blocks... ");
	for (n = 0; n < numGridBlocks; n++) {
		grid_mass_ptr[n] /= gridBlockVolume;
	}
	fprintf(stdout, "[done]\n");

	fprintf(stdout, "Fourier transform... ");
	fftw_execute(p);
	fprintf(stdout, "[done]\n");
	fftw_destroy_plan(p);

	double mode_k, one_mode_ps;
	FILE *output_file_ptr;
	output_file_ptr = fopen("./output.dat", "wb");
	fprintf(stdout, "Calculating power spectrum... ");
	for(mode_k = 1.0; mode_k < gridLength/2; mode_k += 1.0){
		one_mode_ps = oneModePS(mode_k, deltaK, grid_fourier_ptr);
		fwrite(&mode_k, 1, sizeof(double), output_file_ptr);
		fwrite(&one_mode_ps, 1, sizeof(double), output_file_ptr);
	}
	fclose(output_file_ptr);
	fprintf(stdout, "[done]\n");

	/*for (counter = 0; counter < gridLength * gridLength * (gridLength / 2 + 1); counter++) {*/
		/*printf("%f + i%f\n", creal(grid_fourier_ptr[counter]), cimag(grid_fourier_ptr[counter]));*/
	/*}*/

	fftw_free(grid_fourier_ptr);
	free(grid_mass_ptr);
	return 0;
}
