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
#include "./../global_functions/grid.h"
#include "./../global_functions/memory_allocation.h"
#include "./../global_functions/file_handling.h"

#include "./include/load_fourier_transformed_data.h"
#include "./include/rho_tilda.h"
#include "./include/one_mode_ps.h"

int main() {

	char in_filename[256];
	choosing_input(in_filename);

	allocate_struct_config(&C);
	get_config(C, in_filename);

	char alg_name[256];
	choosing_algorithm(alg_name);

	char load_input_msg[256] = "Load Fourier transformed data... ";
	clock_t start_load_input = start(load_input_msg);

	size_t grid_fourier_size = pow(NUM_GRID_IN_EACH_AXIS, 2) *
		((NUM_GRID_IN_EACH_AXIS / 2) + 1);

	fftw_complex * grid_fourier;
	grid_fourier = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *
											   grid_fourier_size);

	char input_file[256] = "";
	append_fourier_transformed_filename(in_filename, alg_name, *C, input_file);
	load_fourier_transformed_data(input_file, grid_fourier);

	done(start_load_input);

	char gen_ps_msg[256] = "Generating power spectrum... ";
	clock_t start_gen_ps = start(gen_ps_msg);

	double log_of_the_mode;

	char out_path[256] = "./outputs/";
	append_power_spectrum_filename(in_filename, alg_name, *C, out_path);

	FILE * out_file;
	open_file(&out_file, out_path, "wb");

	double * results;
	allocate_double_array(&results, 3);

	double log_of_largest_mode = log10(sqrt(3) * NUM_GRID_IN_EACH_AXIS / 2);

	fprintf(out_file, "Mode     \tLeft err \tRight err\tPower   \tPower err\tN\n");

	double log_of_half_k_bins_width = LOG_OF_K_BINS_WIDTH / 2;
	for(log_of_the_mode = log_of_half_k_bins_width;
		log_of_the_mode < log_of_largest_mode;
		log_of_the_mode += LOG_OF_K_BINS_WIDTH){

		// callback results of:
		one_mode_ps(log_of_the_mode, log_of_half_k_bins_width, grid_fourier,
					results);
		// +--------------------------+-----------------------------+
		// | 0: mode power | 1: error | 2: number of found elements |
		// +--------------------------+-----------------------------+

		double k = pow(10, log_of_the_mode) * 2 * PI / C->BoxLength;
		double le = pow(10, log_of_the_mode - log_of_half_k_bins_width) * 2 * PI / C->BoxLength;
		double re = pow(10, log_of_the_mode + log_of_half_k_bins_width) * 2 * PI / C->BoxLength;
		double p = results[0] / pow(NUM_GRID_IN_EACH_AXIS, 2);
		double pe = results[1] / pow(NUM_GRID_IN_EACH_AXIS, 2);

		fprintf(out_file, "%f\t%f\t%f\t%f\t%f\t%d\n", k, le, re, p, pe,
				(int)results[2]);
	}

	fclose(out_file);

	done(start_gen_ps);

	free(results);
	fftw_free(grid_fourier);
	free(C);
	return 0;
}
