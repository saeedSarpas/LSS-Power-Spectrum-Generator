#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/memory/allocate.h"
#include "./../../global_functions/filenames/append_input_name.h"
#include "./../../global_functions/filenames/append_input_info_name.h"
#include "./../../global_functions/io/write_to.h"
#include "./../../global_functions/io/open_file.h"
#include "./../../global_functions/config_file/get_config.h"
#include "./../../global_functions/info_file/write_info_to.h"

#include "./../../global_structs/particle_data_struct.h"
#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/input_file_info.h"

#include "./include/get_number_of_lines.h"
#include "./include/load_halotab_from_file.h"

int main() {

	clock_t _r_h_f_ = start("Reading HaloTab_Run1 file... ");

	FILE *input_file;
	char *input_path = strdup("./../input/HaloTab_Run1.0.1_FOF.txt");

	open_file(&input_file, input_path, "r");
	size_t num_of_lines = get_number_of_lines(input_file);
	rewind(input_file);

	particle_data_struct *P;
	allocate((void **)&P, num_of_lines, sizeof(particle_data_struct));
	load_halotab_from_file(input_file, P);

	fclose(input_file);

	done(_r_h_f_);


	clock_t _s_o_f_ = start("Saving output file...");

	FILE *output_file;

	config_struct conf;
	get_config(&conf, "./../../configurations.cfg");

	char *output_path = strdup("./../../0_structured_input/");
	append_input_name(conf.input_files[0][1], &output_path);

	open_file(&output_file, output_path, "wb");

	write_to(output_file, P, num_of_lines, sizeof(particle_data_struct));

	fclose(output_file);

	done(_s_o_f_);


	clock_t _s_c_f_ = start("Saving configuration file... ");

	input_info_struct info;
	info.num_of_parts = num_of_lines;
	info.box_length = 1200.0;

	char *info_path = strdup("./../../0_structured_input/");
	append_input_info_name(conf.input_files[0][1], &info_path);

	FILE *info_file;
	open_file(&info_file, info_path, "w+");

	write_info_to(info_file, &info);

	fclose(info_file);

	done(_s_c_f_);

	free(P);
	free(input_path);
	free(output_path);
	free(info_path);
	return 0;
}
