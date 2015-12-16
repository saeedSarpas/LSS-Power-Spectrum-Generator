#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <fftw.h>
#include <time.h>

#include "./../configurations.h"
#include "./../global_functions/config_file.h"
#include "./../global_functions/clock.h"
#include "./../global_functions/filenames.h"
#include "./../global_functions/file_handling.h"
#include "./../global_functions/memory_allocation.h"

int main() {

	int mass_mode;
	printf("Mass mode [0 for constant mass, 1 for real mass]: ");
	scanf("%d", &mass_mode);

	char nickname[256];
	if (mass_mode == 0) {
		strcpy(nickname, IN_NICKS[1]);
	} else if (mass_mode == 1) {
		strcpy(nickname, IN_NICKS[2]);
	} else {
		printf("[Wrong mass mode]\n");
		exit(0);
	}

	clock_t _r_h_f_ = start("Reading HaloTab_Run1 file... ");

	double mass_const = 1.0f;

	FILE * in_file;

	char in_path[256] = "./../0_input/";
	strcat(in_path, IN_FILENAME[1]);

	open_file(&in_file, in_path, "r");

	size_t num_line = 0;
	while(!feof(in_file)) {
		char c = fgetc(in_file);
		if(c == '\n') {
			num_line ++;
		}
	}
	rewind(in_file);

	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int num_halo;
	int cntr = 0;

	allocate_struct_particle_data_array(&P, num_line);

	while ((read = getline(&line, &len, in_file)) != -1) {
		sscanf(line, "%lf\t%lf\t%lf\t%lf\t%d\n",
				&P[cntr].Mass, &P[cntr].Pos[0], &P[cntr].Pos[1], &P[cntr].Pos[2], &num_halo);

		if (mass_mode == 0) { P[cntr].Mass = mass_const; }

		cntr++;
	}

	fclose(in_file);

	done(_r_h_f_);

	clock_t _s_o_f_ = start("Saving output file...");

	FILE * out_file;

	char out_path[256] = "./outputs/";
	append_input_filename(nickname, out_path);

	open_file(&out_file, out_path, "wb");

	write_struct_particle_data_to(out_file, P, num_line, out_path);

	done(_s_o_f_);

	clock_t _s_c_f_ = start("Saving configuration file... ");

	allocate_struct_config(&C);

	C->NumPart = num_line;
	C->BoxLength = 1200;

	set_config(*C, nickname);

	done(_s_c_f_);

	free(C);
	free(P);

	return 0;
}
