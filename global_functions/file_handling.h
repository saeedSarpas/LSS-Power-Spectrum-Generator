void open_file(FILE ** file, char * path, char * mode) {
  if ( !(*file = fopen(path, mode))) {
    printf("[Cannot open file %s]\n", path);
    exit(0);
  }
}

void write_struct_triangle_to_file(struct triangles * t,
                                   size_t nmemb, FILE * file, char * file_path) {
  if (fwrite(t, sizeof(struct triangles), nmemb, file) != nmemb) {
    printf("[Cannot write to file %s]\n", file_path);
    exit(0);
  }
}

void write_double_to_file(double * d, size_t nmemb, FILE * file,
                          char * file_path) {
  if (fwrite(d, sizeof(double), nmemb, file) != nmemb) {
    printf("[Cannot write to file %s]\n", file_path);
    exit(0);
  }
}
