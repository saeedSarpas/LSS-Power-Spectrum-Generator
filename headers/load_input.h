struct particle_data {
    float Pos[3];
    float Vel[3];
    float Mass;
} *P;

int allocateMemory(void) {
    fprintf(stdout, "Allocating memory for %d particls... ", numPart);

    if(P = malloc(numPart * sizeof(struct particle_data)) ) {
        fprintf(stdout, "[done]\n");
    } else {
        fprintf(stderr, "failed to allocate memory.\n");
        exit(0);
    }
}

int loadInputFromFile(void) {
    char inputPath[] = "./input/input.dat";

    FILE * inputFile;
    char buf[200];

    sprintf(buf, "%s", inputPath);

    allocateMemory();

    if(inputFile = fopen(buf, "r")) {
        fprintf(stdout, "Reading %s... ", buf);
        fflush(stdout);
    } else {
        fprintf(stderr, "Cannot open file `%s`\n", buf);
        exit(0);
    }

    int n, i;
    for (n = 0; n < numPart; n++) {
        for (i = 0; i < 3; i++) {
            fread(&P[n].Pos[i], sizeof(float), 1, inputFile);
        }

        for (i = 0; i < 3; i++) {
            fread(&P[n].Vel[i], sizeof(float), 1, inputFile);
        }

        fread(&P[n].Mass, sizeof(float), 1, inputFile);
    }

    fclose(inputFile);
    printf("[done]\n");
}
