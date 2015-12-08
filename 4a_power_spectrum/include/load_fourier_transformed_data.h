void load_fourier_transformed_data(char filename[256],
		fftw_complex * grid_fourier_delta) {

	char input_path[256] = "./../3_fftw/outputs/";

	strcat(input_path, filename);

	FILE * input_file;

	if (!(input_file = fopen(input_path , "rb"))) {
		printf("[Cannot open file `%s`]\n", input_path);
		exit(0);
	}

	size_t grid_fourier_size = pow(NUM_GRID_IN_EACH_AXIS, 2) *
		((NUM_GRID_IN_EACH_AXIS / 2) + 1);

	if (fread(grid_fourier_delta, sizeof(fftw_complex), grid_fourier_size,
				input_file) != grid_fourier_size) {
		printf("[Cannot read file %s]", input_path);
		exit(0);
	};

	fclose(input_file);
}
