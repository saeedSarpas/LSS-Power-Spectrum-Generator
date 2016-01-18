#ifndef CONFIG_STRUCT_H
#define CONFIG_STRUCT_H

typedef struct {
	int num_of_input_files;
	char *inputs[3][2];
	char *ngp_alias;
	char *cic_alias;
	char *tsc_alias;
	int num_of_grids_in_each_axis;
	double log_of_k_bins_width;
} config;

#endif
