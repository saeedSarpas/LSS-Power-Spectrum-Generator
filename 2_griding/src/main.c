#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/particle_data_struct.h"
#include "./../../global_structs/input_file_info.h"

#include "./../../global_functions/config_file/get_config.h"
#include "./../../global_functions/io/open_file.h"
#include "./../../global_functions/io/write_to.h"
#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/memory/allocate.h"
#include "./../../global_functions/filenames/append_input_info_name.h"
#include "./../../global_functions/filenames/append_input_name.h"
#include "./../../global_functions/filenames/append_density_contrast_filename.h"
#include "./../../global_functions/info_file/read_info_from.h"
#include "./../../global_functions/grid/three_to_one.h"

#include "./include/load_input.h"
#include "./include/cic.h"
#include "./include/tsc.h"
#include "./include/ngp.h"
#include "./include/density_contrast.h"

int main() {
	config_struct conf;
	get_config(&conf, "./../../configurations.cfg");

	char *filename_alias;
	filename_alias = conf.input_files[conf.run_params.file_index][1];

	char *algorithm_alias;
	algorithm_alias =
		conf.mass_assignment_functions[conf.run_params.mass_assignment_index][1];

	input_info_struct info;
	char *info_path = strdup("./../../0_structured_input/");
	append_input_info_name(filename_alias, &info_path);
	read_info_from(info_path, &info);

	clock_t _r_g_i_ = start("Reading griding input... ");

	particle_data_struct *P;
	allocate((void **)&P, info.num_of_parts, sizeof(particle_data_struct));

	char *input_path = strdup("./../../0_structured_input/");
	append_input_name(filename_alias, &input_path);

	load_input(P, input_path, &info);

	done(_r_g_i_);


	double *grid_mass;
	size_t tot_num_of_grids = pow(conf.run_params.num_of_axis_grids, 3);
	allocate((void **)&grid_mass, tot_num_of_grids, sizeof(double));

	if (strcmp(algorithm_alias, "cic") == 0) {
		char alg[256] = "Griding using cloud in cell (CIC) algorithm... ";
		clock_t begin = start(alg);
		cic(P, grid_mass, &info, &conf);
		done(begin);
	} else if (strcmp(algorithm_alias, "tsc") == 0) {
		char alg[256] = "Griding using triangular shaped cloud (TSC) algorithm... ";
		clock_t begin = start(alg);
		tsc(P, grid_mass, &info, &conf);
		done(begin);
	} else if (strcmp(algorithm_alias, "ngp") == 0) {
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
	allocate((void **)&grid_delta, tot_num_of_grids, sizeof(double));

	density_contrast(grid_mass, &info, &conf, grid_delta);

	done(_c_d_c_);

	clock_t _s_g_b_ = start("Saving griding (binary)... ");

	FILE *output_file;
	char *output_path = strdup("./../output/");
	append_density_contrast_filename(filename_alias, algorithm_alias,
									 &info, &conf, &output_path);
	open_file(&output_file, output_path, "wb");

	write_to(output_file, grid_delta, tot_num_of_grids, sizeof(double));

	fclose(output_file);

	done(_s_g_b_);

	clock_t _s_g_a_ = start("Saving griding (ascii)... ");

	FILE * ascii_output_file;
	char *ascii_output_path = strdup("./../output/ascii-");
	append_density_contrast_filename(filename_alias, algorithm_alias, &info,
									 &conf, &ascii_output_path);
	open_file(&ascii_output_file, ascii_output_path, "w");

	int i, j, k, index;
	for (i = 0; i < conf.run_params.num_of_axis_grids; i++) {
		for (j = 0; j < conf.run_params.num_of_axis_grids; j++) {
			for (k = (conf.run_params.num_of_axis_grids / 2);
				 k < (conf.run_params.num_of_axis_grids / 2) + 1; k++) {

				index = three_to_one(i, j, k, &conf);
				fprintf(ascii_output_file, "%d\t%d\t%f\n", i, j, grid_delta[index]);
			}
		}
	}

	fclose(ascii_output_file);

	done(_s_g_a_);

	free(P);
	free(grid_delta);
	free(filename_alias);
	free(algorithm_alias);
	free(info_path);
	free(input_path);
	free(output_path);
	free(ascii_output_path);
	return 0;
}
