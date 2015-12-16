#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <complex.h>
#include <fftw.h>

#include "./../configurations.h"
#include "./../global_functions/choosing.h"
#include "./../global_functions/clock.h"
#include "./../global_functions/config_file.h"
#include "./../global_functions/grid.h"
#include "./../global_functions/filenames.h"
#include "./../global_functions/memory_allocation.h"
#include "./../global_functions/file_handling.h"

#include "./include/load_structured_input.h"
#include "./include/ngp.h"
#include "./include/cic.h"
#include "./include/tsc.h"
#include "./include/density_contrast.h"

int main() {
	char input_fn[256];
	choosing_input(input_fn);

	char alg_name[256];
	choosing_algorithm(alg_name);

	allocate_struct_config(&C);
	get_config(C, input_fn);

	clock_t _r_g_i_ = start("Reading griding input... ");

	allocate_struct_particle_data_array(&P, C->NumPart);

	char input_path[256] = "./../1_load_input_file/outputs/";
	append_input_filename(input_fn, input_path);

	load_sturctured_input(P, input_path, *C);

	done(_r_g_i_);

	double * grid_mass;
	size_t tot_num_of_grids = pow(NUM_GRID_IN_EACH_AXIS, 3);
	allocate_double_array(&grid_mass, tot_num_of_grids);

	if (strcmp(alg_name, CIC_POSTFIX) == 0) {
		char alg[256] = "Griding using cloud in cell (CIC) algorithm... ";
		clock_t begin = start(alg);
		cic(P, grid_mass, C);
		done(begin);
	} else if (strcmp(alg_name, TSC_POSTFIX) == 0) {
		char alg[256] = "Griding using triangular shaped cloud (TSC) algorithm... ";
		clock_t begin = start(alg);
		tsc(P, grid_mass, C);
		done(begin);
	} else if (strcmp(alg_name, NGP_POSTFIX) == 0) {
		char alg[256] = "Griding using nearest grid points (NGP) algorithm... ";
		clock_t begin = start(alg);
		ngp(P, grid_mass, C);
		done(begin);
	} else {
		printf("[Wrong algorithm]\n");
		exit(0);
	}

	clock_t _c_d_c_ = start("Calculating density contrast... ");

	double * grid_delta;
	allocate_double_array(&grid_delta, tot_num_of_grids);

	density_contrast(grid_mass, *C, grid_delta);

	done(_c_d_c_);

	clock_t _s_g_b_ = start("Saving griding (binary)... ");

	FILE * out_file;
	char output_path[256] = "./outputs/";
	append_density_contrast_filename(input_fn, alg_name, *C, output_path);
	open_file(&out_file, output_path, "w");

	write_double_to_file(out_file, grid_delta, tot_num_of_grids, output_path);

	fclose(out_file);

	done(_s_g_b_);

	clock_t _s_g_a_ = start("Saving griding (ascii)... ");

	FILE * ascii_out_file;
	char ascii_output_path[256] = "./outputs/ascii-";
	append_density_contrast_filename(input_fn, alg_name, *C,
			ascii_output_path);
	open_file(&ascii_out_file, ascii_output_path, "w");

	int i, j, k, index;
	for (i = 0; i < NUM_GRID_IN_EACH_AXIS; i++) {
		for (j = 0; j < NUM_GRID_IN_EACH_AXIS; j++) {
			for (k = (NUM_GRID_IN_EACH_AXIS / 2);
					k < (NUM_GRID_IN_EACH_AXIS / 2) + 1; k++) {

				index = three_to_one(i, j, k);
				fprintf(ascii_out_file, "%d\t%d\t%f\n", i, j, grid_delta[index]);
			}
		}
	}

	fclose(ascii_out_file);

	done(_s_g_a_);

	free(P); free(C);
	free(grid_mass);
	free(grid_delta);

	return 0;
}
