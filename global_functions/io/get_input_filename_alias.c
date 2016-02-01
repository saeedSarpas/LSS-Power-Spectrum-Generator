#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./../../global_structs/config_struct.h"

char* get_input_filename_alias(config_struct *C) {
	printf("Choose the input file, [");
	int i;
	for (i = 0; i < C->num_of_input_files; i++) {
		printf("%d for %s",i , C->inputs[i][1]);
		if (i != C->num_of_input_files - 1) {
			printf(", ");
		}
	}
	printf("]:");

	char *input_filename;

	int index;
	scanf("%d", &index);

	if (index >= C->num_of_input_files || index < 0) {
		printf("[Wrong input file]\n");
		exit(0);
	} else {
		input_filename = strdup(C->inputs[index][1]);
	}

	return input_filename;
}
