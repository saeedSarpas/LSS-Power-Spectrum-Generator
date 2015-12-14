int load_sturctured_input(struct particle_data P[], char input_path[256],
		struct config C) {

	FILE * input_file;

	open_file(&input_file, input_path, "rb");

	read_struct_particle_data_from(input_file, P, C.NumPart, input_path);

	fclose(input_file);
}
