#include "./str_concat.h"

void append_input_infos_name(char *filename, char **returned_path) {
	char *strings[] = {filename, ".info"};
	str_concat(strings, 2, returned_path);
}
