#include <cgreen/cgreen.h>
#include <math.h>

#include "./../../../global_structs/config_struct.h"
#include "./../../../global_structs/input_file_info.h"
#include "./../../../global_structs/particle_data_struct.h"

#include "./../../../global_functions/memory/allocate_particle_data_struct.h"
#include "./../../../global_functions/memory/allocate_double_array.h"
#include "./../../../global_functions/grid/three_to_one.h"

#include "./cic.h"

Describe(cic);
BeforeEach(cic) {}
AfterEach(cic) {}

Ensure(cic, returns_right_value_for_a_trivial_case) {
	config_struct conf;
	conf.num_of_grids_in_each_axis = 10;
	int tot_num_of_grids = pow(conf.num_of_grids_in_each_axis, 3);

	input_info_struct info;
	info.num_of_parts = 10;
	info.box_length = 10;

	particle_data_struct *P;
	allocate_particle_data_struct(&P, info.num_of_parts);

	int i;
	for (i = 0; i < info.num_of_parts; i++) {
		P[i].Pos[0] = 4.5;
		P[i].Pos[1] = 4.5;
		P[i].Pos[2] = 4.5;
		P[i].Mass = 1;
	}

	double *grid_mass;
	allocate_double_array(&grid_mass, tot_num_of_grids);

	cic(P, grid_mass, &info, &conf);

	for (i = 0; i < tot_num_of_grids; i++) {
		int index = three_to_one(4, 4, 4, &conf);
		if (i != index)
			assert_that(grid_mass[i], is_equal_to(0));
		else
			assert_that(grid_mass[i], is_equal_to(10));
	}
}

Ensure(cic, calculate_the_share_of_each_cell_right) {
	config_struct conf;
	conf.num_of_grids_in_each_axis = 10;
	int tot_num_of_grids = pow(conf.num_of_grids_in_each_axis, 3);

	input_info_struct info;
	info.num_of_parts = 10;
	info.box_length = 10;

	particle_data_struct *P;
	allocate_particle_data_struct(&P, info.num_of_parts);

	int i;
	for (i = 0; i < info.num_of_parts; i++) {
		P[i].Pos[0] = 4;
		P[i].Pos[1] = 4;
		P[i].Pos[2] = 4;
		P[i].Mass = 1;
	}

	double *grid_mass;
	allocate_double_array(&grid_mass, tot_num_of_grids);

	cic(P, grid_mass, &info, &conf);

	int index, j, k;
	for (i = -2; i <= 1; i++) {
		for (j = -2; j <= 1; j++) {
			for (k = -2; k <= 1; k++) {
				index = three_to_one(4 + i, 4 + j, 4 + k, &conf);
				if (i == -2 || j == -2 || k == -2 || i == 1 || j == 1 || k == 1)
					assert_that(grid_mass[index],is_equal_to(0));
				else
					assert_that(grid_mass[index],is_equal_to(1.25));
			}
		}
	}
}

Ensure(cic, calculate_the_share_of_grid_right_at_borders) {
	config_struct conf;
	conf.num_of_grids_in_each_axis = 10;
	int tot_num_of_grids = pow(conf.num_of_grids_in_each_axis, 3);

	input_info_struct info;
	info.num_of_parts = 10;
	info.box_length = 10;

	particle_data_struct *P;
	allocate_particle_data_struct(&P, info.num_of_parts);

	int i;
	for (i = 0; i < info.num_of_parts; i++) {
		P[i].Pos[0] = 4;
		P[i].Pos[1] = 0;
		P[i].Pos[2] = 4;
		P[i].Mass = 1;
	}

	double *grid_mass;
	allocate_double_array(&grid_mass, tot_num_of_grids);

	cic(P, grid_mass, &info, &conf);

	int index = three_to_one(4, 9, 4, &conf);
	assert_that(grid_mass[index],is_equal_to(1.25));
}

TestSuite *cic_tests() {
	TestSuite *suite = create_test_suite();
	add_test_with_context(suite, cic, returns_right_value_for_a_trivial_case);
	add_test_with_context(suite, cic, calculate_the_share_of_each_cell_right);
	add_test_with_context(suite, cic, calculate_the_share_of_grid_right_at_borders);
	return suite;
}
