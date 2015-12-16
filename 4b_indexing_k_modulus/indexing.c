#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <complex.h>
#include <fftw.h>

#include "./../configurations.h"
#include "./../global_functions/grid.h"
#include "./../global_functions/clock.h"
#include "./../global_functions/filenames.h"
#include "./../global_functions/memory_allocation.h"
#include "./../global_functions/file_handling.h"

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

	clock_t _i_k_m_ = start("Indexing k modes... ");

	int total_num_grid = pow(NUM_GRID_IN_EACH_AXIS, 3);
	allocate_struct_modes_array(&M, total_num_grid);

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

	done(_i_k_m_);

	clock_t _s_i_m_ = start("Saving indexed modes... ");

	char output_path[256] = "./outputs/";
	append_indexed_modes_filename(output_path);

	FILE * output_file;

	open_file(&output_file, output_path, "wb");

	write_struct_modes_to(output_file, M, total_num_grid, output_path);

	done(_s_i_m_);

	return 0;
}
