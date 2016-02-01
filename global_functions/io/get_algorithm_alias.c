#include <stdio.h>
#include <string.h>

#include "./../../global_structs/config_struct.h"

char* get_algorithm_alias(config_struct *C) {
	printf("Choose algorithm, [0 for NGP, 1 for CIC, 2 for TSC]: ");

	int algorithm;
	scanf("%d", &algorithm);

	char * algorithm_alias;
	if (algorithm == 1) {
		algorithm_alias = strdup(C->cic_alias);
	} else if (algorithm == 2) {
		algorithm_alias = strdup(C->tsc_alias);
	} else if (algorithm == 0) {
		algorithm_alias = strdup(C->ngp_alias);
	} else {
		printf("[Wrong algorithm]\n");
	}

	return algorithm_alias;
}
