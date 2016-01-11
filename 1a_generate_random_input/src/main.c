#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./../../global_functions/clock/start.h"
#include "./../../global_functions/clock/done.h"
#include "./../../global_functions/open_file.h"
#include "./../../global_functions/memory/allocate_particle_data_struct.h"
#include "./../../global_functions/filenames/append_input_name.h"
#include "./../../global_functions/filenames/append_input_infos_name.h"
#include "./../../global_functions/io/write_particle_data_struct_to.h"
#include "./../../global_functions/config_file/get_config.h"
#include "./../../global_functions/info_file/write_input_file_infos_to.h"

#include "./../../global_structs/particle_data_struct.h"
#include "./../../global_structs/input_file_infos.h"
#include "./../../global_structs/config_struct.h"

int NUM_OF_PARTS = 10000000;
double BOX_LENGTH = 256.0;

double random_double(int max) {
	return (((double)rand() / (double)(RAND_MAX)) * max);
}

int main() {

	clock_t _g_r_i_ = start("Generating random input... ");

particle_data *P;
	allocate_particle_data_struct(&P, NUM_OF_PARTS);

int i, n;
	for (n = 0; n < NUM_OF_PARTS; n++) {
		for (i = 0; i < 3; i++) {
			P[n].Pos[i] = random_double(BOX_LENGTH);
		}
		P[n].Mass = 10.0;
	}

	done(_g_r_i_);


	clock_t _s_o_f_ = start("Saving output file...");

	FILE * out_file;

	config conf;
	get_config(&conf);

	char *out_path = strdup("./../../0_structured_input/");
	append_input_name(conf.inputs[0][1], &out_path);

	open_file(&out_file, out_path, "wb");

	write_particle_data_struct_to(out_file, P, NUM_OF_PARTS, out_path);

	fclose(out_file);

	done(_s_o_f_);


	clock_t _s_c_f_ = start("Saving configuration file... ");

	input_file_infos infos;
	infos.num_of_parts = NUM_OF_PARTS;
	infos.box_length = BOX_LENGTH;

	char *info_path = strdup("./../../0_structured_input/");
	append_input_infos_name(conf.inputs[0][1], &info_path);

	FILE *info_file;
	open_file(&info_file, info_path, "w+");

	write_input_file_infos_to(info_file, &infos);

	fclose(info_file);

	done(_s_c_f_);

	free(P);
	return 0;
}
