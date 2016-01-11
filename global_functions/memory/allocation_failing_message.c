#include <stdio.h>
#include <stdlib.h>

void allocation_failing_message (char * t_name, size_t size) {
	printf("[Faild to allocate memory for an array of %s with length %d]\n",
		   t_name, (int)size);
}
