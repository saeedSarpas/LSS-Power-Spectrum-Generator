#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers/constants.h"
#include "headers/load_input.h"
#include "headers/griding.h"

int main() {
	loadInputFromFile(); // From load_input header file

	float * grid_mass_ptr;
	grid_mass_ptr = calloc(pow(numGrid, 3), sizeof(float));

	char algorithm;
	fprintf(stdout, "Choose griding algorithm, [n for NGP (defualt), c for CIC, t for TSC]: ");
	fscanf(stdin, "%c", &algorithm);

	int n;
	if (algorithm == 'c') {
		fprintf(stdout, "Griding using cloud in cell (CIC) algorithm... ");
		for (n = 0; n < numPart; n++) {
			CIC(P[n], grid_mass_ptr);
		}
		fprintf(stdout, "[done]\n");
	} else if (algorithm == 't') {
		fprintf(stdout, "Griding using triangular shaped cloud (TSC) algorithm... ");
		for (n = 0; n < numPart; n++) {
			TSC(P[n], grid_mass_ptr);
		}
		fprintf(stdout, "[done]\n");
	} else {
		fprintf(stdout, "Griding using nearest grid points (NGP) algorithm... ");
		for (n = 0; n < numPart; n++) {
			NGP(P[n], grid_mass_ptr);
		}
		fprintf(stdout, "[done]\n");
	}



	free(grid_mass_ptr);
	return 0;
}
