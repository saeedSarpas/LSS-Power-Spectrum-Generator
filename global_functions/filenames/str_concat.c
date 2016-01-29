#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_concat(char *strings[], int length, char **result) {
	int i, strings_length = 0;
	for (i = 0; i < length; i++) {
		strings_length += strlen(strings[i]);
	}

	*result = (char *)realloc(*result, strlen(*result) + strings_length + 1);

	for (i = 0; i < length; i++) {
		strcat(*result, strings[i]);
	}
}
