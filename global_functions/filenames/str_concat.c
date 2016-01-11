#include <stdlib.h>
#include <string.h>

void str_concat(char *strings[], int length, char **result) {
	int i;

	for (i = 0; i < length; i++) {
		*result = (char *)realloc(*result, strlen(*result) + strlen(strings[i]) + 1);
		strcat(*result, strings[i]);
	}
}
