void config_address(char in_filename[256], char * conf_addr) {
	char addr[256] = "./../1_load_input_file/outputs/";
	strcat(addr, in_filename);
	strcat(addr, CONFIG_EXT);
	strcpy(conf_addr, addr);
}

void set_config(struct config C, char in_filename[256]) {
	char conf_addr[256];
	config_address(in_filename, conf_addr);

	FILE * config_file;
	if (!(config_file = fopen(conf_addr, "w"))) {
		printf("Unable to open file!\n");
		exit(0);
	}

	fprintf(config_file, "num_part\t%d\n", C.NumPart);
	fprintf(config_file, "box_length\t%lf\n", C.BoxLength);

	fclose(config_file);
}

void get_config(struct config *C, char in_filename[256]) {
	char conf_addr[256];
	config_address(in_filename, conf_addr);

	FILE * config_file;
	if (!(config_file = fopen(conf_addr, "r"))) {
		printf("Unable to open file!\n");
		exit(0);
	}

	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int num_halo;
	int line_num = 0;

	while ((read = getline(&line, &len, config_file) != -1)) {
		if (line_num == 0) {
			sscanf(line, "num_part\t%d", &C->NumPart);
		} else if (line_num == 1) {
			sscanf(line, "box_length\t%lf", &C->BoxLength);
		}
		line_num++;
	}

	fclose(config_file);
}
