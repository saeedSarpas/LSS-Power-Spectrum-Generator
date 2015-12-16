clock_t start (char message[256]) {

	printf(message, 256);
	fflush(stdout);

	clock_t begin;
	begin = clock();

	return begin;
}

void done (clock_t begin) {

	clock_t end = clock();

	double duration;
	duration = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("[done in %f sec]\n", duration);
	fflush(stdout);
}
