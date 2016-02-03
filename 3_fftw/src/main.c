#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>
#include <string.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/particle_data_struct.h"
#include "./../../global_structs/input_file_info.h"

#include "./../../global_functions/config_file/get_config.h"
#include "./../../global_functions/io/get_algorithm_alias.h"
#include "./../../global_functions/io/get_input_filename_alias.h"
#include "./../../global_functions/filenames/append_input_info_name.h"
#include "./../../global_functions/info_file/read_input_file_info.h"
#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/memory/allocate_fftw_complex.h"
#include "./../../global_functions/memory/allocate_double_array.h"
#include "./../../global_functions/filenames/append_density_contrast_filename.h"
#include "./../../global_functions/filenames/append_fourier_transformed_filename.h"
#include "./../../global_functions/open_file.h"
#include "./../../global_functions/io/write_fftw_complex_to.h"

#include "./include/load_density_contrast_grid.h"
#include "./include/convert_real_delta_to_complex.h"
#include "./include/reordering_fourier_input.h"

int main() {

	config_struct conf;
	get_config(&conf);

	char *input_filename_alias;
	input_filename_alias = get_input_filename_alias(&conf);

	char *algorithm_alias;
	algorithm_alias = get_algorithm_alias(&conf);

	input_info_struct info;
	char *input_info_path = strdup("./../../0_structured_input/");
	append_input_info_name(input_filename_alias, &input_info_path);
	read_input_file_info(&info, input_info_path);

	clock_t _c_a_c_f_f_ = start("Creating a c2c FFTW plan... ");

	size_t tot_num_of_grids = pow(conf.num_of_grids_in_each_axis, 3);

	fftw_complex *delta_complex;
	allocate_fftw_complex(&delta_complex, tot_num_of_grids);

	fftw_complex *delta_fourier;
	allocate_fftw_complex(&delta_fourier, tot_num_of_grids);

	int rank[3] = {
		conf.num_of_grids_in_each_axis,
		conf.num_of_grids_in_each_axis,
		conf.num_of_grids_in_each_axis
	};

	fftw_plan p;
	p = fftw_plan_dft(3, rank, delta_complex, delta_fourier, FFTW_FORWARD,
					  FFTW_MEASURE);

	done(_c_a_c_f_f_);


	clock_t _l_d_c_ = start("Loading density contrast... ");

	char *input_path = strdup("./../../2_griding/output/");
	append_density_contrast_filename(input_filename_alias, algorithm_alias,
									 &info, &conf, &input_path);

	double *delta_real;
	allocate_double_array(&delta_real, tot_num_of_grids);
	load_density_contrast_grid(input_path, delta_real, &conf);

	convert_real_delta_to_complex(delta_real, delta_complex, &conf);

	reordering_fourier_input(delta_complex, &conf);

	done(_l_d_c_);


	clock_t _f_t_ = start("Fourier transform... ");

	fftw_execute(p);
	fftw_destroy_plan(p);

	done(_f_t_);


	clock_t _n_ = start("Normalizing... ");

	unsigned int i;
	double sqrt_tot_num_of_grids = sqrt(tot_num_of_grids);
	for (i = 0; i < tot_num_of_grids; i++)
		delta_fourier[i] /=  sqrt_tot_num_of_grids;

	done(_n_);


	clock_t _s_d_ = start("Saving data... ");

	char *output_path = strdup("./../output/");
	append_fourier_transformed_filename(input_filename_alias, algorithm_alias,
										&info, &conf, &output_path);

	FILE * out_file;
	open_file(&out_file, output_path, "wb");

	write_fftw_complex_to(out_file, output_path, delta_fourier,
						  tot_num_of_grids);

	done(_s_d_);

	fftw_free(delta_fourier);
	free(delta_complex);
	free(input_info_path);
	free(input_path);
	free(output_path);

	return 0;
}
