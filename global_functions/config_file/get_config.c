#include <stdio.h>
#include <string.h>
#include <libconfig.h>

#include "./my_libconfig.h"
#include "./../../global_structs/config_struct.h"

void get_config (struct config_tag *C) {
	config_t cfg;
	config_setting_t *files, *aliases, *grid_setting, *filename_setting;

	libconfig_init(&cfg);
	libconfig_read_file(&cfg, "./../../configurations.cfg");

	files = libconfig_lookup(&cfg, "input.files");

	const char *file_name, *file_alias;
	int i, l = libconfig_setting_length(files);

	C->num_of_input_files = l;

	for (i = 0; i < l; i++) {
		filename_setting = libconfig_setting_get_elem(files, i);

		file_name = libconfig_setting_lookup_string(filename_setting, "filename");
		C->inputs[i][0] = strdup(file_name);

		file_alias = libconfig_setting_lookup_string(filename_setting, "alias");
		C->inputs[i][1] = strdup(file_alias);
	}

	const char *ngp, *cic, *tsc;
	aliases = libconfig_lookup(&cfg, "output.aliases");

	ngp = libconfig_setting_lookup_string(aliases, "NGP");
	C->ngp_alias = strdup(ngp);

	cic = libconfig_setting_lookup_string(aliases, "CIC");
	C->cic_alias = strdup(cic);

	tsc = libconfig_setting_lookup_string(aliases, "TSC");
	C->tsc_alias = strdup(tsc);

	grid_setting = libconfig_lookup(&cfg, "grid");
	C->num_of_grids_in_each_axis = libconfig_setting_lookup_int(grid_setting,
																"num_of_grids_in_each_axis");

	libconfig_destroy(&cfg);
}
