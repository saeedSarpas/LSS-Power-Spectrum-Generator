#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <complex.h>
#include <fftw3.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/filenames_struct.h"
#include "./../../global_structs/modes_struct.h"

#include "./../../global_functions/config_file/load_config_from.h"
#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/memory/allocate.h"
#include "./../../global_functions/grid/three_to_one.h"
#include "./../../global_functions/io/open_file.h"
#include "./../../global_functions/io/write_to.h"
#include "./../../global_functions/filenames/generate_filenames.h"
#include "./../../global_functions/strings/concat.h"
#include "./../../global_functions/modes/sort_modes.h"

#include "./include/load_modes_into.h"

int main () {
	config_struct conf = load_config_from("./../../configurations.cfg");
  filenames_struct filenames = generate_filenames(&conf);

	clock_t _i_k_m_ = start("Indexing k modes... ");

	modes_struct *indexed_modes;
	int tot_num_of_grids = pow(conf.params.numOfAxisGrids, 3);
	allocate((void **)&indexed_modes, tot_num_of_grids, sizeof(modes_struct));

	load_modes_into(indexed_modes, &conf);
	sort_modes(indexed_modes, &conf);

	done(_i_k_m_);

	clock_t _s_i_m_ = start("Saving indexed modes... ");

	char *output_path = concat(2,
    "./../output/", filenames.indexedModes);

	FILE *output_file;
	open_file(&output_file, output_path, "wb");
  write_to(output_file, indexed_modes, tot_num_of_grids,
			 sizeof(modes_struct));

	done(_s_i_m_);

	return 0;
}
