#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers/constants.h"
#include "headers/load_input.h"
#include "headers/griding.h"

int main() {
    loadInputFromFile(); // From load_input header file

    float * mass_grid_ptr;
    mass_grid_ptr = calloc(pow(numGrid, 3), sizeof(float));

    char algorithm;
    fprintf(stdout, "Choose griding algorithm, [n for NGP (defualt), c for CIC]: ");
    fscanf(stdin, "%c", &algorithm);

    int n;
    if (algorithm == 'c') {
      fprintf(stdout, "Griding using cloud in cell (CIC) algorithm... ");
      for (n = 0; n < numPart; n++) {
        CIC(P[n], mass_grid_ptr);
      }
      fprintf(stdout, "[done]\n");
    } else {
      fprintf(stdout, "Griding using nearest grid points (NGP) algorithm... ");
      for (n = 0; n < numPart; n++) {
        NGP(P[n], mass_grid_ptr);
      }
      fprintf(stdout, "[done]\n");
    }

    free(mass_grid_ptr);
    return 0;
}
