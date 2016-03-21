#include <cgreen/cgreen.h>

TestSuite *find_first_mode_with_modulus_tests();
TestSuite *find_last_mode_with_modulus_tests();
TestSuite *find_first_mode_greater_than_or_equal_to_tests();
TestSuite *sort_modes_tests();
TestSuite *three_to_one_tests();
TestSuite *load_config_from_tests();
TestSuite *generate_filenames_tests();
TestSuite *concat_tests();

int main(int argc, char **argv) {
	TestSuite *suite = create_test_suite();

	add_suite(suite, find_first_mode_with_modulus_tests());
	add_suite(suite, find_last_mode_with_modulus_tests());
	add_suite(suite, find_first_mode_greater_than_or_equal_to_tests());
	add_suite(suite, sort_modes_tests());
	add_suite(suite, three_to_one_tests());
	add_suite(suite, load_config_from_tests());
	add_suite(suite, generate_filenames_tests());
	add_suite(suite, concat_tests());

	if (argc > 1) {
		return run_single_test(suite, argv[1], create_text_reporter());
	}

	return run_test_suite(suite, create_text_reporter());
}
