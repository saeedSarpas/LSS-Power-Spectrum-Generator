void load_density_contrast_grid(char filename[256], double * grid_delta) {

	char input_path[256] = "./../2_griding/outputs/";

	strcat(input_path, filename);

	FILE * input_file;
	open_file(&input_file, input_path, "r");

	size_t tot_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);

	read_double_from_file(input_file, input_path, grid_delta, tot_num_grid);

	fclose(input_file);
}
