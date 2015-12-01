#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./../configurations.h"
#include "./../global_functions/config_file.h"
#include "./../global_functions/clock.h"
#include "./../global_functions/filenames.h"

int NUM_PART = 10000000;
int BOX_LENGTH = 256;

double random_double(int max) {
	return (((double)rand() / (double)(RAND_MAX)) * max);
}

int main() {
	int i, n;

	char ran_out_msg[256] = "Generating random input... ";
	clock_t begin = start(ran_out_msg);

	double * random_num, mass_const = 10.0f;

	if (!(P = malloc(NUM_PART * sizeof(struct particle_data))) ) {
		fprintf(stderr, "[Failed to allocate memory.]\n");
		exit(0);
	}

	for (n = 0; n < NUM_PART; n++) {
		for (i = 0; i < 3; i++) {
			P[n].Pos[i] = random_double(BOX_LENGTH);
		}
		P[n].Mass = mass_const;
	}

	FILE * out_file;

	char out_path[256] = "./outputs/";
	append_input_filename(IN_NICKS[0], out_path);

	if (!(out_file = fopen(out_path, "wb"))) {
		printf("[Cannot open file %s]\n", out_path);
		exit(0);
	}

	for (n = 0; n < NUM_PART; n++) {
		for (i = 0; i < 3; i++) {
			fwrite(&P[n].Pos[i], 1, sizeof(double), out_file);
		}
		fwrite(&P[n].Mass, 1, sizeof(double), out_file);
	}

	fclose(out_file);
	done(begin);

	char save_conf[256] = "Saving configuration file... ";
	begin = start(save_conf);

	if (!(C = malloc(sizeof(struct config))) ) {
		fprintf(stderr, "[Failed to allocate memory.]\n");
		exit(0);
	}

	C->NumPart = NUM_PART;
	C->BoxLength = BOX_LENGTH;

	set_config(*C, IN_NICKS[0]);

	done(begin);

	free(C);
	free(P);
	return 0;
}
