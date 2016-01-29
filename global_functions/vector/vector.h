#include <stddef.h>

#include "./../../global_structs/vector_struct.h"

void vector_new(vector *, size_t, size_t);
void vector_dispose(vector *);
void vector_push(vector *, void *);
void vector_pop(vector *, void *);
void vector_get_elem(vector *, int, void *);
