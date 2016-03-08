#include "./grid_boundry_checker.h"

#include "./../../global_structs/config_struct.h"

int move_along_grid_axis (int init_pos, int step, config_struct *conf) {
	return grid_boundry_checker(init_pos + step, conf);
}
