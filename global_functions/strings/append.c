#include <stdlib.h>
#include <string.h>

void append(char *base, char *string) {
  int length = strlen(base) + strlen(string) + 1;
  base = realloc(base, length);
  strcat(base, string);
}
