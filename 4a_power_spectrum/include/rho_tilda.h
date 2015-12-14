void rho_tilda(int i, int j, int k, fftw_complex * grid_fourier,
						 fftw_complex * result) {

	// Change the order of modes by considering the location of DC mode on the
	// r2c FFTW output array

	if (i < 0) { i = NUM_GRID_IN_EACH_AXIS  + i; }
	if (j < 0) { j = NUM_GRID_IN_EACH_AXIS  + j; }
	if (k < 0) { k = NUM_GRID_IN_EACH_AXIS  + k; }

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
	// the value of the element (the output values satisfy Hermitian redundancy):
	//
	// X_{k_1, k_2, ..., k_d} = X^*_{N_1 - k_1, N_2 - k_2, ..., N_d - k_d}

	int index;

	if (i > (NUM_GRID_IN_EACH_AXIS / 2)){

		int index, ii, jj, kk;
		ii = NUM_GRID_IN_EACH_AXIS - i;
		jj = NUM_GRID_IN_EACH_AXIS - j;
		kk = NUM_GRID_IN_EACH_AXIS - k;

		index = three_to_one(ii, jj, kk);

		/* result[0] = creal(conj(grid_fourier[index])); */
		/* result[1] = cimag(conj(grid_fourier[index])); */
		*result = conj(grid_fourier[index]);
	} else {
		index = three_to_one(i, j, k);

		/* result[0] = creal(grid_fourier[index]); */
		/* result[1] = cimag(grid_fourier[index]); */
		*result = grid_fourier[index];
	}
}
