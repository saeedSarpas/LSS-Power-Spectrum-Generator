#include <cgreen/cgreen.h>

#include "./../../../global_structs/particle_data_struct.h"

#include "./../../../global_functions/io/open_file.h"
#include "./../../../global_functions/memory/allocate.h"

#include "./../../src/include/load_halotab_from_file.h"

#define TEST_FILE_ADDR "./test.file"
#define TEST_FILE_NUM_OF_LINES 5
#define DOUBLE_NUM 1.234567

Describe(load_halotab_from_file);

BeforeEach(load_halotab_from_file) {
	FILE *fp;
	open_file(&fp, TEST_FILE_ADDR, "w");
	int i;
	double x = DOUBLE_NUM;
	for (i = 0; i < TEST_FILE_NUM_OF_LINES; i++){
		fprintf(fp, "%lf\t%lf\t%lf\t%lf\t%d\n", x, x, x, x, i + 1);
		x *= i + 1;
	}
	fclose(fp);
}

AfterEach(load_halotab_from_file) {
	remove(TEST_FILE_ADDR);
}

Ensure(load_halotab_from_file, load_data_correctly) {
	FILE * fp;
	open_file(&fp, TEST_FILE_ADDR, "r");

	particle_data_struct *P;
	allocate((void **)&P, TEST_FILE_NUM_OF_LINES, sizeof(particle_data_struct));

	load_halotab_from_file(fp, P);

	double x = DOUBLE_NUM;
	int i;
	for (i = 0; i < TEST_FILE_NUM_OF_LINES; i++) {

		assert_that(P[i].Mass, is_equal_to(x));
		assert_that(P[i].Pos[0], is_equal_to(x));
		assert_that(P[i].Pos[1], is_equal_to(x));
		assert_that(P[i].Pos[2], is_equal_to(x));

		x *= i + 1;
	}
}

TestSuite *load_halotab_from_file_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, load_halotab_from_file, load_data_correctly);
	return suite;
}
