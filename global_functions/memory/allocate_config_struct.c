#include <stdio.h>
#include <stdlib.h>

#include "allocation_failing_message.h"
#include "./../../global_structs/config_struct.h"

void allocate_config_struct(config ** c) {
	if ( !(*c = calloc(1, sizeof(config)))) {
		allocation_failing_message("struct config", 1);
		exit(0);
	}
}
