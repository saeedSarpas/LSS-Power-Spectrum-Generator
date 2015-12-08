void ngp (struct particle_data P, double * grid_mass, struct config C) {

	int i, j, k;

	double grid_length = C.BoxLength / NUM_GRID_IN_EACH_AXIS;

	i = P.Pos[0] / grid_length;
	j = P.Pos[1] / grid_length;
	k = P.Pos[2] / grid_length;

	int index = three_to_one(i, j, k);

	grid_mass[index] += P.Mass;
}
