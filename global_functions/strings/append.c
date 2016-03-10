#include <stdlib.h>
#include <string.h>

char* append(char *base, char *string) {
  char *result = malloc(strlen(base) + strlen(string) + 1);

  strcat(result, base);
  strcat(result, string);

  return result;
}
