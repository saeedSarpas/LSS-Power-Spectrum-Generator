void tsc (struct particle_data P, double * grid_mass, struct config C) {

	int i, pos[3];
	double overlap, weight[3][3];
	double grid_length = C.BoxLength / NUM_GRID_IN_EACH_AXIS;

	for (i = 0; i < 3; i++) {
		pos[i] = P.Pos[i] / grid_length;
		overlap = fmodf(P.Pos[i], grid_length);

		double overlap_ratio = overlap/grid_length;

		weight[i][0] = 0.5  * pow((1 - overlap_ratio), 2);
		weight[i][1] = 0.75 - pow((overlap_ratio - 0.5), 2);
		weight[i][2] = 0.5  * pow(overlap_ratio, 2);
	}

	int l, m, n, index, neighbor_pos[3];
	for (l = 0; l < 3; l++) {
		for (m = 0; m < 3; m++) {
			for (n = 0; n < 3; n++) {
				neighbor_pos[0] = move_along_grid_axis(pos[0], l - 1);
				neighbor_pos[1] = move_along_grid_axis(pos[1], m - 1);
				neighbor_pos[2] = move_along_grid_axis(pos[2], n - 1);

				index = three_to_one(neighbor_pos[0], neighbor_pos[1], neighbor_pos[2]);
				grid_mass[index] += weight[0][l] * weight[1][m] * weight[2][n]
									* P.Mass;
			}
		}
	}
}
