#include <cgreen/cgreen.h>

TestSuite *reordering_fourier_input_tests();
TestSuite *convert_real_delta_to_complex_tests ();

int main(int argc, char **argv) {
	TestSuite *suite = create_test_suite();

	add_suite(suite, reordering_fourier_input_tests());
	add_suite(suite, convert_real_delta_to_complex_tests());

	if (argc > 1) {
		return run_single_test(suite, argv[1], create_text_reporter());
	}

	return run_test_suite(suite, create_text_reporter());
}
