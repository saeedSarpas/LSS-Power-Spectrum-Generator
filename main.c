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
	double * gird_mass;
	gird_mass = calloc(pow(NUM_GRID_BLOCKS, 3), sizeof(double));
	fftw_complex * gird_fourier;
	gird_fourier = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NUM_FOURIER_GRID_BLOCKS);
	fftw_plan p;
	int rank[3] = {NUM_GRID_BLOCKS, NUM_GRID_BLOCKS, NUM_GRID_BLOCKS};
	p = fftw_plan_dft_r2c(3, rank, gird_mass, gird_fourier, FFTW_MEASURE);
	printf("[done]\n");

	printf("Choose griding algorithm, [1 for NGP, 2 for CIC, 3 for TSC]: ");
	char algorithm_name[10];
	int algorithm;
	scanf("%d", &algorithm);
	if (algorithm == 2) {
		printf("Griding using cloud in cell (CIC) algorithm... ");
		for (n = 0; n < NUM_OF_PART; n++) { CIC(P[n], gird_mass); }
		strcpy(algorithm_name, "-cic.dat");
		printf("[done]\n");
	} else if (algorithm == 3) {
		printf("Griding using triangular shaped cloud (TSC) algorithm... ");
		for (n = 0; n < NUM_OF_PART; n++) { TSC(P[n], gird_mass); }
		strcpy(algorithm_name, "-tsc.dat");
		printf("[done]\n");
	} else {
		printf("Griding using nearest grid points (NGP) algorithm... ");
		for (n = 0; n < NUM_OF_PART; n++) { NGP(P[n], gird_mass); }
		strcpy(algorithm_name, "-ngp.dat");
		printf("[done]\n");
	}

	printf("Dividing grid mass by the volume of the grid blocks... ");
	int total_num_grid_blocks = pow(NUM_GRID_BLOCKS, 3);
	double grid_block_volume = pow(GRID_SIZE, 3);
	for (n = 0; n < total_num_grid_blocks; n++) {
		gird_mass[n] /= grid_block_volume;
	}
	printf("[done]\n");

	int save_griding;
	printf("Do you want to save the griding output? [0 for no, 1 for yes] : ");
	scanf("%d", &save_griding);
	if (save_griding == 1) {
		FILE * griding;
		char griding_output[50] = "./output/raw_data/griding";
		strcat(griding_output, algorithm_name);
		griding = fopen(griding_output, "w");
		int index;
		double density_holder;
		for (i = 0; i < NUM_GRID_BLOCKS; i++){
			for (j = 0; j < NUM_GRID_BLOCKS; j++){
				for (k = 10; k < 11; k++){
					index = threeToOne(i,j,k);
					density_holder = gird_mass[index];
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
	double complex one_mode_ps;
	double one_mode_ps_real, one_mode_ps_imag, mode_log;
	double delta_k = 10 * GRID_SIZE, max_mode = (sqrt(3) * NUM_GRID_BLOCKS / 2);
	FILE * result_file;
	char power_spectrum[50] = "./output/raw_data/power-spectrum";
	strcat(power_spectrum, algorithm_name);
	result_file = fopen(power_spectrum, "wb");
	int offset = 20;

	double mode_interval_log = log10(sqrt(3) * NUM_GRID_BLOCKS / 2) / NUM_OF_BINS;

	for(mode_log = mode_interval_log; mode_log < mode_interval_log * NUM_OF_BINS; mode_log += 2 * mode_interval_log){
		one_mode_ps = oneModePS(mode_log, mode_interval_log, gird_fourier);
		fprintf(result_file, "%f\t%f\t%f\n", mode_log, mode_interval_log, pow(cabs(one_mode_ps), 2));
	}
	fclose(result_file);
	printf("[done]\n");

	fftw_free(gird_fourier);
	free(gird_mass);
	return 0;
}
