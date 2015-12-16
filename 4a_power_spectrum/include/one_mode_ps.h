void variance(double * power_array, int length, double * callback_results) {

	// callback results:
	// +-----------------------------+
	// | 0: mode power | 1: variance |
	// +-----------------------------+

	int i;

	callback_results[0] = 0.0f;

	for (i = 1; i <= length; i++) {
		callback_results[0] += power_array[i];
	}

	callback_results[0] /= length;

	callback_results[1] = 0.0;

	for (i = 0; i < length; i++) {
		callback_results[1] += pow((power_array[i] - callback_results[0]), 2);
	}
}

void one_mode_ps (double log_of_the_mode, double log_of_bins_half_width,
				  fftw_complex * gird_fourier, double * callback_results) {

	// callback results:
	// +--------------------------+-----------------------------+
	// | 0: mode power | 1: error | 2: number of found elements |
	// +--------------------------+-----------------------------+

	int i, j, k, length = 0;
	size_t tot_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);

	double log_of_k_modulus, *power_array;
	allocate_double_array(&power_array, tot_num_grid);

	fftw_complex *rho;
	allocate_fftw_complex_array(&rho, 1);

	// Following we iterate through all negative and positive Fourier mode and
	// it is the job of rho_tilda function to return the right element of
	// the output of r2c FFTW transform

	int cntr = 0, mid_grid = NUM_GRID_IN_EACH_AXIS / 2;

	for (i = - mid_grid; i < mid_grid; i++){
		for (j = - mid_grid; j < mid_grid; j++){
			for (k = - mid_grid; k < mid_grid; k++){
				log_of_k_modulus = log10(sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2)));

				double min = log_of_the_mode - log_of_bins_half_width;
				double max = log_of_the_mode + log_of_bins_half_width;

				if (log_of_k_modulus >= min && log_of_k_modulus < max) {
					rho_tilda(i, j, k, gird_fourier, rho);
					power_array[length] = pow(creal(*rho), 2)
						+ pow(cimag(*rho), 2);
					length++;
					cntr++;
				}
			}
		}
	}

	callback_results[2] = (float)cntr;

	if (length != 0) {
		double sigma_squared;
		variance(power_array, length, callback_results);
		callback_results[1] = sqrt(callback_results[1]) / length;
	} else {
		printf("\n[Find no point in this shell, mode= %f and mode_interval = %f]\n", pow(10, log_of_the_mode), pow(10, log_of_bins_half_width));
		exit(0);
	}
}
