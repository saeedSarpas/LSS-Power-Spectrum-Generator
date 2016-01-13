#include "./grid_boundry_checker.h"

#include "./../../global_structs/config_struct.h"

int move_along_grid_axis (int init_pos, int step, config *conf) {
	int new_pos = init_pos + step;
	return grid_boundry_checker(new_pos, conf);
}
