int load_input(struct particle_data P[], char in_filename[256],
		struct config C) {

	int i, n;

	char input_path[256] = "./../1_load_input_file/outputs/";

	append_input_filename(in_filename, input_path);

	FILE * input_file;

	if (!(input_file = fopen(input_path , "rb"))) {
		printf("[Cannot open file `%s`]\n", input_path);
		exit(0);
	}

	for (n = 0; n < C.NumPart; n++) {
		for (i = 0; i < 3; i++) {
			fread(&P[n].Pos[i], sizeof(double), 1, input_file);
		}

		fread(&P[n].Mass, sizeof(double), 1, input_file);
	}

	fclose(input_file);
}
