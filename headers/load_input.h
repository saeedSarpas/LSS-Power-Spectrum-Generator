struct particle_data {
    float Pos[3];
    float Vel[3];
    float Mass;
} *P;

int allocate_memory(void) {
    printf("allocating memory...");

    if(P = malloc(NumPart * sizeof(struct particle_data)) ) {
        fprintf(stderr, "memory has allocated for %d particle_data\n", NumPart);
    } else {
        fprintf(stderr, "failed to allocate memory.\n");
        exit(0);
    }

    printf("[done]\n");
}

int load_input_from_file(void) {
    char inputPath[] = "input/input.dat";

    FILE * inputFile;
    char buf[200];

    sprintf(buf, "%s", inputPath);

    if(inputFile = fopen(buf, "r")) {
        fprintf(stdout, "reading %s ... ", buf);
        fflush(stdout);
    } else {
        fprintf(stderr, "can't open file `%s`\n", buf);
        exit(0);
    }

    allocate_memory();

    int n, i;
    for (n = 0; n < NumPart; n++) {
        for (i = 0; i < 3; i++) {
            fread(&P[n].Pos[i], sizeof(float), 1, inputFile);
        }

        for (i = 0; i < 3; i++) {
            fread(&P[n].Vel[i], sizeof(float), 1, inputFile);
        }

        fread(&P[n].Mass, sizeof(float), 1, inputFile);
    }

    fclose(inputFile);
    printf("[done].\n");
}
