#include <stddef.h>

#include "./../../global_structs/vector_struct.h"

void vector_new(vector_struct *, size_t, size_t);
void vector_dispose(vector_struct *);
void vector_push(vector_struct *, void *);
void vector_pop(vector_struct *, void *);
void vector_get_elem(vector_struct *, int, void *);
