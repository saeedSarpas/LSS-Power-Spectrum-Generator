void ngp (struct particle_data P, double * grid_mass, struct config C) {

	int i, j, k;

	double grid_length = C.BoxLength / NUM_GRID_IN_EACH_AXIS;

	i = P.Pos[0] / grid_length;
	j = P.Pos[1] / grid_length;
	k = P.Pos[2] / grid_length;

	int index = threeToOne(i, j, k);

	grid_mass[index] += P.Mass;
}

void cic_weigth (int index, int * d_index, double overlap, double * weight,
		struct config C) {

	double grid_length = C.BoxLength / NUM_GRID_IN_EACH_AXIS;

	double grid_half_size = grid_length / 2.0;

	if (overlap > grid_half_size) {
		*weight = 1 - (overlap / grid_length) + 0.5;
		*d_index = +1;
	} else {
		*weight = (overlap / grid_length) + 0.5;
		*d_index = -1;
	}
}

void cic (struct particle_data P, double * grid_mass, struct config C) {

	int i, j, k;
	int di, dj, dk;

	double i_weight, j_weight, k_weight, overlap;
	double grid_length = C.BoxLength / NUM_GRID_IN_EACH_AXIS;

	i = P.Pos[0] / grid_length;
	overlap = fmodf(P.Pos[0], grid_length);
	cic_weigth(i, &di, overlap, &i_weight, C);

	j = P.Pos[1] / grid_length;
	overlap = fmodf(P.Pos[1], grid_length);
	cic_weigth(j, &dj, overlap, &j_weight, C);

	k = P.Pos[2] / grid_length;
	overlap = fmodf(P.Pos[2], grid_length);
	cic_weigth(k, &dk, overlap, &k_weight, C);

	int index;
	index = threeToOne(i, j, k);
	grid_mass[index] += i_weight * j_weight * k_weight * P.Mass;

	index = threeToOne(i+di, j, k);
	grid_mass[index] += (1 - i_weight) * j_weight * k_weight * P.Mass;

	index = threeToOne(i, j+dj, k);
	grid_mass[index] += i_weight * (1 - j_weight) * k_weight * P.Mass;

	index = threeToOne(i, j, k+dk);
	grid_mass[index] += i_weight * j_weight * (1 - k_weight) * P.Mass;

	index = threeToOne(i+di, j+dj, k);
	grid_mass[index] += (1 - i_weight) * (1 - j_weight) * k_weight * P.Mass;

	index = threeToOne(i, j+dj, k+dk);
	grid_mass[index] += i_weight * (1 - j_weight) * (1 - k_weight) * P.Mass;

	index = threeToOne(i+di, j, k+dk);
	grid_mass[index] += (1 - i_weight) * j_weight * (1 - k_weight) * P.Mass;

	index = threeToOne(i+di, j+dj, k+dk);
	grid_mass[index] += (1 - i_weight) * (1 - j_weight) * (1 - k_weight) * P.Mass;
}

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
				neighbor_pos[0] = moveAlongGridAxis(pos[0], l - 1);
				neighbor_pos[1] = moveAlongGridAxis(pos[1], m - 1);
				neighbor_pos[2] = moveAlongGridAxis(pos[2], n - 1);

				index = threeToOne(neighbor_pos[0], neighbor_pos[1], neighbor_pos[2]);
				grid_mass[index] += weight[0][l] * weight[1][m] * weight[2][n]
									* P.Mass;
			}
		}
	}
}
