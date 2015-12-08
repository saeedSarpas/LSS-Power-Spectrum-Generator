void density_contrast(double * grid_mass, struct config C,
		double * grid_delta) {

	int n, total_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);

	double grid_length = C.BoxLength / NUM_GRID_IN_EACH_AXIS;
	double grid_block_volume = pow(grid_length, 3);

	double mean_density, total_mass = 0.0f;

	for (n = 0; n < total_num_grid; n++) {
		total_mass += grid_mass[n];
	}

	mean_density = total_mass / pow(C.BoxLength, 3);

	for (n = 0; n < total_num_grid; n++) {
		grid_delta[n] = ((grid_mass[n] / grid_block_volume) / mean_density) - 1;
	}
}
