#ifndef CONFIG_STRUCT_H
#define CONFIG_STRUCT_H

typedef struct run_params_struct_tag {
	int file_index;
	int mass_assignment_index;
	int binning_index;
	int num_of_axis_grids;
} run_params_struct;

typedef struct config_struct_tag {
	char *input_files[2][2]; // [filename][alias]
	char *mass_assignment_functions[3][2]; // [algorithm_name][alias]
	char *binning[2][2]; // [binning_algorithm_name][alias]
	run_params_struct run_params;
} config_struct;

#endif
