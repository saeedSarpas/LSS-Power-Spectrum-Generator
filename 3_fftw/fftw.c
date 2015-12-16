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
#include "./../global_functions/grid.h"

#include "./include/load_density_contrast_grid.h"
#include "./include/fill_fftw_complex_grid_delta.h"
#include "./include/reordering_fourier_input.h"

int main() {

	char input_mode[256];
	choosing_input(input_mode);

	char alg_name[256];
	choosing_algorithm(alg_name);

	allocate_struct_config(&C);
	get_config(C, input_mode);

	clock_t _c_a_c_f_f_ = start("Creating a c2c FFTW plan... ");

	fftw_complex * grid_delta;
	size_t tot_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);
	allocate_fftw_complex_array(&grid_delta, tot_num_grid);

	fftw_complex * grid_fourier;
	allocate_fftw_complex_array(&grid_fourier, tot_num_grid);

	int rank[3] = {NUM_GRID_IN_EACH_AXIS, NUM_GRID_IN_EACH_AXIS,
				   NUM_GRID_IN_EACH_AXIS};

	fftw_plan p;
	p = fftw_plan_dft(3, rank, grid_delta, grid_fourier, FFTW_FORWARD, FFTW_MEASURE);

	done(_c_a_c_f_f_);

	clock_t _l_d_c_ = start("Loading density contrast... ");

	char input_path[256] = "./../2_griding/outputs/";
	append_density_contrast_filename(input_mode, alg_name, *C, input_path);

	double * temp;
	allocate_double_array(&temp, tot_num_grid);
	load_density_contrast_grid(input_path, temp);

	fill_fftw_complex_grid_delta(temp, grid_delta);

	reordering_fourier_input(grid_delta);

	done(_l_d_c_);

	clock_t _f_t_ = start("Fourier transform... ");

	fftw_execute(p);
	fftw_destroy_plan(p);

	done(_f_t_);

	clock_t _s_d_ = start("Saving data... ");

	char output_path[256] = "./outputs/";
	append_fourier_transformed_filename(input_mode, alg_name, *C, output_path);

	FILE * out_file;

	open_file(&out_file, output_path, "wb");

	write_fftw_complex_to_file(out_file, output_path, grid_fourier,
							   tot_num_grid);

	done(_s_d_);

	fftw_free(grid_fourier);
	free(grid_delta); free(C);

	return 0;
}
