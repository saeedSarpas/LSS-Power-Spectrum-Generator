#include <cgreen/cgreen.h>
#include <string.h>

#include "./append.h"

Describe (append);

#define BASE "base"
#define STRING "string"

static char *result;

BeforeEach (append) {
  result = strdup(BASE);
  result = realloc(result, strlen(result) + strlen(STRING) + 1);
  strcat(result, STRING);
}

Ensure(append, appends_strings_correctly) {
  char *base = strdup(BASE);
  append(base, STRING);

  assert_true(strcmp(base, result) == 0);

  free(base);
}

AfterEach (append) {
  free(result);
}

TestSuite *append_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, append, appends_strings_correctly);
	return suite;
}
