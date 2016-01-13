#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "./../../global_functions/config_file/get_config.h"
#include "./../../global_functions/io/get_algorithm_alias.h"
#include "./../../global_functions/io/get_input_filename_alias.h"
#include "./../../global_functions/io/write_double_to.h"
#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/memory/allocate_particle_data_struct.h"
#include "./../../global_functions/memory/allocate_double_array.h"
#include "./../../global_functions/filenames/append_input_infos_name.h"
#include "./../../global_functions/filenames/append_input_name.h"
#include "./../../global_functions/filenames/append_density_contrast_filename.h"
#include "./../../global_functions/info_file/read_input_file_infos.h"
#include "./../../global_functions/grid/three_to_one.h"
#include "./../../global_functions/open_file.h"

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/particle_data_struct.h"
#include "./../../global_structs/input_file_infos.h"

#include "./include/load_input.h"
#include "./include/cic.h"
#include "./include/tsc.h"
#include "./include/ngp.h"
#include "./include/density_contrast.h"

int main() {
	config conf;
	get_config(&conf);

	char *input_filename_alias;
	input_filename_alias = get_input_filename_alias(&conf);

	char *algorithm_alias;
	algorithm_alias = get_algorithm_alias(&conf);

	input_file_infos info;
	char *input_info_path = strdup("./../../0_structured_input/");
	append_input_infos_name(input_filename_alias, &input_info_path);
	read_input_file_infos(&info, input_info_path);

	clock_t _r_g_i_ = start("Reading griding input... ");

	particle_data *P;
	allocate_particle_data_struct(&P, info.num_of_parts);

	char *input_path = strdup("./../../0_structured_input/");
	append_input_name(input_filename_alias, &input_path);

	load_input(P, input_path, &info);

	done(_r_g_i_);


	double * grid_mass;
	size_t tot_num_of_grids = pow(conf.num_of_grids_in_each_axis, 3);
	allocate_double_array(&grid_mass, tot_num_of_grids);

	if (strcmp(algorithm_alias, conf.cic_alias) == 0) {
		char alg[256] = "Griding using cloud in cell (CIC) algorithm... ";
		clock_t begin = start(alg);
		cic(P, grid_mass, &info, &conf);
		done(begin);
	} else if (strcmp(algorithm_alias, conf.tsc_alias) == 0) {
		char alg[256] = "Griding using triangular shaped cloud (TSC) algorithm... ";
		clock_t begin = start(alg);
		tsc(P, grid_mass, &info, &conf);
		done(begin);
	} else if (strcmp(algorithm_alias, conf.ngp_alias) == 0) {
		char alg[256] = "Griding using nearest grid points (NGP) algorithm... ";
		clock_t begin = start(alg);
		ngp(P, grid_mass, &info, &conf);
		done(begin);
	} else {
		printf("[Wrong algorithm]\n");
		exit(0);
	}

	clock_t _c_d_c_ = start("Calculating density contrast... ");

	double * grid_delta;
	allocate_double_array(&grid_delta, tot_num_of_grids);

	density_contrast(grid_mass, &info, &conf, grid_delta);

	done(_c_d_c_);

	clock_t _s_g_b_ = start("Saving griding (binary)... ");

	FILE *output_file;
	char *output_path = strdup("./../output/");
	append_density_contrast_filename(input_filename_alias, algorithm_alias,
									 &info, &conf, &output_path);
	open_file(&output_file, output_path, "wb");

	write_double_to(output_file, grid_delta, tot_num_of_grids, output_path);

	fclose(output_file);

	done(_s_g_b_);

	clock_t _s_g_a_ = start("Saving griding (ascii)... ");

	FILE * ascii_output_file;
	char *ascii_output_path = strdup("./../output/ascii-");
	append_density_contrast_filename(input_filename_alias, algorithm_alias,
									 &info, &conf, &ascii_output_path);
	open_file(&ascii_output_file, ascii_output_path, "w");

	int i, j, k, index;
	for (i = 0; i < conf.num_of_grids_in_each_axis; i++) {
		for (j = 0; j < conf.num_of_grids_in_each_axis; j++) {
			for (k = (conf.num_of_grids_in_each_axis / 2);
				 k < (conf.num_of_grids_in_each_axis / 2) + 1; k++) {

				index = three_to_one(i, j, k, &conf);
				fprintf(ascii_output_file, "%d\t%d\t%f\n", i, j, grid_delta[index]);
			}
		}
	}

	fclose(ascii_output_file);

	done(_s_g_a_);

	free(P);
	free(grid_mass);
	free(grid_delta);
	free(input_filename_alias);
	free(algorithm_alias);
	free(input_info_path);

	return 0;
}
