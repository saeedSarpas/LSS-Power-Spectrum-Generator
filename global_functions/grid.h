int gridBoundryChecker (int pos) {
	if (pos > NUM_GRID_IN_EACH_AXIS - 1) {
		return pos - NUM_GRID_IN_EACH_AXIS;
	} else if (pos < 0) {
		return pos + NUM_GRID_IN_EACH_AXIS;
	} else {
		return pos;
	}
}

int threeToOne(int i, int j, int k) {
	i = gridBoundryChecker(i);
	j = gridBoundryChecker(j);
	k = gridBoundryChecker(k);

	return k * NUM_GRID_IN_EACH_AXIS * NUM_GRID_IN_EACH_AXIS + j * NUM_GRID_IN_EACH_AXIS + i;
}

int moveAlongGridAxis(int init_pos, int step) {
	int new_pos = init_pos + step;
	return gridBoundryChecker(new_pos);
}
