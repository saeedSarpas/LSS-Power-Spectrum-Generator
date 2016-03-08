#include <stdio.h>

#include "./../../global_structs/config_struct.h"

int grid_boundry_checker (int pos, config_struct *conf) {
	if (pos > conf->params.numOfAxisGrids - 1) {
		return pos - conf->params.numOfAxisGrids;
	} else if (pos < 0) {
		return pos + conf->params.numOfAxisGrids;
	} else {
		return pos;
	}
}
