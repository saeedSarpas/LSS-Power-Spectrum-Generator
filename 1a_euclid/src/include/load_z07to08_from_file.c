#include <stdio.h>

#include "./../../../global_structs/particle_struct.h"

void load_z07to08_from_file(FILE *file, particle_struct *P) {
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int cntr = 0;

	while ((read = getline(&line, &len, file)) != -1) {
		sscanf(line, "  %lf       %lf       %lf     \n",
			   &P[cntr].Pos[0], &P[cntr].Pos[1], &P[cntr].Pos[2]);

		P[cntr].Pos[0] += 100.0;
		P[cntr].Pos[1] += 100.0;
		P[cntr].Pos[2] += 100.0;
		P[cntr].Mass = 1.0;

		cntr++;
	}
}
