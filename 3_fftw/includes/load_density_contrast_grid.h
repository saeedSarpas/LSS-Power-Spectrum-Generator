void load_density_contrast_grid(char filename[256], double * grid_delta) {

	char input_path[256] = "./../2_griding/outputs/";

	strcat(input_path, filename);

	FILE * input_file;

	if(!(input_file = fopen(input_path, "r"))) {
		printf("[Cannot open file `%s`]\n", input_path);
		exit(0);
	}

	int total_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);

	if(fread(grid_delta, sizeof(double), total_num_grid, input_file) !=
			total_num_grid) {
		printf("[Cannot read from file %s]", input_path);
		exit(0);
	}

	fclose(input_file);
}
