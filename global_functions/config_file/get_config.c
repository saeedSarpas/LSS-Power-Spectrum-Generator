#include <stdio.h>
#include <string.h>
#include <libconfig.h>

#include "./my_libconfig.h"
#include "./../../global_structs/config_struct.h"

void get_config (config_struct *conf, char *conf_path) {

	config_t cfg;
	config_setting_t *input_files, *griding_mass_addignment_functions,
		*binning_algorithm, *run_params, *setting;

	libconfig_init(&cfg);
	libconfig_read_file(&cfg, conf_path);

	int i, len;
	const char *name, *alias;

	input_files = libconfig_lookup(&cfg, "input.files");
	len = libconfig_setting_length(input_files);
	for (i = 0; i < len; i++) {
		setting = libconfig_setting_get_elem(input_files, i);

		name = libconfig_setting_lookup_string(setting, "filename");
		conf->input_files[i][0] = strdup(name);

		alias = libconfig_setting_lookup_string(setting, "alias");
		conf->input_files[i][1] = strdup(alias);
	}


	griding_mass_addignment_functions =
		libconfig_lookup(&cfg,"griding.mass_assignment_functions");
	len = libconfig_setting_length(griding_mass_addignment_functions);
	for (i = 0; i < len; i++) {
		setting =
			libconfig_setting_get_elem(griding_mass_addignment_functions, i);

		name = libconfig_setting_lookup_string(setting, "name");
		conf->mass_assignment_functions[i][0] = strdup(name);

		alias =libconfig_setting_lookup_string(setting, "alias");
		conf->mass_assignment_functions[i][1] = strdup(alias);
	}

	binning_algorithm = libconfig_lookup(&cfg, "binning.algorithms");
	len = libconfig_setting_length(binning_algorithm);
	for (i = 0; i < len; i++) {
		setting = libconfig_setting_get_elem(binning_algorithm, i);

		name =  libconfig_setting_lookup_string(setting, "name");
		conf->binning[i][0] = strdup(name);

		alias = libconfig_setting_lookup_string(setting, "alias");
		conf->binning[i][1] = strdup(alias);
	}

	run_params = libconfig_lookup(&cfg, "run_params");
	conf->run_params.file_index =
		libconfig_setting_lookup_int(run_params, "file_index");
	conf->run_params.mass_assignment_index =
		libconfig_setting_lookup_int(run_params, "mass_assignment_index");
	conf->run_params.binning_index =
		libconfig_setting_lookup_int(run_params, "binning_index");
	conf->run_params.num_of_axis_grids =
		libconfig_setting_lookup_int(run_params, "num_of_axis_grids");

	libconfig_destroy(&cfg);
}
