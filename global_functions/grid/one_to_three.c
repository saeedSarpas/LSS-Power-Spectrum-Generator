#include <math.h>

#include "./../../global_structs/config_struct.h"

void one_to_three (int x, int *pos, config_struct *conf) {
  int ret = x % (int)pow(conf->num_of_grids_in_each_axis, 2);

  pos[0] = x / pow(conf->num_of_grids_in_each_axis, 2);
  pos[1] = ret / conf->num_of_grids_in_each_axis;
  pos[2] = ret % conf->num_of_grids_in_each_axis;
}
