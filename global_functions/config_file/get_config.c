#include <stdio.h>
#include <string.h>
#include <libconfig.h>

#include "./my_libconfig.h"
#include "./../../global_structs/config_struct.h"

void get_config (config *conf) {

	config_t cfg;
	config_setting_t *files, *aliases, *grid, *bins, *filename_setting;

	libconfig_init(&cfg);
	libconfig_read_file(&cfg, "./../../configurations.cfg");

	files = libconfig_lookup(&cfg, "input.files");

	const char *file_name, *file_alias;
	int i, len = libconfig_setting_length(files);

	conf->num_of_input_files = len;

	for (i = 0; i < len; i++) {
		filename_setting = libconfig_setting_get_elem(files, i);

		file_name = libconfig_setting_lookup_string(filename_setting,
				"filename");
		conf->inputs[i][0] = strdup(file_name);

		file_alias = libconfig_setting_lookup_string(filename_setting,
				"alias");
		conf->inputs[i][1] = strdup(file_alias);
	}

	const char *ngp, *cic, *tsc;
	aliases = libconfig_lookup(&cfg, "output.aliases");

	ngp = libconfig_setting_lookup_string(aliases, "NGP");
	conf->ngp_alias = strdup(ngp);

	cic = libconfig_setting_lookup_string(aliases, "CIC");
	conf->cic_alias = strdup(cic);

	tsc = libconfig_setting_lookup_string(aliases, "TSC");
	conf->tsc_alias = strdup(tsc);

	grid = libconfig_lookup(&cfg, "grid");
	conf->num_of_grids_in_each_axis = libconfig_setting_lookup_int(grid,
			"num_of_grids_in_each_axis");

	bins = libconfig_lookup(&cfg, "bins");
	conf->min_num_of_modes_in_bins = libconfig_setting_lookup_int(bins,
			"min_num_of_modes_in_bins");

	libconfig_destroy(&cfg);
}
