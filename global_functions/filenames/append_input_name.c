#include "./str_concat.h"

void append_input_name(char *filename, char **returned_path) {
	char *strings[] = {filename, ".dat"};
	str_concat(strings, 2, returned_path);
}
