#include <stdio.h>
#include <stdlib.h>
#include "./../include/constants.h"

struct particle_data {
	double Pos[3];
	double Vel[3];
	double Mass;
} *P;

void random_double_num_ptr(int max, double * random_num) {
	*random_num = ((double)rand() / (double)(RAND_MAX)) * max;
}

int main() {
	FILE *input_file_ptr;
	input_file_ptr = fopen("./input.dat", "wb");

	if (!input_file_ptr) {
		printf("Unable to open file!\n");
		return 1;
	}

	double * random_num;
	random_num = malloc(sizeof(double));

	int i;
	for (i = 0; i < NUM_OF_PART; i++) {
		int j;
		for (j = 0; j < 7; j++) {
			random_double_num_ptr(BOX_SIZE, random_num);
			fwrite(random_num, 1, sizeof(double), input_file_ptr);
		}
	}

	fclose(input_file_ptr);

	return 0;
}
