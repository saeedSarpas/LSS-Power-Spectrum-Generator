#include <math.h>

#include "./../../global_structs/config_struct.h"

void one_to_three (int x, int *pos, config_struct *conf) {
  int ret = x % (int)pow(conf->params.numOfAxisGrids, 2);

  pos[0] = x / pow(conf->params.numOfAxisGrids, 2);
  pos[1] = ret / conf->params.numOfAxisGrids;
  pos[2] = ret % conf->params.numOfAxisGrids;
}
