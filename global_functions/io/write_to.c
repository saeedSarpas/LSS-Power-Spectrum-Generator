#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void write_to(FILE *file, void *ptr, unsigned int nmemb, unsigned int size) {
	if (fwrite(ptr, size, nmemb, file) != nmemb) {
		printf("[fwrite error: %s]\n", strerror(errno));
		exit(0);
	}
}
