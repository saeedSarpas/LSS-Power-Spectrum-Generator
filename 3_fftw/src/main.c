#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>
#include <string.h>
#include <time.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/particle_struct.h"
#include "./../../global_structs/info_strcut.h"

#include "./../../global_functions/config_file/load_config_from.h"
#include "./../../global_functions/info_file/get_info_from.h"
#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/memory/allocate.h"
#include "./../../global_functions/io/open_file.h"
#include "./../../global_functions/io/write_to.h"
#include "./../../global_functions/filenames/generate_filenames.h"
#include "./../../global_functions/strings/concat.h"

#include "./include/load_density_contrast_grid.h"
#include "./include/convert_real_delta_to_complex.h"
#include "./include/reordering_fourier_input.h"

int main() {

	config_struct conf = load_config_from("./../../configurations.cfg");
  filenames_struct filenames = generate_filenames(&conf);


	clock_t _c_a_c_f_f_ = start("Creating a c2c FFTW plan... ");

	size_t tot_num_of_grids = pow(conf.params.numOfAxisGrids, 3);

	fftw_complex *delta_complex;
	allocate((void **)&delta_complex, tot_num_of_grids, sizeof(fftw_complex));

	fftw_complex *delta_fourier;
	allocate((void **)&delta_fourier, tot_num_of_grids, sizeof(fftw_complex));


	int rank[3] = {
		conf.params.numOfAxisGrids,
		conf.params.numOfAxisGrids,
		conf.params.numOfAxisGrids
	};

	fftw_plan p;
	p = fftw_plan_dft(3, rank, delta_complex, delta_fourier, FFTW_FORWARD,
					  FFTW_MEASURE);

	done(_c_a_c_f_f_);


	clock_t _l_d_c_ = start("Loading density contrast... ");

	char *input_path = concat(2,
    "./../../2_griding/output/", filenames.densityContrast);

	double *delta_real;
	allocate((void **)&delta_real, tot_num_of_grids, sizeof(double));
	load_density_contrast_grid(input_path, delta_real, &conf);
	convert_real_delta_to_complex(delta_real, delta_complex, &conf);
	reordering_fourier_input(delta_complex, &conf);

	done(_l_d_c_);


	clock_t _f_t_ = start("Fourier transform... ");

	fftw_execute(p);
	fftw_destroy_plan(p);

	done(_f_t_);


	clock_t _s_d_ = start("Saving data... ");

	char *output_path = concat(2,
    "./../output/", filenames.fourierTransformed);

	FILE * out_file;
	open_file(&out_file, output_path, "wb");

	write_to(out_file, (void *)delta_fourier, tot_num_of_grids,
			 sizeof(fftw_complex));

	done(_s_d_);

	free(delta_real);
	fftw_free(delta_fourier);
	fftw_free(delta_complex);
	free(input_path);
	free(output_path);
	return 0;
}
