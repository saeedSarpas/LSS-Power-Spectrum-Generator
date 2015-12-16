void fill_fftw_complex_grid_delta(double * temp, fftw_complex * grid_delta) {
	int i;
	size_t tot_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);

	for (i = 0; i < tot_num_grid; i++) {
		grid_delta[i] = temp[i] + 0.0 * I;
	}
}
