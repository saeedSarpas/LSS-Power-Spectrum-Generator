#ifndef VECTOR_STRUCT_H
#define VECTOR_STRUCT_H

#include <stddef.h>

typedef struct vector{
	void *elems;
	size_t elem_size;
	size_t log_length;
	size_t alloc_length;
} vector_struct;

#endif
