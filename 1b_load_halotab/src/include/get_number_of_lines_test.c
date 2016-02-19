#include <cgreen/cgreen.h>

#include "./../../../global_functions/io/open_file.h"

#include "./../../src/include/get_number_of_lines.h"

#define TEST_FILE_ADDR "./test.file"
#define TEST_FILE_NUM_OF_LINES 5
#define DOUBLE_NUM 1.234567

Describe(get_number_of_lines);

BeforeEach(get_number_of_lines) {
	FILE * fp;
	open_file(&fp, TEST_FILE_ADDR, "w");
	int i;
	double x = DOUBLE_NUM;
	for (i = 0; i < TEST_FILE_NUM_OF_LINES; i++){
		fprintf(fp, "%lf\t%lf\t%lf\t%lf\t%d\n", x, x, x, x, i + 1);
		x *= i + 1;
	}
	fclose(fp);
}

AfterEach(get_number_of_lines) {
	remove(TEST_FILE_ADDR);
}

Ensure(get_number_of_lines, returns_right_number_of_lines) {
	FILE * fp;
	open_file(&fp, TEST_FILE_ADDR, "r");
	size_t nol = get_number_of_lines(fp);
	assert_that(nol, is_equal_to(5));
}

TestSuite *get_number_of_lines_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, get_number_of_lines, returns_right_number_of_lines);
	return suite;
}
