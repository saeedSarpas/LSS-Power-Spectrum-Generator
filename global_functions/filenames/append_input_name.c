#include "./str_concat.h"

void append_input_name(char *filename_alias, char **returned_path) {
	char *strings[] = {filename_alias, ".dat"};
	str_concat(strings, 2, returned_path);
}
