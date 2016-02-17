#include <math.h>

#include "./../../global_structs/config_struct.h"

void one_to_three (int x, int *pos, config_struct *conf) {
  int ret = x % (int)pow(conf->run_params.num_of_axis_grids, 2);

  pos[0] = x / pow(conf->run_params.num_of_axis_grids, 2);
  pos[1] = ret / conf->run_params.num_of_axis_grids;
  pos[2] = ret % conf->run_params.num_of_axis_grids;
}
