#include <stdio.h>
#include <string.h>
#include <time.h>

clock_t start (char *message) {

	printf(message, strlen(message));
	fflush(stdout);

	clock_t start = clock();

	return start;
}
