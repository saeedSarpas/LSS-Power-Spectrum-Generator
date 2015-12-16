void rho_tilda(int i, int j, int k, fftw_complex * grid_fourier,
						 fftw_complex * result) {

	i += NUM_GRID_IN_EACH_AXIS / 2;
	j += NUM_GRID_IN_EACH_AXIS / 2;
	k += NUM_GRID_IN_EACH_AXIS / 2;

	int index = three_to_one(i, j, k);
	*result = grid_fourier[index];
}
