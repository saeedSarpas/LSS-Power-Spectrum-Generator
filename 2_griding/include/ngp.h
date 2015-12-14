void ngp (struct particle_data * P, double * grid_mass, struct config * C) {

	int i, j, k, n;

	double grid_length = C->BoxLength / NUM_GRID_IN_EACH_AXIS;

	for (n = 1; n < C->NumPart; n++) {
		i = P[n].Pos[0] / grid_length;
		j = P[n].Pos[1] / grid_length;
		k = P[n].Pos[2] / grid_length;

		int index = three_to_one(i, j, k);

		grid_mass[index] += P->Mass;
	}
}
