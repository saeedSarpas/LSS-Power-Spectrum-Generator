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

#include "./include/load_modes_into.h"
#include "./include/sort.h"

int main () {

	config_struct conf;
	get_config(&conf, "./../../configurations.cfg");

	clock_t _i_k_m_ = start("Indexing k modes... ");

	modes_struct *indexed_modes;
	int tot_num_of_grids = pow(conf.run_params.num_of_axis_grids, 3);
	allocate_modes_struct(&indexed_modes, tot_num_of_grids);

	load_modes_into(indexed_modes, &conf);
	sort(indexed_modes, &conf);

	done(_i_k_m_);

	clock_t _s_i_m_ = start("Saving indexed modes... ");

	char *output_path = strdup("./../output/");
	append_indexed_modes_filename(&conf, &output_path);

	FILE *output_file;
	open_file(&output_file, output_path, "wb");
	write_modes_struct_to(output_file, indexed_modes, tot_num_of_grids,
			output_path);

	done(_s_i_m_);

	return 0;
}
