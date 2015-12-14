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

int main(int argc, char *argv[]) {

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

	double mode_log;

	char out_path[256] = "./outputs/";
	append_power_spectrum_filename(in_filename, alg_name, *C, out_path);

	FILE * out_file;
	open_file(&out_file, out_path, "wb");

	double mode_interval_log = log10(sqrt(3) * NUM_GRID_IN_EACH_AXIS / 2)
								/ (2 * NUM_OF_BINS);

	double * results;
	allocate_double_array(&results, 3);

	int tot = 0;
	for(mode_log = mode_interval_log; mode_log < mode_interval_log * 2 *
			NUM_OF_BINS; mode_log += 2 * mode_interval_log){

		// callback results of:
		one_mode_ps(mode_log, mode_interval_log, grid_fourier, results);
		// +--------------------------+-----------------------------+
		// | 0: mode power | 1: error | 2: number of found elements |
		// +--------------------------+-----------------------------+

		fprintf(out_file, "%f\t%f\t%f\t%f\t%d\n", mode_log, mode_interval_log,
				results[0], results[1], (int)results[2]);
		printf("%d\n", (int)results[2]);
		tot += (int)results[2];
	}
	printf("%d, %d\n", tot, (int)pow(NUM_GRID_IN_EACH_AXIS, 3));

	fclose(out_file);

	done(start_gen_ps);

	free(results);
	fftw_free(grid_fourier);
	free(C);
	return 0;
}
