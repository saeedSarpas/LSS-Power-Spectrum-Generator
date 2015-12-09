void load_indexed_modes(struct modes * M[]) {

  size_t total_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);

  char imi_path[256] = "./../4b_indexing_k_modulus/outputs/";
  append_indexed_modes_filename(imi_path);

  FILE * indexed_mode_file;

  open_file(&indexed_mode_file, imi_path, "rb");

	if (fread(*M, sizeof(struct modes), total_num_grid,
            indexed_mode_file) != total_num_grid) {
		printf("[Cannot read file %s]", imi_path);
		exit(0);
	};

  fclose(indexed_mode_file);
}
