#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "./../configurations.h"
#include "./../global_functions/grid.h"
#include "./../global_functions/clock.h"
#include "./../global_functions/filenames.h"

int comp_func (const void * m1, const void * m2) {
  const struct modes *s1 = m1;
  const struct modes *s2 = m2;

  if (s1->length > s2->length) {
    return 1;
  } else if (s1->length < s2->length) {
    return -1;
  } else {
    return 0;
  }
}

int main () {
  char indexing_msg[256] = "Indexing k modes... ";
  clock_t begin_indexing = start(indexing_msg);

  int total_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);
  if (!(M = malloc(total_num_grid * sizeof(struct modes)))) {
    printf("[Faild to allocate memory]\n");
    exit(0);
  }

  int index, i, j, k;
  for (i = - NUM_GRID_IN_EACH_AXIS; i < NUM_GRID_IN_EACH_AXIS; i++) {
    for (j = - NUM_GRID_IN_EACH_AXIS; j < NUM_GRID_IN_EACH_AXIS; j++) {
      for (k = - NUM_GRID_IN_EACH_AXIS; k < NUM_GRID_IN_EACH_AXIS; k++) {
        index = three_to_one(i, j, k);
        M[index].index = index;
        M[index].kx = i;
        M[index].ky = j;
        M[index].kz = k;
        M[index].length = sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2));
      }
    }
  }

  qsort(&M[0], total_num_grid, sizeof(struct modes), comp_func);

  done(begin_indexing);

  char save_msg[256] = "Saving indexed modes... ";
  clock_t begin_saving = start(save_msg);

  char output_path[256] = "./outputs/";
  append_indexed_modes_filename(output_path);

  FILE * output_file;

	if(!(output_file = fopen(output_path, "wb"))) {
		printf("[Cannot open file %s]\n", output_path);
		exit(0);
	}

	if(fwrite(M, sizeof(struct modes), total_num_grid,
            output_file) != total_num_grid) {
		printf("[Cannot write on file %s]", output_path);
		exit(0);
	}

  done(begin_saving);

  return 0;
}
