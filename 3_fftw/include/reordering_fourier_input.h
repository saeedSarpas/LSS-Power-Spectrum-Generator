void reordering_fourier_input(fftw_complex * grid_delta) {
	// This function reorders the Fourier input in a way that the zero-th
	// element lies at the center of the output array

	int i, pos[3];
	size_t tot_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);

	for (i = 0; i < tot_num_grid; i++) {
		one_to_three(i, pos);
		if ((pos[0] + pos[1] + pos[2]) % 2 != 0) {
			grid_delta[i] = -1 * grid_delta[i];
		}
	}
}
