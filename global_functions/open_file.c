#include <stdio.h>
#include <stdlib.h>

void open_file(FILE **file, char *path, char *mode) {
	if (!(*file = fopen(path, mode))) {
		printf("[Cannot open file %s]\n", path);
		exit(0);
	}
}
