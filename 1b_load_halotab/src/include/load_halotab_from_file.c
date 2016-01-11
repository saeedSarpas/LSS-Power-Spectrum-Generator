#include <stdio.h>

#include "./../../../global_structs/particle_data_struct.h"

void load_halotab_from_file(FILE *file, particle_data P[], int mass_mode) {
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int num_halo, cntr = 0;

	while ((read = getline(&line, &len, file)) != -1) {
		sscanf(line, "%lf\t%lf\t%lf\t%lf\t%d\n",
			   &P[cntr].Mass, &P[cntr].Pos[0], &P[cntr].Pos[1], &P[cntr].Pos[2],
			   &num_halo);

		if (mass_mode == 1) { P[cntr].Mass = 1.0; }

		cntr++;
	}
}
