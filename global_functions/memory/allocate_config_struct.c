#include <stdio.h>
#include <stdlib.h>

#include "allocation_failing_message.h"
#include "./../../global_structs/config_struct.h"

void allocate_config_struct(config_struct ** c) {
	if ( !(*c = calloc(1, sizeof(struct config_struct_tag)))) {
		allocation_failing_message("struct config", 1);
		exit(0);
	}
}
