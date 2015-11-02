#include <stdio.h>
#include <stdlib.h>
#include "headers/constants.h"
#include "headers/load_input.h"

int main() {
    load_input_from_file();

    int i;
    for (i = 0; i < NumPart ; i++) {
        fprintf(stdout, "%f \n", P[i].Mass);
    }

    return 0;
}
