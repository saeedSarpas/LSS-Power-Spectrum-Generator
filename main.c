#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>
#include <fftw3.h>
#include <stdbool.h>
#include <string.h>
#include "include/constants.h"
#include "include/global_functions.h"
#include "include/load_input.h"
#include "include/griding.h"
#include "include/power_spectrum.h"

int main(int argc, char *argv[]) {
	int counter, i, j, k, n;

	printf("Reading input file...");
	loadInputFromFile();
	printf("[done]\n");

	printf("Creating FFTW plan... ");
	double * grid_mass;
	grid_mass = calloc(pow(NUM_GRID_BLOCKS, 3), sizeof(double));
	fftw_complex * grid_fourier;
	grid_fourier = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NUM_FOURIER_GRID_BLOCKS);
	fftw_plan p;
	int rank[3] = {NUM_GRID_BLOCKS, NUM_GRID_BLOCKS, NUM_GRID_BLOCKS};
	p = fftw_plan_dft_r2c(3, rank, grid_mass, grid_fourier, FFTW_MEASURE);
	printf("[done]\n");

	printf("Choose griding algorithm, [1 for NGP, 2 for CIC, 3 for TSC]: ");
	char algorithm_name[10];
	int algorithm;
	scanf("%d", &algorithm);
	if (algorithm == 2) {
		printf("Griding using cloud in cell (CIC) algorithm... ");
		for (n = 0; n < NUM_OF_PART; n++) { CIC(P[n], grid_mass); }
		strcpy(algorithm_name, "-cic.dat");
		printf("[done]\n");
	} else if (algorithm == 3) {
		printf("Griding using triangular shaped cloud (TSC) algorithm... ");
		for (n = 0; n < NUM_OF_PART; n++) { TSC(P[n], grid_mass); }
		strcpy(algorithm_name, "-tsc.dat");
		printf("[done]\n");
	} else {
		printf("Griding using nearest grid points (NGP) algorithm... ");
		for (n = 0; n < NUM_OF_PART; n++) { NGP(P[n], grid_mass); }
		strcpy(algorithm_name, "-ngp.dat");
		printf("[done]\n");
	}

	printf("Dividing grid mass by the volume of the grid blocks... ");
	int total_num_grid_blocks = pow(NUM_GRID_BLOCKS, 3);
	double grid_block_volume = pow(GRID_SIZE, 3);
	for (n = 0; n < total_num_grid_blocks; n++) {
		grid_mass[n] /= grid_block_volume;
	}
	printf("[done]\n");

	int save_griding;
	printf("Do you want to save the griding output? [0 for no, 1 for yes] : ");
	scanf("%d", &save_griding);
	if (save_griding == 1) {
		FILE * griding;
		char griding_output[50] = "./output/raw_data/griding";
		strcat(griding_output, algorithm_name);
		if(!(griding = fopen(griding_output, "w"))) {
			printf("[Cannot open file `%s`]\n", griding_output);
			exit(0);
		}
		int index;
		double density_holder;
		for (i = 0; i < NUM_GRID_BLOCKS; i++){
			for (j = 0; j < NUM_GRID_BLOCKS; j++){
				for (k = 10; k < 11; k++){
					index = threeToOne(i,j,k);
					density_holder = grid_mass[index];
					fprintf(griding,"%d\t%d\t%f\n", i, j, density_holder);
				}
			}
		}
		fclose(griding);
	}

	printf("Fourier transform... ");
	fftw_execute(p);
	printf("[done]\n");
	fftw_destroy_plan(p);

	printf("Generating power spectrum... ");
	double mode_log;
	FILE * result_file;
	char power_spectrum[50] = "./output/raw_data/power-spectrum";
	strcat(power_spectrum, algorithm_name);
	result_file = fopen(power_spectrum, "wb");
	if(!(result_file = fopen(power_spectrum, "wb"))) {
		printf("[Cannot open file `%s`]\n", power_spectrum);
		exit(0);
	}
	int offset = 20;

	double mode_interval_log = log10(sqrt(3) * NUM_GRID_BLOCKS / 2) / NUM_OF_BINS;

	double * callback_results;
	callback_results = malloc(2 * sizeof(double));

	for(mode_log = mode_interval_log; mode_log < mode_interval_log * NUM_OF_BINS; mode_log += 2 * mode_interval_log){

		// callback results of:
		oneModePS(mode_log, mode_interval_log, grid_fourier, callback_results);
		// +--------------------------+
		// | 0: mode power | 1: error |
		// +--------------------------+

		fprintf(result_file, "%f\t%f\t%f\t%f\n", mode_log, mode_interval_log, callback_results[0], callback_results[1]);
	}
	fclose(result_file);
	printf("[done]\n");

	fftw_free(grid_fourier);
	free(grid_mass);
	return 0;
}
