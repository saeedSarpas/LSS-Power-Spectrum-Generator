#include <cgreen/cgreen.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/input_file_info.h"
#include "./../../../global_structs/particle_data_struct.h"

#include "./../../../global_functions/memory/allocate.h"
#include "./../../../global_functions/grid/three_to_one.h"

#include "./cic.h"

Describe(cic);

#define NUM_OF_GRIDS 10
#define NUM_OF_PARTS 10
#define BOX_LENGTH 10

static config_struct conf;
static int tot_num_of_grids;
static input_info_struct info;
static particle_data_struct *P;
static double *grid_mass;
static void fill_P (double, double, double, double);

BeforeEach(cic) {
	conf.run_params.num_of_axis_grids = 10;
	tot_num_of_grids = pow(conf.run_params.num_of_axis_grids, 3);

	info.num_of_parts = NUM_OF_PARTS;
	info.box_length = BOX_LENGTH;

	allocate((void **)&P, info.num_of_parts, sizeof(particle_data_struct));

	allocate((void **)&grid_mass, tot_num_of_grids, sizeof(double));
}

AfterEach(cic) {
	free(P);
	free(grid_mass);
}

Ensure(cic, returns_right_value_for_a_trivial_case) {
	fill_P(4.5, 4.5, 4.5, 1);
	cic(P, grid_mass, &info, &conf);

	int i, index = three_to_one(4, 4, 4, &conf);
	for (i = 0; i < tot_num_of_grids; i++) {
		if (i != index)
			assert_that(grid_mass[i], is_equal_to(0));
		else
			assert_that(grid_mass[i], is_equal_to(1 * info.num_of_parts));
	}
}

Ensure(cic, calculate_the_share_of_each_cell_right) {
	fill_P(4.0, 4.0, 4.0, 1);
	cic(P, grid_mass, &info, &conf);

	int index, i, j, k;
	for (i = -2; i <= 1; i++) {
		for (j = -2; j <= 1; j++) {
			for (k = -2; k <= 1; k++) {
				index = three_to_one(4 + i, 4 + j, 4 + k, &conf);
				if (i == -2 || j == -2 || k == -2 || i == 1 || j == 1 || k == 1)
					assert_that(grid_mass[index], is_equal_to(0));
				else
					assert_that(grid_mass[index],
								is_equal_to(1 * info.num_of_parts / 8));
			}
		}
	}
}

Ensure(cic, calculate_the_share_of_grid_right_at_borders) {
	fill_P(4, 0, 4, 1);

	cic(P, grid_mass, &info, &conf);

	int index = three_to_one(4, 9, 4, &conf);
	assert_that(grid_mass[index],is_equal_to(1.25));
}

TestSuite *cic_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, cic, returns_right_value_for_a_trivial_case);
	add_test_with_context(suite, cic, calculate_the_share_of_each_cell_right);
	add_test_with_context(suite, cic,
						 calculate_the_share_of_grid_right_at_borders);
	return suite;
}

void fill_P (double x, double y, double z, double mass) {
	int i;
	for (i = 0; i < info.num_of_parts; i++) {
		P[i].Pos[0] = x;
		P[i].Pos[1] = y;
		P[i].Pos[2] = z;
		P[i].Mass = mass;
	}
}
