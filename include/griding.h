void NGP (struct particle_data P, double * grid_mass) {
	int i, j, k;

	i = P.Pos[0] / GRID_SIZE;
	j = P.Pos[1] / GRID_SIZE;
	k = P.Pos[2] / GRID_SIZE;

	int index = threeToOne(i, j, k);

	grid_mass[index] += P.Mass;
}

void cicWeight (int index, int * d_index, double overlap, double * weight) {
	double grid_half_size = GRID_SIZE / 2.0;

	if (overlap > grid_half_size) {
		*weight = 1 - (overlap / GRID_SIZE) + 0.5;
		*d_index = +1;
	} else {
		*weight = (overlap / GRID_SIZE) + 0.5;
		*d_index = -1;
	}
}

void CIC (struct particle_data P, double * grid_mass) {
	int i, j, k;
	int di, dj, dk;

	double i_weight, j_weight, k_weight;
	double overlap;

	i = P.Pos[0] / GRID_SIZE;
	overlap = fmodf(P.Pos[0], GRID_SIZE);
	cicWeight(i, &di, overlap, &i_weight);

	j = P.Pos[1] / GRID_SIZE;
	overlap = fmodf(P.Pos[1], GRID_SIZE);
	cicWeight(j, &dj, overlap, &j_weight);

	k = P.Pos[2] / GRID_SIZE;
	overlap = fmodf(P.Pos[2], GRID_SIZE);
	cicWeight(k, &dk, overlap, &k_weight);

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

void TSC (struct particle_data P, double * grid_mass) {
	int pos[3];
	double overlap;
	double weight[3][3];

	int i;
	for (i = 0; i < 3; i++) {
		pos[i] = P.Pos[i] / GRID_SIZE;
		overlap = fmodf(P.Pos[i], GRID_SIZE);

		double overlap_ratio = overlap/GRID_SIZE;
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
				grid_mass[index] += weight[0][l] * weight[1][m] * weight[2][n] * P.Mass;
			}
		}
	}
}
