void cic_weigth (int index, int * d_index, double overlap, double * weight,
		double * grid_length) {

	double grid_half_size = *grid_length / 2.0;

	if (overlap > grid_half_size) {
		*weight = 1 - (overlap / *grid_length) + 0.5;
		*d_index = +1;
	} else {
		*weight = (overlap / *grid_length) + 0.5;
		*d_index = -1;
	}
}

void cic (struct particle_data * P, double * grid_mass, struct config * C) {

	int i, j, k, n, index;
	int di, dj, dk;

	double i_weight, j_weight, k_weight, overlap;
	double grid_length = C->BoxLength / NUM_GRID_IN_EACH_AXIS;

	for (n = 0; n < C->NumPart; n++) {
		i = P[n].Pos[0] / grid_length;
		overlap = fmodf(P[n].Pos[0], grid_length);
		cic_weigth(i, &di, overlap, &i_weight, &grid_length);

		j = P[n].Pos[1] / grid_length;
		overlap = fmodf(P[n].Pos[1], grid_length);
		cic_weigth(j, &dj, overlap, &j_weight, &grid_length);

		k = P[n].Pos[2] / grid_length;
		overlap = fmodf(P[n].Pos[2], grid_length);
		cic_weigth(k, &dk, overlap, &k_weight, &grid_length);

		index = three_to_one(i, j, k);
		grid_mass[index] += i_weight * j_weight * k_weight * P[n].Mass;

		index = three_to_one(i+di, j, k);
		grid_mass[index] += (1 - i_weight) * j_weight * k_weight * P[n].Mass;

		index = three_to_one(i, j+dj, k);
		grid_mass[index] += i_weight * (1 - j_weight) * k_weight * P[n].Mass;

		index = three_to_one(i, j, k+dk);
		grid_mass[index] += i_weight * j_weight * (1 - k_weight) * P[n].Mass;

		index = three_to_one(i+di, j+dj, k);
		grid_mass[index] += (1 - i_weight) * (1 - j_weight) * k_weight * P[n].Mass;

		index = three_to_one(i, j+dj, k+dk);
		grid_mass[index] += i_weight * (1 - j_weight) * (1 - k_weight) * P[n].Mass;

		index = three_to_one(i+di, j, k+dk);
		grid_mass[index] += (1 - i_weight) * j_weight * (1 - k_weight) * P[n].Mass;

		index = three_to_one(i+di, j+dj, k+dk);
		grid_mass[index] += (1 - i_weight) * (1 - j_weight) * (1 - k_weight) * P[n].Mass;
	}
}
