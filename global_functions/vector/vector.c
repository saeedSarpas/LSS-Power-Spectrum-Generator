#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./../../global_structs/vector_struct.h"
#include "./../../global_structs/bins_struct.h"

void vector_new(vector_struct *v, size_t elem_size, size_t alloc_length) {
	v->elem_size = elem_size;
	v->log_length = 0;
	v->alloc_length = alloc_length;
	v->elems = malloc(elem_size * alloc_length);
	if (v->elems == NULL) {
		printf("[Unable to allocate space for the vector]\n");
		exit(EXIT_FAILURE);
	}
}

void vector_dispose(vector_struct *v) {
	free(v->elems);
}

static void vector_grow (vector_struct *v) {
	v->alloc_length *= 2;
	v->elems = realloc(v->elems, v->alloc_length * v->elem_size);
	if (v->elems == NULL) {
		printf("[Unable to reallocate the vector]\n");
		exit(EXIT_FAILURE);
	}
}

void vector_push(vector_struct *v, void *elem_addr) {
	if (v->log_length == v->alloc_length) {
		vector_grow(v);
	}
	void *target = (char *) v->elems + v->log_length * v->elem_size;
	memcpy(target, elem_addr, v->elem_size);
	v->log_length++;
}

void vector_pop(vector_struct *v, void *elem_addr) {
	v->log_length--;
	void *source = (char *) v->elems + v->log_length * v->elem_size;
	memcpy(elem_addr, source, v->elem_size);
}

void vector_get_elem(vector_struct *v, int elem, void *elem_addr) {
	void *source = (char *) v->elems + elem * v->elem_size;
	memcpy(elem_addr, source, v->elem_size);
}
