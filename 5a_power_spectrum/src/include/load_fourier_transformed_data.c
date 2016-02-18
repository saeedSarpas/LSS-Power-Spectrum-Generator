#include <complex.h>
#include <fftw3.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/io/open_file.h"
#include "./../../../global_functions/io/read_from.h"

void load_fourier_transformed_data(char *path, fftw_complex *grid_fourier,
		config_struct *conf) {

	FILE *file;
	open_file(&file, path, "rb");

	size_t tot_num_of_grids = pow(conf->run_params.num_of_axis_grids, 3);

	read_from(file, tot_num_of_grids, sizeof(fftw_complex),
			  (void *)grid_fourier);

	fclose(file);
}
