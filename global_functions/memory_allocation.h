void failed_message (char * t_name, size_t size) {
  printf("[Faild to allocate memory for an array of %s with length %d]\n",
         t_name, (int)size);
}

void allocate_struct_config(struct config ** c) {
  if ( !(*c = malloc(sizeof(struct config)))) {
    failed_message("struct config", 1);
    exit(0);
  }
}

void allocate_struct_particle_data_array (struct particle_data ** p,
                                          size_t size) {
  if( !(*p = malloc(size * sizeof(struct particle_data)))) {
    failed_message("struct particle data", size);
    exit(0);
  }
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
