#ifndef CONFIG_STRUCT_H
#define CONFIG_STRUCT_H

typedef struct config_struct_tag{
	int num_of_input_files;
	char *inputs[3][2];
	char *ngp_alias;
	char *cic_alias;
	char *tsc_alias;
	int num_of_grids_in_each_axis;
	int min_num_of_modes_in_bins;
} config_struct;

#endif
