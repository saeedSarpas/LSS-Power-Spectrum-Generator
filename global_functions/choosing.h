void choosing_algorithm(char alg_name[256]) {
	printf("Choose algorithm, [0 for NGP, 1 for CIC, 2 for TSC]: ");

	int algorithm;
	scanf("%d", &algorithm);

	if (algorithm == 1) {
		strcpy(alg_name, CIC_POSTFIX);
	} else if (algorithm == 2) {
		strcpy(alg_name, TSC_POSTFIX);
	} else if (algorithm == 0) {
		strcpy(alg_name, NGP_POSTFIX);
	} else {
		printf("[Wrong algorithm]\n");
	}
}

void choosing_input(char * in_filename) {
	printf("Choose the input file, [0 for random, 1 for HaloTab-CnstMass, 2 for HaloTab]: ");

	in_filename[0] = '\0';

	int in_file;
	scanf("%d", &in_file);

	if (in_file == 2) {
		strcpy(in_filename, IN_NICKS[2]);
	} else if (in_file == 1) {
		strcpy(in_filename, IN_NICKS[1]);
	} else if (in_file == 0) {
		strcpy(in_filename, IN_NICKS[0]);
	} else {
		printf("[Wrong input file]\n");
		exit(0);
	}
}
