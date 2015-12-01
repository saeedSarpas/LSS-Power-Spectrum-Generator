#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>
#include <string.h>
#include <time.h>

#include "./../configurations.h"
#include "./../global_functions/clock.h"
#include "./../global_functions/choosing.h"
#include "./../global_functions/config_file.h"
#include "./../global_functions/filenames.h"
#include "./includes/load_density_contrast_grid.h"

int main(int argc, char *argv[]) {

	char in_filename[256];
	choosing_input(in_filename);

	char alg_name[256];
	choosing_algorithm(alg_name);

	if( !(C = malloc(sizeof(struct config))) ) {
		printf("[Failed to allocate memory.]\n");
		exit(0);
	}
	get_config(C, in_filename);

	char fftw_plan_msg[256] = "Creating FFTW plan... ";
	clock_t begin = start(fftw_plan_msg);

	double * grid_delta;
	grid_delta = calloc(pow(NUM_GRID_IN_EACH_AXIS, 3), sizeof(double));

	size_t grid_fourier_size = pow(NUM_GRID_IN_EACH_AXIS, 2) *
		((NUM_GRID_IN_EACH_AXIS / 2) + 1);

	fftw_complex * grid_fourier;
	grid_fourier = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *
			grid_fourier_size);

	int rank[3] = {NUM_GRID_IN_EACH_AXIS, NUM_GRID_IN_EACH_AXIS,
		NUM_GRID_IN_EACH_AXIS};

	fftw_plan p;
	p = fftw_plan_dft_r2c(3, rank, grid_delta, grid_fourier, FFTW_MEASURE);

	done(begin);

	char load_input_msg[256] = "Loading density contrast... ";
	begin = start(load_input_msg);

	char input_file[256] = "";
	append_density_contrast_filename(in_filename, alg_name, *C, input_file);

	load_density_contrast_grid(input_file, grid_delta);

	done(begin);

	char fourier_trans_msg[256] = "Fourier transform... ";
	begin = start(fourier_trans_msg);

	fftw_execute(p);
	fftw_destroy_plan(p);

	done(begin);

	char save_out[256] = "Saving data... ";
	begin = start(save_out);

	char output_path[256] = "./outputs/";
	append_fourier_transformed_filename(in_filename, alg_name, *C, output_path);

	FILE * out_file;

	if(!(out_file = fopen(output_path, "wb"))) {
		printf("[Cannot open file %s]\n", output_path);
		exit(0);
	}

	if(fwrite(grid_fourier, sizeof(fftw_complex), grid_fourier_size,
				out_file) != grid_fourier_size) {
		printf("[Cannot write on file %s]", output_path);
		exit(0);
	}

	done(begin);

	fftw_free(grid_fourier); free(grid_delta); free(C);
	return 0;
}
