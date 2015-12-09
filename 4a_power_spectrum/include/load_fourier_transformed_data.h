void load_fourier_transformed_data(char filename[256],
								   fftw_complex * grid_fourier_delta) {

	char input_path[256] = "./../3_fftw/outputs/";

	strcat(input_path, filename);

	FILE * input_file;

	open_file(&input_file, input_path, "rb");

	size_t grid_fourier_size = pow(NUM_GRID_IN_EACH_AXIS, 2) *
		((NUM_GRID_IN_EACH_AXIS / 2) + 1);

	read_fftw_comlex_from(input_file, input_path, grid_fourier_delta,
						  grid_fourier_size);

	fclose(input_file);
}
