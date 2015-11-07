int gridBoundryChecker (int pos) {
	if (pos > gridLength - 1) {
		return pos - gridLength;
	} else if (pos < 0) {
		return pos + gridLength;
	} else {
		return pos;
	}
}

int threeToOne(int i, int j, int k) {
	i = gridBoundryChecker(i);
	j = gridBoundryChecker(j);
	k = gridBoundryChecker(k);

	return k * gridLength * gridLength + j * gridLength + i;
}

int moveAlongGridAxis(int init_pos, int step) {
	int new_pos = init_pos + step;
	return gridBoundryChecker(new_pos);
}
