struct particle_data {
	double Pos[3];
	double Vel[3];
	double Mass;
} *P;

int allocateMemory(void) {
	if( !(P = malloc(NUM_OF_PART * sizeof(struct particle_data))) ) {
		fprintf(stderr, "[Failed to allocate memory.]\n");
		exit(0);
	}
}

int loadInputFromFile() {
	char inputPath[] = "./input/input.dat";

	FILE * inputFile;
	char buf[200];

	sprintf(buf, "%s", inputPath);

	allocateMemory();

	if(!(inputFile = fopen(buf, "r"))) {
		fprintf(stderr, "[Cannot open file `%s`]\n", buf);
		exit(0);
	}

	int n, i;
	for (n = 0; n < NUM_OF_PART; n++) {
		for (i = 0; i < 3; i++) {
			fread(&P[n].Pos[i], sizeof(double), 1, inputFile);
		}

		for (i = 0; i < 3; i++) {
			fread(&P[n].Vel[i], sizeof(double), 1, inputFile);
		}

		fread(&P[n].Mass, sizeof(double), 1, inputFile);
	}

	fclose(inputFile);
}
