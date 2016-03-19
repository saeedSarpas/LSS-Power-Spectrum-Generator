#include <cgreen/cgreen.h>
#include <math.h>

#include "./../../global_structs/config_struct.h"
#include "./../../global_structs/modes_struct.h"

#include "./../memory/allocate.h"
#include "./../grid/three_to_one.h"

#include "./sort_modes.h"

Describe(sort_modes);

#define NUM_OF_GRIDS (4)
#define MAX_VALUE (100000)

static config_struct conf;
static modes_struct modes_array[NUM_OF_GRIDS * NUM_OF_GRIDS * NUM_OF_GRIDS];

BeforeEach(sort_modes) {
	conf.params.numOfAxisGrids = NUM_OF_GRIDS;

  int i, array_length = pow(NUM_OF_GRIDS, 3);
  double random_number;

  for (i = 0; i < array_length; i++) {
      random_number = (double)rand()/(double)RAND_MAX * MAX_VALUE;
      modes_array[i].modulus = random_number;
  }
}

AfterEach(sort_modes) {}

Ensure(sort_modes, sorts_the_array_in_an_ascending_order) {
	sort_modes(modes_array, &conf);

	int i, tot_num_of_grids = pow(conf.params.numOfAxisGrids, 3);

	for (i = 0; i < tot_num_of_grids - 1; i++)
		assert_true(modes_array[i].modulus <= modes_array[i+1].modulus);
}

TestSuite *sort_modes_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, sort_modes,
                        sorts_the_array_in_an_ascending_order);
	return suite;
}
