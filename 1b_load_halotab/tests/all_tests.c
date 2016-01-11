#include <cgreen/cgreen.h>

TestSuite *get_number_of_lines_tests();
TestSuite *load_halotab_from_file_tests();

int main(int argc, char **argv) {
	TestSuite *suite = create_test_suite();

	add_suite(suite, get_number_of_lines_tests());
	add_suite(suite, load_halotab_from_file_tests());

	if (argc > 1) {
		return run_single_test(suite, argv[1], create_text_reporter());
	}

	return run_test_suite(suite, create_text_reporter());
}
