double complex rho_tilda(int i, int j, int k, fftw_complex * grid_fourier) {
	bool negative_mode = false;
 	if (i < 0){ negative_mode = true; }
 	if (j < 0){ negative_mode = true; }
 	if (k < 0){ negative_mode = true; }

	int index = threeToOne(abs(i), abs(j), abs(k));

	if (negative_mode){
		return conj(grid_fourier[index]);
	} else {
		return grid_fourier[index];
	}
}

double complex oneModePS (double mode_log, double mode_interval_log, fftw_complex * gird_fourier){
	int i, j, k, counter = 0;
	double complex P_k = 0.0 + 0.0 * I, rho;
	double d_log;
	for (i = - (NUM_GRID_BLOCKS / 2); i <= NUM_GRID_BLOCKS / 2; i++){
		for (j = - (NUM_GRID_BLOCKS / 2); j <= NUM_GRID_BLOCKS / 2; j++){
			for (k = - (NUM_GRID_BLOCKS / 2); k <= NUM_GRID_BLOCKS / 2; k++){
				d_log = log10(sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2)));
				if (d_log >= mode_log - mode_interval_log && d_log <= mode_log + mode_interval_log) {
					P_k += rho_tilda(i, j, k, gird_fourier);
					counter++;
				}
			}
		}
	}

	if (counter != 0) {
		return P_k / counter;
	} else {
		printf("\nFind no point in this shell, log10(mode)= %f and log10(mode_interval)= %f\n", mode_log, mode_interval_log);
		exit(0);
	}
}
