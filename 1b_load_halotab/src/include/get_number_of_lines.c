#include <stdio.h>

size_t get_number_of_lines (FILE *file) {
	size_t num_of_lines = 0;

	while(!feof(file)) {
		char c = fgetc(file);
		if(c == '\n') {
			num_of_lines ++;
		}
	}

	return num_of_lines;
}
