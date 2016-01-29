#include <complex.h>
#include <fftw3.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"

#include "./../../../global_functions/open_file.h"
#include "./../../../global_functions/io/read_fftw_complex_from.h"

void load_fourier_transformed_data(char *path, fftw_complex *grid_fourier,
		config *conf) {

	FILE *file;
	open_file(&file, path, "rb");

	size_t tot_num_of_grids = pow(conf->num_of_grids_in_each_axis, 3);

	read_fftw_comlex_from(file, path, grid_fourier, tot_num_of_grids);

	fclose(file);
}
