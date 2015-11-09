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

	char input_type;
	fprintf(stdout, "Input type: [r for random filed, u for uniform field (default)]: ");
	fscanf(stdin, "%c", &input_type);

	if (input_type == 'r') {
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
	} else {
		double i, j, k, mass=100.0;
		int counter;
		for (i = 0.5; i < BOX_SIZE; i += 2.0){
			for (j = 0.5; j < BOX_SIZE; j += 2.0){
				for (k = 0.5; k < BOX_SIZE; k +=2.0){
					fwrite(&i, 1, sizeof(double), input_file_ptr);
					fwrite(&j, 1, sizeof(double), input_file_ptr);
					fwrite(&k, 1, sizeof(double), input_file_ptr);
					for (counter = 0; counter < 4; counter++){
						fwrite(&mass, 1, sizeof(double), input_file_ptr);
					}
				}
			}
		}
	}

	fclose(input_file_ptr);

	return 0;
}
