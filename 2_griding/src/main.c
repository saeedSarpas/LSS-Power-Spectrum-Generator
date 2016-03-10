#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/particle_struct.h"
#include "./../../global_structs/info_strcut.h"
#include "./../../global_structs/filenames_struct.h"

#include "./../../global_functions/config_file/load_config_from.h"
#include "./../../global_functions/io/open_file.h"
#include "./../../global_functions/io/write_to.h"
#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/memory/allocate.h"
#include "./../../global_functions/info_file/get_info_from.h"
#include "./../../global_functions/grid/three_to_one.h"
#include "./../../global_functions/filenames/generate_filenames.h"
#include "./../../global_functions/strings/concat.h"

#include "./include/load_input.h"
#include "./include/cic.h"
#include "./include/tsc.h"
#include "./include/ngp.h"
#include "./include/density_contrast.h"

int main() {
	config_struct conf = load_config_from("./../../configurations.cfg");
  filenames_struct filenames = generate_filenames(&conf);

  char *info_path = concat(2,
    "./../../0_structured_input/", filenames.inputInfo);
	info_struct info = get_info_from(info_path);


	clock_t _r_g_i_ = start("Reading griding input... ");

	particle_struct *P;
	allocate((void **)&P, info.numOfParts, sizeof(struct particle));

	char *input_path = concat(2,
    "./../../0_structured_input/", filenames.structuredInput);

	load_input(P, input_path, &info);

	done(_r_g_i_);


	double *grid_mass;
  int tot_num_of_grids = pow(conf.params.numOfAxisGrids, 3);
	char *alg_alias = conf.massFunctions[conf.params.massAssignmentIndex].alias;
  allocate((void **)&grid_mass, tot_num_of_grids, sizeof(double));

	if (strcmp(alg_alias, "cic") == 0) {
		clock_t begin = start("Griding using cloud in cell (CIC) algorithm... ");
		cic(P, grid_mass, &info, &conf);
		done(begin);
	} else if (strcmp(alg_alias, "tsc") == 0) {
		clock_t begin = start("Griding using triangular shaped cloud (TSC) algorithm... ");
		tsc(P, grid_mass, &info, &conf);
		done(begin);
	} else if (strcmp(alg_alias, "ngp") == 0) {
		clock_t begin = start("Griding using nearest grid points (NGP) algorithm... ");
		ngp(P, grid_mass, &info, &conf);
		done(begin);
	} else {
		printf("[Wrong algorithm]\n");
		exit(0);
	}

	clock_t _c_d_c_ = start("Calculating density contrast... ");

	double *grid_delta;
	allocate((void **)&grid_delta, tot_num_of_grids, sizeof(double));

	density_contrast(grid_mass, &info, &conf, grid_delta);

	done(_c_d_c_);

	clock_t _s_g_b_ = start("Saving griding (binary)... ");

	FILE *output_file;
	char *output_path = concat(2,
    "./../output/", filenames.densityContrast);
	open_file(&output_file, output_path, "wb");

	write_to(output_file, grid_delta, tot_num_of_grids, sizeof(double));

	fclose(output_file);

	done(_s_g_b_);

	clock_t _s_g_a_ = start("Saving griding (ascii)... ");

	FILE * ascii_output_file;
	char *ascii_output_path = concat(2,
    "./../output/ascii-", filenames.densityContrast);
	open_file(&ascii_output_file, ascii_output_path, "w");

	int i, j, k, index;
	for (i = 0; i < conf.params.numOfAxisGrids; i++) {
		for (j = 0; j < conf.params.numOfAxisGrids; j++) {
			for (k = (conf.params.numOfAxisGrids / 2);
				 k < (conf.params.numOfAxisGrids / 2) + 1; k++) {

				index = three_to_one(i, j, k, &conf);
				fprintf(ascii_output_file, "%d\t%d\t%f\n", i, j, grid_delta[index]);
			}
		}
	}

	fclose(ascii_output_file);

	done(_s_g_a_);

	free(P);
	free(grid_delta);
	free(alg_alias);
	free(info_path);
	free(input_path);
	free(output_path);
	free(ascii_output_path);
	return 0;
}
