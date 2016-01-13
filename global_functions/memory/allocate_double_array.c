#include <stdlib.h>

#include "./allocation_failing_message.h"

void allocate_double_array (double **d, size_t size) {
  if ( !(*d = calloc(size, sizeof(double)))) {
    allocation_failing_message("double", size);
    exit(0);
  }
}
