#include <stdlib.h>

#include "allocation_failing_message.h"
#include "./../../global_structs/input_file_info.h"

void allocate_input_file_info_struct(input_info_struct **info) {
	if (!(*info = calloc(1, sizeof(struct input_info_struct_tag)))) {
		allocation_failing_message("struct input_file_info", 1);
		exit(0);
	}
}
