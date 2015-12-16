void open_file(FILE ** file, char * path, char * mode) {
	if ( !(*file = fopen(path, mode))) {
		printf("[Cannot open file %s]\n", path);
		exit(0);
	}
}

void write_struct_particle_data_to(FILE * file, struct particle_data * p,
								   size_t nmemb, char * file_path) {
	if (fwrite(p, sizeof(struct particle_data), nmemb, file) != nmemb) {
		printf("[Cannot write to file %s]\n", file_path);
		exit(0);
	}
}

void write_struct_modes_to(FILE * file, struct modes * m,
						   size_t nmemb, char * file_path) {
	if (fwrite(m, sizeof(struct modes), nmemb, file) != nmemb) {
		printf("[Cannot write to file %s]\n", file_path);
		exit(0);
	}
}

void write_struct_triangle_to_file(struct triangles * t, size_t nmemb,
								   FILE * file, char * file_path) {
	if (fwrite(t, sizeof(struct triangles), nmemb, file) != nmemb) {
		printf("[Cannot write to file %s]\n", file_path);
		exit(0);
	}
}

void write_fftw_complex_to_file(FILE * file, char * file_path,
								fftw_complex * f, size_t size) {
	if (fwrite(f, sizeof(fftw_complex), size, file) != size) {
		printf("[Cannot write to file %s]", file_path);
		exit(0);
	}
}

void write_double_to_file(FILE * file, double * d, size_t nmemb,
						  char * file_path) {
	if (fwrite(d, sizeof(double), nmemb, file) != nmemb) {
		printf("[Cannot write to file %s]\n", file_path);
		exit(0);
	}
}

void read_struct_particle_data_from(FILE * file, struct particle_data * p,
									size_t size, char * file_path) {
	if (fread(p, sizeof(struct particle_data), size, file) != size) {
		printf("[Cannot read from file %s]", file_path);
		exit(0);
	}
}

void read_double_from_file(FILE * file, char * file_path, double * d,
						   size_t size) {
	if (fread(d, sizeof(double), size, file) != size) {
		printf("[Cannot read from file %s]", file_path);
		exit(0);
	}
}

void read_fftw_comlex_from(FILE * file, char * file_path, fftw_complex * f,
						   size_t size) {
	if (fread(f, sizeof(fftw_complex), size, file) != size) {
		printf("[Cannot read from file %s]\n", file_path);
		exit(0);
	}
}
