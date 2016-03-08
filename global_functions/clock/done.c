#include <stdio.h>
#include <time.h>

void done (clock_t begin) {

	clock_t end = clock();
	double duration = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("[done in %f sec]\n", duration);
	fflush(stdout);
}
