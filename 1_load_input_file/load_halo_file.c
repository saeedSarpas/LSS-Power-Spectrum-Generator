#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./../configurations.h"
#include "./../global_functions/config_file.h"
#include "./../global_functions/clock.h"
#include "./../global_functions/filenames.h"

int main() {
	int i, n;

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

	char read_halo_msg[256] = "Reading HaloTab_Run1 file... ";
	clock_t begin = start(read_halo_msg);

	double mass_const = 1.0f;

	FILE * in_file;

	char in_path[256] = "./../0_input/";
	strcat(in_path, IN_FILENAME[1]);

	if (!(in_file = fopen(in_path, "r"))) {
		printf("[Cannot open stream %s]\n", in_path);
		exit(0);
	}

	int num_line = 0;
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

	if (!(P = malloc(num_line * sizeof(struct particle_data)))) {
		printf("[Failed to allocate memory.]\n");
		exit(0);
	}

	while ((read = getline(&line, &len, in_file)) != -1) {
		sscanf(line, "%lf\t%lf\t%lf\t%lf\t%d\n",
				&P[cntr].Mass, &P[cntr].Pos[0], &P[cntr].Pos[1], &P[cntr].Pos[2], &num_halo);

		if (mass_mode == 0) { P[cntr].Mass = mass_const; }

		cntr++;
	}

	fclose(in_file);

	done(begin);

	char save_msg[256] = "Saving output file...";
	begin = start(save_msg);

	FILE * out_file;

	char out_path[256] = "./outputs/";
	append_input_filename(nickname, out_path);

	if (!(out_file = fopen(out_path, "wb"))) {
		printf("[Cannot open file %s]\n", out_path);
		exit(0);
	}

	for (n = 0; n < num_line; n++) {
		for (i = 0; i < 3; i++) {
			fwrite(&P[n].Pos[i], 1, sizeof(double), out_file);
		}
		fwrite(&P[n].Mass, 1, sizeof(double), out_file);
	}

	done(begin);

	char save_conf[256] = "Creating configuration file... ";
	begin = start(save_conf);

	if (!(C = malloc(sizeof(struct config))) ) {
		fprintf(stderr, "[Failed to allocate memory.]\n");
		exit(0);
	}

	C->NumPart = num_line;
	C->BoxLength = 1200;

	set_config(*C, nickname);

	done(begin);

	free(C);
	free(P);
	return 0;
}
