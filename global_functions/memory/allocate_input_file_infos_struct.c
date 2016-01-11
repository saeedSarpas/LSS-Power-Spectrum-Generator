#include <stdlib.h>

#include "allocation_failing_message.h"
#include "./../../global_structs/input_file_infos.h"

void allocate_input_file_infos_struct(input_file_infos **info) {
	if (!(*info = calloc(1, sizeof(input_file_infos)))) {
		allocation_failing_message("struct input_file_infos", 1);
		exit(0);
	}
}
