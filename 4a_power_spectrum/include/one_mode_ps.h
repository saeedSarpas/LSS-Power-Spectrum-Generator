void variance(double * power_array, int length, double * callback_results) {

	// callback results:
	// +-----------------------------+
	// | 0: mode power | 1: variance |
	// +-----------------------------+

	int i;

	callback_results[0] = 0.0f;

	for (i = 1; i < length; i++) {
		callback_results[0] += power_array[i];
	}

	callback_results[0] /= length;

	callback_results[1] = 0.0f;

	for (i = 0; i < length; i++) {
		callback_results[1] += pow((power_array[i] - callback_results[0]), 2);
	}
}

void one_mode_ps (double mode_log, double mode_interval_log,
		fftw_complex * gird_fourier, double * callback_results) {

	// callback results:
	// +--------------------------+
	// | 0: mode power | 1: error |
	// +--------------------------+

	int i, j, k, length = 0;
	double rho, d_log, *power_array;
	power_array = calloc(pow(NUM_GRID_IN_EACH_AXIS , 3), sizeof(double));

	// Following we iterate through all negative and positive Fourier mode and
	// it is the job of rho_tilda function to return the right element of
	// the output of r2c FFTW transform

	int mid_grid = NUM_GRID_IN_EACH_AXIS / 2;
	for (i = - mid_grid; i < mid_grid; i++){
		for (j = - mid_grid; j < mid_grid; j++){
			for (k = - mid_grid; k < mid_grid; k++){
				d_log = log10(sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2)));

				double min = mode_log - mode_interval_log;
				double max = mode_log + mode_interval_log;

				if (d_log >= min && d_log < max) {
					rho = rho_tilda(i, j, k, gird_fourier);
					power_array[length] += pow(creal(rho), 2) + pow(cimag(rho), 2);
					length++;
				}
			}
		}
	}

	if (length != 0) {
		double sigma_squared;
		variance(power_array, length, callback_results);
		callback_results[1] = sqrt(callback_results[1]) / length;
	} else {
		printf("\nFind no point in this shell, log10(mode)= %f and log10(mode_interval)= %f\n", mode_log, mode_interval_log);
		exit(0);
	}
}
