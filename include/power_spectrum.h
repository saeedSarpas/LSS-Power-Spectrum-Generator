double rho_tilda(int * pos, fftw_complex * grid_fourier_ptr) {
	int i, index;
	index = threeToOne(pos[0], pos[1], pos[2]);

	if(index > fourierGridLength) {
		index = pow(gridLength, 3) - index;
	}

	return sqrt(pow(creal(grid_fourier_ptr[index]),2) + pow(cimag(grid_fourier_ptr[index]),2));
}

double onePointOnOneModePS (int * pos, double mode_k, double dk, fftw_complex * grid_fourier_ptr){
	int i, j, k;
	int new_pos[3];
	int counter = 0;
	double P_k = 0.0;
	double range = ceil(mode_k) + ceil(dk);
	for (i = pos[0] - range; i <= pos[0] + range; i++){
		for (j = pos[1] - range; j <= pos[1] + range; j++){
			for (k = pos[2] - range; k <= pos[2] + range; k++){
				double d;
				d = sqrt(pow(pos[0] - i,2) + pow(pos[1] - j,2) + pow(pos[2] - k,2));
				if (d > mode_k - dk && d < mode_k + dk) {
					new_pos[0] = gridBoundryChecker(i);
					new_pos[1] = gridBoundryChecker(j);
					new_pos[2] = gridBoundryChecker(k);
					P_k += rho_tilda(pos, grid_fourier_ptr) * rho_tilda(new_pos, grid_fourier_ptr);
					counter++;
				}
			}
		}
	}

	if (counter != 0) {
		return P_k / counter;
	} else {
		fprintf(stderr, "\nFind no point in this shell, you may want to change the size of \\Delata k.\n");
		exit(0);
	}
}

double oneModePS (double mode_k, double dk, fftw_complex * grid_fourier_ptr) {
	int pos[3], counter = 0;
	double P_k = 0.0;
	for (pos[0] = 0; pos[0] < gridLength; pos[0]++){
		for (pos[1] = 0; pos[1] < gridLength; pos[1]++){
			for (pos[2] = 0; pos[2] < gridLength; pos[2]++){
				P_k += onePointOnOneModePS(pos, mode_k, dk, grid_fourier_ptr);
				counter++;
			}
		}
	}

	return P_k / counter;
}
