#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <fftw3.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "./../configurations.h"
#include "./../global_functions/clock.h"
#include "./../global_functions/choosing.h"
#include "./../global_functions/config_file.h"
#include "./../global_functions/filenames.h"
#include "./../global_functions/grid.h"

#include "./include/select_modes_with_length.h"

int main () {
  char load_indexed_modes_msg[256] = "Loading input data... ";
  clock_t start_loading = start(load_indexed_modes_msg);

  size_t total_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);
  if (!(M = malloc(total_num_grid * sizeof(struct modes)))) {
    printf("[Faild to allocate memory]\n");
    exit(0);
  }

  char imi_path[256] = "./../4b_indexing_k_modulus/outputs/";
  append_indexed_modes_filename(imi_path);

  FILE * indexed_mode_file;

	if(!(indexed_mode_file = fopen(imi_path, "rb"))) {
		printf("[Cannot open file %s]\n", imi_path);
		exit(0);
	}

	if (fread(M, sizeof(struct modes), total_num_grid,
            indexed_mode_file) != total_num_grid) {
		printf("[Cannot read file %s]", imi_path);
		exit(0);
	};

  done(start_loading);

  char finding_triangles_msg[256] = "Finding triangles... ";
  clock_t ft_start = start(finding_triangles_msg);

  unsigned int index1, index2;
  int vec1[3], vec2[3], sum_vec[3];
  double vec1_length, vec2_length, vec3_length;

  int * indices;
  if (!(indices = malloc(total_num_grid * sizeof(int)))) {
    printf("[Faild to allocate memory]\n");
    exit(0);
  }

  int counter = 0;
  for (index1 = 0; index1 < total_num_grid; index1++) {
    for (index2 = 0; index2 < total_num_grid; index2++) {

      one_to_three(index1, vec1);
      one_to_three(index2, vec2);

      // \vec{k_1} + \vec{k_2} = \vec{k_3}

      sum_vec[0] = vec1[0] + vec2[0];
      sum_vec[1] = vec1[1] + vec2[1];
      sum_vec[2] = vec1[2] + vec2[2];

      vec1_length = sqrt(pow(vec1[0], 2) + pow(vec1[1], 2) + pow(vec1[2], 2));
      vec2_length = sqrt(pow(vec2[0], 2) + pow(vec2[1], 2) + pow(vec2[2], 2));
      vec3_length = sqrt(pow(sum_vec[0], 2) + pow(sum_vec[1], 2) + pow(sum_vec[2], 2));

      if (vec1_length == vec2_length && vec2_length == vec3_length) {
        select_modes_with_length(&M, vec3_length, indices);
        // indices:
        // +---+----------+-----------------------+--------------+
        // | N | index 1 | index 2 ... index N | unset memory |
        // +---+----------+-----------------------+--------------+
        if (indices[0] > 0){
          int i;
          for (i = 1; i <= indices[0]; i++) {
            if (sum_vec[0] != 0 && M[indices[i]].kx + sum_vec[0] == 0) {
              if (sum_vec[1] != 0 && M[indices[i]].ky + sum_vec[1] == 0) {
                if (sum_vec[2] != 0 && M[indices[i]].kz + sum_vec[2] == 0) {
                  counter++;
                }
              }
            }
          }
        }
      }
    }
    fflush(stdout);
    printf("\n %d\t%d\n", index1, counter);
  }

  done(ft_start);

  return 0;
}
