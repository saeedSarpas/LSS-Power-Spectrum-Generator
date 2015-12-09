void failed_message (char * t_name, size_t size) {
  printf("[Faild to allocate memory for an array of %s with length %d]\n",
         t_name, (int)size);
}

void allocate_struct_modes_array (struct modes ** m, size_t size) {
  if( !(*m = malloc(size * sizeof(struct modes)))) {
    failed_message("struct modes", size);
    exit(0);
  }
}

void allocate_struct_triangles_array (struct triangles ** t, size_t size) {
  if( !(*t = malloc(size * sizeof(struct triangles)))) {
    failed_message("struct triangles", size);
    exit(0);
  }
}

void allocate_int_array (int ** i, size_t size) {
  if( !(*i = malloc(size * sizeof(int)))) {
    failed_message("int", size);
    exit(0);
  }
}
