void str_concat(char * strings[], int length, char return_path[256]) {
	int i;
	for (i = 0; i < length; i++) {
		strcat(return_path, strings[i]);
	}
}

void append_input_filename(char * filename, char return_path[256]) {
	char * strings[] = {filename, ".dat"};
	str_concat(strings, 2, return_path);
}

void append_density_contrast_filename(char in_file[256], char alg_name[256],
		struct config C, char return_path[256]) {

	char num_grid_in_each_axis[5];
	sprintf(num_grid_in_each_axis, "%d", NUM_GRID_IN_EACH_AXIS);

	char num_part[16];
	sprintf(num_part, "%d", C.NumPart);

	char * strings[] = {"density-contrast-grid-", alg_name, "-",
		num_grid_in_each_axis, "-", in_file, "-", num_part, ".dat"};

	str_concat(strings, 9, return_path);
}

void append_fourier_transformed_filename(char in_file[256], char alg_name[256],
		struct config C, char return_path[256]) {

	char num_grid_in_each_axis[5];
	sprintf(num_grid_in_each_axis, "%d", NUM_GRID_IN_EACH_AXIS);

	char num_part[16];
	sprintf(num_part, "%d", C.NumPart);

	char * strings[] = {"fourier-transformed-grid-", alg_name, "-",
		num_grid_in_each_axis, "-", in_file, "-", num_part, ".dat"};

	str_concat(strings, 9, return_path);
}

void append_power_spectrum_filename(char in_file[256], char alg_name[256],
		struct config C, char return_path[256]) {

	char num_grid_in_each_axis[3];
	sprintf(num_grid_in_each_axis, "%d", NUM_GRID_IN_EACH_AXIS);

	char num_part[16];
	sprintf(num_part, "%d", C.NumPart);

	char * strings[] = {"power_spectrum-", alg_name, "-",
		num_grid_in_each_axis, "-", in_file, "-", num_part, ".dat"};

	str_concat(strings, 9, return_path);
}