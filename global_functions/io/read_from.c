#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void read_from (FILE *file, unsigned int nmemb, unsigned int size, void *ptr) {
	if (fread(ptr, size, nmemb, file) != nmemb) {
		printf("[fread error: %s]\n", strerror(errno));
		exit(0);
	}
}
