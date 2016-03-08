#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void open_file (FILE **file, char *path, char *mode) {
	if (!(*file = fopen(path, mode))) {
		printf("[fopen error: %s (%s)]\n", strerror(errno), path);
		exit(EXIT_FAILURE);
	}
}
