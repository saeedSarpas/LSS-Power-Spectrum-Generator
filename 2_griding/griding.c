#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "./../configurations.h"
#include "./../global_functions/choosing.h"
#include "./../global_functions/clock.h"
#include "./../global_functions/config_file.h"
#include "./../global_functions/grid.h"
#include "./../global_functions/filenames.h"
#include "./includes/load_input.h"
#include "./includes/griding.h"
#include "./includes/density_contrast.h"

int main() {
	char in_filename[256];
	choosing_input(in_filename);

	char alg_name[256];
	choosing_algorithm(alg_name);

	if (!(C = malloc(sizeof(struct config))) ) {
		printf("[Failed to allocate memory.]\n");
		exit(0);
	}

	get_config(C, in_filename);

	char load_msg[256] = "Reading griding input... ";
	clock_t begin = start(load_msg);

	if (!(P = malloc(C->NumPart * sizeof(struct particle_data))) ) {
		printf("[Failed to allocate memory.]\n");
		exit(0);
	}

	load_input(P, in_filename, *C);

	done(begin);

	double * grid_mass;
	if (!(grid_mass = calloc(pow(NUM_GRID_IN_EACH_AXIS, 3), sizeof(double)))) {
		printf("[Failed to allocate memory.]");
	}

	if (alg_name == CIC_POSTFIX) {
		char alg[256] = "Griding using cloud in cell (CIC) algorithm... ";
		clock_t begin = start(alg);
		int n;
		for (n = 0; n < C->NumPart; n++) { cic(P[n], grid_mass, *C); }
		done(begin);
	} else if (alg_name == TSC_POSTFIX) {
		char alg[256] = "Griding using triangular shaped cloud (TSC) algorithm... ";
		clock_t begin = start(alg);
		int n;
		for (n = 0; n < C->NumPart; n++) { tsc(P[n], grid_mass, *C); }
		done(begin);
	} else {
		char alg[256] = "Griding using nearest grid points (NGP) algorithm... ";
		clock_t begin = start(alg);
		int n;
		for (n = 0; n < C->NumPart; n++) { ngp(P[n], grid_mass, *C); }
		done(begin);
	}

	char calc_dens_msg[256] = "Calculating density contrast... ";
	begin = start(calc_dens_msg);

	double * grid_delta;
	if (!(grid_delta = calloc(pow(NUM_GRID_IN_EACH_AXIS, 3), sizeof(double)))) {
		printf("[Failed to allocate memory.]");
	};

	density_contrast(grid_mass, *C, grid_delta);

	done(begin);

	char save_output_msg[256] = "Saving griding (binary)... ";
	begin = start(save_output_msg);

	char output_path[256] = "./outputs/";
	append_density_contrast_filename(in_filename, alg_name, *C, output_path);

	FILE * out_file;

	if (!(out_file = fopen(output_path, "w"))) {
		printf("[Cannot open file %s]\n", output_path);
		exit(0);
	}

	int total_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);
	if (fwrite(grid_delta, sizeof(double), total_num_grid, out_file) !=
			total_num_grid) {
		printf("[Cannot write on stream %s]", output_path);
		exit(0);
	}
	fclose(out_file);

	done(begin);

	char save_output_ascii_msg[256] = "Saving griding (ascii)... ";
	begin = start(save_output_ascii_msg);

	char ascii_output_path[256] = "./outputs/ascii-";
	append_density_contrast_filename(in_filename, alg_name, *C,
			ascii_output_path);

	FILE * ascii_out_file;

	if (!(ascii_out_file = fopen(ascii_output_path, "w"))) {
		printf("[Cannot open file %s]\n", ascii_output_path);
		exit(0);
	}

	int i, j, k, index;
	for (i = 0; i < NUM_GRID_IN_EACH_AXIS; i++) {
		for (j = 0; j < NUM_GRID_IN_EACH_AXIS; j++) {
			for (k = (NUM_GRID_IN_EACH_AXIS / 2);
					k < (NUM_GRID_IN_EACH_AXIS / 2) + 1; k++) {

				index = threeToOne(i, j, k);
				fprintf(ascii_out_file, "%d\t%d\t%f\n", i, j, grid_delta[index]);
			}
		}
	}
	fclose(ascii_out_file);

	done(begin);

	free(P); free(C);
	free(grid_mass);
	free(grid_delta);
}
