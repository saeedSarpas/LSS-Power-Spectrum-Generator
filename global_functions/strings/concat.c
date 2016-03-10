#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "./../memory/allocate.h"

char* concat (int count, ...) {

  if (count < 2) {
    printf("[You should at least provide two argumemts for concat function]\n");
    exit(EXIT_FAILURE);
  }

  va_list list;
  char **strings = malloc(count * sizeof(char *));

  va_start(list, count);

  int i, length = 0;
	for (i = 0; i < count; i++) {
    strings[i] = va_arg(list, char *);
		length += strlen(strings[i]);
  }

  char *result;
  allocate((void **)&result, length + 1, sizeof(char));

	for (i = 0; i < count; i++)
		strcat(result, strings[i]);

  free(strings);
  va_end(list);

  return result;
}
