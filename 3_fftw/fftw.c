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
#include "./../global_functions/memory_allocation.h"
#include "./../global_functions/file_handling.h"

#include "./include/load_density_contrast_grid.h"

int main(int argc, char *argv[]) {
	int i;

	char in_filename[256];
	choosing_input(in_filename);

	char alg_name[256];
	choosing_algorithm(alg_name);

	allocate_struct_config(&C);
	get_config(C, in_filename);

	char fftw_plan_msg[256] = "Creating FFTW plan... ";
	clock_t start_fftw_plan = start(fftw_plan_msg);

	double * grid_delta;
	size_t tot_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);
	allocate_double_array(&grid_delta, tot_num_grid);

	size_t grid_fourier_size = pow(NUM_GRID_IN_EACH_AXIS, 2) *
		((NUM_GRID_IN_EACH_AXIS / 2) + 1);

	fftw_complex * grid_fourier;
	allocate_fftw_complex_array(&grid_fourier, grid_fourier_size);
	grid_fourier = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *
											   grid_fourier_size);

	int rank[3] = {NUM_GRID_IN_EACH_AXIS, NUM_GRID_IN_EACH_AXIS,
				   NUM_GRID_IN_EACH_AXIS};

	fftw_plan p;
	p = fftw_plan_dft_r2c(3, rank, grid_delta, grid_fourier, FFTW_MEASURE);

	done(start_fftw_plan);

	char load_input_msg[256] = "Loading density contrast... ";
	clock_t start_load_input = start(load_input_msg);

	char input_path[256] = "./../2_griding/outputs/";
	append_density_contrast_filename(in_filename, alg_name, *C, input_path);

	load_density_contrast_grid(input_path, grid_delta);

	done(start_load_input);

	char fourier_trans_msg[256] = "Fourier transform... ";
	clock_t start_fourier_trans = start(fourier_trans_msg);

	fftw_execute(p);
	fftw_destroy_plan(p);

	done(start_fourier_trans);

	char save_out[256] = "Saving data... ";
	clock_t start_saving = start(save_out);

	char output_path[256] = "./outputs/";
	append_fourier_transformed_filename(in_filename, alg_name, *C, output_path);

	FILE * out_file;

	open_file(&out_file, output_path, "wb");

	write_fftw_complex_to_file(out_file, output_path, grid_fourier,
							   grid_fourier_size);

	done(start_saving);

	fftw_free(grid_fourier);
	free(grid_delta); free(C);

	return 0;
}
