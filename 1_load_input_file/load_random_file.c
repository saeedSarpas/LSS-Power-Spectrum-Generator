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

int NUM_PART = 10000000;
int BOX_LENGTH = 256;

double random_double(int max) {
	return (((double)rand() / (double)(RAND_MAX)) * max);
}

int main() {
	int i, n;

	clock_t _g_r_i_ = start("Generating random input... ");

	double mass_const = 10.0;

	allocate_struct_particle_data_array(&P, NUM_PART);

	for (n = 0; n < NUM_PART; n++) {
		for (i = 0; i < 3; i++) {
			P[n].Pos[i] = random_double(BOX_LENGTH);
		}
		P[n].Mass = mass_const;
	}

	FILE * out_file;

	char out_path[256] = "./outputs/";
	append_input_filename(IN_NICKS[0], out_path);

	open_file(&out_file, out_path, "wb");

	write_struct_particle_data_to(out_file, P, NUM_PART, out_path);

	fclose(out_file);

	done(_g_r_i_);

	clock_t _s_c_f_ = start("Saving configuration file... ");

	allocate_struct_config(&C);

	C->NumPart = NUM_PART;
	C->BoxLength = BOX_LENGTH;

	set_config(*C, IN_NICKS[0]);

	done(_s_c_f_);

	free(C);
	free(P);
	return 0;
}
