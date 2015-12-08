int grid_boundry_checker (int pos) {
	if (pos > NUM_GRID_IN_EACH_AXIS - 1) {
		return pos - NUM_GRID_IN_EACH_AXIS;
	} else if (pos < 0) {
		return pos + NUM_GRID_IN_EACH_AXIS;
	} else {
		return pos;
	}
}

int three_to_one (int i, int j, int k) {
	i = grid_boundry_checker(i);
	j = grid_boundry_checker(j);
	k = grid_boundry_checker(k);

	return k * pow(NUM_GRID_IN_EACH_AXIS, 2) + j * NUM_GRID_IN_EACH_AXIS + i;
}

void one_to_three (int x, int * pos) {
  int ret = x % (int)pow(NUM_GRID_IN_EACH_AXIS, 2);

  pos[0] = x / pow(NUM_GRID_IN_EACH_AXIS, 2);
  pos[1] = ret / NUM_GRID_IN_EACH_AXIS;
  pos[2] = ret % NUM_GRID_IN_EACH_AXIS;

  int i;
  for (i = 0; i < 3; i++) {
    if (pos[i] >= (NUM_GRID_IN_EACH_AXIS / 2)) {
      pos[i] -= NUM_GRID_IN_EACH_AXIS;
    }
  }
}

int move_along_grid_axis (int init_pos, int step) {
	int new_pos = init_pos + step;
	return grid_boundry_checker(new_pos);
}
