#include <stdlib.h>

#include "./../../global_structs/modes_struct.h"

#include "./allocation_failing_message.h"

void allocate_modes_struct (modes_struct **m, size_t size) {
  if (!(*m = calloc(size, sizeof(struct modes_struct_tag)))) {
    allocation_failing_message("struct modes", size);
    exit(0);
  }
}

