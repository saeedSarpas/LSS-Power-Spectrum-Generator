#include <stdio.h>
#include <stdlib.h>
#include "./../headers/constants.h"

struct particle_data {
	float Pos[3];
	float Vel[3];
	float Mass;
} *P;

void random_float_num_ptr(int max, float * random_num) {
	*random_num = ((float)rand() / (float)(RAND_MAX)) * max;
}

int main() {
	FILE *input_file_ptr;
	input_file_ptr = fopen("./input.dat", "wb");

	if (!input_file_ptr) {
		printf("Unable to open file!\n");
		return 1;
	}

	float * random_num;
	random_num = malloc(sizeof(float));

	int i;
	for (i = 0; i < numPart; i++) {
		int j;
		for (j = 0; j < 7; j++) {
			random_float_num_ptr(boxSize, random_num);
			fwrite(random_num, 1, sizeof(float), input_file_ptr);
		}
	}

	fclose(input_file_ptr);

	return 0;
}
