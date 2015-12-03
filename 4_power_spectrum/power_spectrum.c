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

#include "./includes/load_input.h"
#include "./includes/power_spectrum.h"

int main(int argc, char *argv[]) {

	char in_filename[256];
	choosing_input(in_filename);

	char alg_name[256];
	choosing_algorithm(alg_name);

	if (!(C = malloc(sizeof(struct config))) ) {
		printf("[Failed to allocate memory.]\n");
		exit(0);
	}
	get_config(C, in_filename);

	char load_input_msg[256] = "Load Fourier transformed data... ";
	clock_t begin = start(load_input_msg);

	size_t grid_fourier_size = pow(NUM_GRID_IN_EACH_AXIS, 2) *
		((NUM_GRID_IN_EACH_AXIS / 2) + 1);

	fftw_complex * grid_fourier;
	grid_fourier = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) *
			grid_fourier_size);

	char input_file[256] = "";
	append_fourier_transformed_filename(in_filename, alg_name, *C, input_file);
	load_input(input_file, grid_fourier);

	done(begin);

	char gen_ps_msg[256] = "Generating power spectrum... ";
	begin = start(gen_ps_msg);

	double mode_log;

	char out_path[256] = "./outputs/";
	append_power_spectrum_filename(in_filename, alg_name, *C, out_path);

	FILE * out_file;
	if(!(out_file = fopen(out_path, "wb"))) {
		printf("[Cannot open file `%s`]\n", out_path);
		exit(0);
	}

	double mode_interval_log = log10(sqrt(3) * NUM_GRID_IN_EACH_AXIS / 2)
								/ (2 * NUM_OF_BINS);

	double * results;
	results = malloc(2 * sizeof(double));

	for(mode_log = mode_interval_log; mode_log < mode_interval_log * 2 *
			NUM_OF_BINS; mode_log += 2 * mode_interval_log){

		/*// callback results of:*/
		one_mode_ps(mode_log, mode_interval_log, grid_fourier, results);
		/*// +--------------------------+*/
		/*// | 0: mode power | 1: error |*/
		/*// +--------------------------+*/

		fprintf(out_file, "%f\t%f\t%f\t%f\n", mode_log, mode_interval_log,
				results[0], results[1]);
	}

	fclose(out_file);

	done(begin);

	free(results);
	fftw_free(grid_fourier);
	free(C);
	return 0;
}
