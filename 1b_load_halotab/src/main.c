#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/open_file.h"
#include "./../../global_functions/memory/allocate_particle_data_struct.h"
#include "./../../global_functions/memory/allocate_config_struct.h"
#include "./../../global_functions/memory/allocate_input_file_infos_struct.h"
#include "./../../global_functions/filenames/append_input_name.h"
#include "./../../global_functions/filenames/append_input_infos_name.h"
#include "./../../global_functions/io/write_particle_data_struct_to.h"
#include "./../../global_functions/config_file/get_config.h"
#include "./../../global_functions/info_file/write_input_file_infos_to.h"

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/input_file_infos.h"

#include "./include/get_number_of_lines.h"
#include "./include/load_halotab_from_file.h"

int main() {

	int mass_mode;
	printf("Mass mode [1 for constant mass, 2 for their real mass]: ");
	scanf("%d", &mass_mode);

	clock_t _r_h_f_ = start("Reading HaloTab_Run1 file... ");

	FILE *input_file;
	char *input_path = strdup("./../input/HaloTab_Run1.0.1_FOF.txt");

	open_file(&input_file, input_path, "r");
	size_t num_of_lines = get_number_of_lines(input_file);
	rewind(input_file);

	particle_data *P;
	allocate_particle_data_struct(&P, num_of_lines);
	load_halotab_from_file(input_file, P, mass_mode);

	fclose(input_file);

	done(_r_h_f_);


	clock_t _s_o_f_ = start("Saving output file...");

	FILE *out_file;

	config conf;
	get_config(&conf);

	char *output_path = strdup("./../../0_structured_input/");
	append_input_name(conf.inputs[mass_mode][1], &output_path);

	open_file(&out_file, output_path, "wb");

	write_particle_data_struct_to(out_file, P, num_of_lines, output_path);

	fclose(out_file);

	done(_s_o_f_);


	clock_t _s_c_f_ = start("Saving configuration file... ");

	input_file_infos infos;
	infos.num_of_parts = num_of_lines;
	infos.box_length = 1200.0;

	char *info_path = strdup("./../../0_structured_input/");
	append_input_infos_name(conf.inputs[mass_mode][1], &info_path);

	FILE *info_file;
	open_file(&info_file, info_path, "w+");

	write_input_file_infos_to(info_file, &infos);

	fclose(info_file);

	done(_s_c_f_);

	free(P);

	return 0;
}
