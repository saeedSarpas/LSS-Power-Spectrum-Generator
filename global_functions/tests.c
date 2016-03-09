#include <cgreen/cgreen.h>

TestSuite *get_mode_in_range_tests();
TestSuite *three_to_one_tests();
TestSuite *load_config_from_tests();
TestSuite *generate_filenames_tests();

int main(int argc, char **argv) {
	TestSuite *suite = create_test_suite();

	add_suite(suite, get_mode_in_range_tests());
	add_suite(suite, three_to_one_tests());
	add_suite(suite, load_config_from_tests());
	add_suite(suite, generate_filenames_tests());

	if (argc > 1) {
		return run_single_test(suite, argv[1], create_text_reporter());
	}

	return run_test_suite(suite, create_text_reporter());
}
