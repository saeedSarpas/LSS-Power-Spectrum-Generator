#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void allocate (void **pptr, unsigned int nmemb, unsigned int size) {
	*pptr = calloc(nmemb, size);
	if (*pptr == NULL) {
		printf("[calloc error: %s]\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
