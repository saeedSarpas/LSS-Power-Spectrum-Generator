double complex rho_tilda(int i, int j, int k, fftw_complex * grid_fourier) {

	// Change the order of modes by considering the location of DC mode on the
	// r2c FFTW output array

	if (i < 0) { i = NUM_GRID_IN_EACH_AXIS  - abs(i); }
	if (j < 0) { j = NUM_GRID_IN_EACH_AXIS  - abs(j); }
	if (k < 0) { k = NUM_GRID_IN_EACH_AXIS  - abs(k); }

	// Following is the output of a two-dimensional r2c FFTW transform of a 8
	// elements real array:
	//
	//     +-----------------------------------------------------------+
	//     |  0,0 |  0,1 |  0,2 |  0,3 |  0,-4 |  0,-3 |  0,-2 |  0,-1 |
	//     +-----------------------------------------------------------+
	//     |  1,0 |  1,1 |  1,2 |  1,3 |  1,-4 |  1,-3 |  1,-2 |  1,-1 |
	//     +-----------------------------------------------------------+
	//     |  2,0 |  2,1 |  2,2 |  2,3 |  2,-4 |  2,-3 |  2,-2 |  2,-1 |
	//     +-----------------------------------------------------------+
	//     |  3,0 |  3,1 |  3,2 |  3,3 |  3,-4 |  3,-3 |  3,-2 |  3,-1 |
	//     +-----------------------------------------------------------+
	//     | -4,0 | -4,1 | -4,2 | -4,3 | -4,-4 | -4,-3 | -4,-2 | -4,-1 |
	//     +-----------------------------------------------------------+
	//
	// Since the r2c FFTW transform returns an array:
	// n_1 * n_2 * (n_3 / 2 +1)
	// elements we should check if the element belongs to second half of the last
	// dimension of the output array. If yes, we should find the linked element
	// from the first half of the array and use following formula to reproduce
	// the value of the element:
	//
	// X_{k_1, k_2, ..., k_d} = X^*_{N_1 - k_1, N_2 - k_2, ..., N_d - k_d}

	int index;

	if (k > (NUM_GRID_IN_EACH_AXIS / 2)){
		index = threeToOne(NUM_GRID_IN_EACH_AXIS  - i,
				NUM_GRID_IN_EACH_AXIS - j,
				NUM_GRID_IN_EACH_AXIS  - k);

		return conj(grid_fourier[index]);
	} else {
		index = threeToOne(i, j, k);

		return grid_fourier[index];
	}
}

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
		callback_results[1] += pow(power_array[i] - callback_results[0], 2);
	}
}

void one_mode_ps (double mode_log, double mode_interval_log, fftw_complex * gird_fourier, double * callback_results) {

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

	for (i = - (NUM_GRID_IN_EACH_AXIS / 2); i < (NUM_GRID_IN_EACH_AXIS / 2); i++){
		for (j = - (NUM_GRID_IN_EACH_AXIS / 2); j < NUM_GRID_IN_EACH_AXIS; j++){
			for (k = - (NUM_GRID_IN_EACH_AXIS / 2); k < NUM_GRID_IN_EACH_AXIS / 2; k++){
				d_log = log10(sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2)));
				if (d_log >= mode_log - mode_interval_log && d_log <= mode_log + mode_interval_log) {
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
