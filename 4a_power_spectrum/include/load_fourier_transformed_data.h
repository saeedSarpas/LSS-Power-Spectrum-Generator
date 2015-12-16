void load_fourier_transformed_data(char input_path[256],
								   fftw_complex * grid_fourier) {

	FILE * input_file;

	open_file(&input_file, input_path, "rb");

	size_t tot_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);

	read_fftw_comlex_from(input_file, input_path, grid_fourier,
						  tot_num_grid);

	fclose(input_file);
}
