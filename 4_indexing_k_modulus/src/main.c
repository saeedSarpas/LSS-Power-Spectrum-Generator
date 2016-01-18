#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <complex.h>
#include <fftw.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/modes_struct.h"

#include "./../../global_functions/config_file/get_config.h"
#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/memory/allocate_modes_struct.h"
#include "./../../global_functions/grid/three_to_one.h"
#include "./../../global_functions/filenames/append_indexed_modes_filename.h"
#include "./../../global_functions/open_file.h"
#include "./../../global_functions/io/write_modes_struct_to.h"

static int comp_func (const void * m1, const void * m2) {
	const modes *s1 = m1;
	const modes *s2 = m2;

	if (s1->length > s2->length) {
		return 1;
	} else if (s1->length < s2->length) {
		return -1;
	} else {
		return 0;
	}
}

int main () {

	config conf;
	get_config(&conf);

	clock_t _i_k_m_ = start("Indexing k modes... ");

	modes *modes;
	int tot_num_of_grids = pow(conf.num_of_grids_in_each_axis, 3);
	allocate_modes_struct(&modes, tot_num_of_grids);

	int half_grid_box_size = conf.num_of_grids_in_each_axis / 2;
	int index, i, j, k;
	for (i = - half_grid_box_size; i < half_grid_box_size; i++) {
		for (j = - half_grid_box_size; j < half_grid_box_size; j++) {
			for (k = - half_grid_box_size; k < half_grid_box_size; k++) {
				index = three_to_one(i, j, k, &conf);
				modes[index].index = index;
				modes[index].kx = i;
				modes[index].ky = j;
				modes[index].kz = k;
				modes[index].length = sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2));
			}
		}
	}

	qsort(&modes[0], tot_num_of_grids, sizeof(modes), comp_func);

	done(_i_k_m_);

	clock_t _s_i_m_ = start("Saving indexed modes... ");

	char *output_path = strdup("./../output/");
	append_indexed_modes_filename(&output_path, &conf);

	FILE * output_file;
	open_file(&output_file, output_path, "wb");
	write_modes_struct_to(output_file, modes, tot_num_of_grids, output_path);

	done(_s_i_m_);

	return 0;
}
