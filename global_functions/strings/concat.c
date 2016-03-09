#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concat (char *strings[], int length) {
  char *result = strdup("");

	int i, strings_length = 0;
	for (i = 0; i < length; i++)
		strings_length += strlen(strings[i]);

	result = realloc(result, strings_length + 1);

	for (i = 0; i < length; i++)
		strcat(result, strings[i]);

  return result;
}
