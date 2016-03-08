#include <stdio.h>
#include <string.h>
#include <libconfig.h>

#include "./my_libconfig.h"
#include "./../../global_structs/config_struct.h"

config_struct load_config_from (char *conf_path) {

  config_struct conf;
	config_t cfg;
	config_setting_t *input_files, *griding_mass_addignment_functions,
		*binning_algorithms, *params, *setting;

	libconfig_init(&cfg);
	libconfig_read_file(&cfg, conf_path);

	int i, len, index;
	const char *name, *alias;

	input_files = libconfig_lookup(&cfg, "input.files");
	len = libconfig_setting_length(input_files);
	for (i = 0; i < len; i++) {
		setting = libconfig_setting_get_elem(input_files, i);

    index = libconfig_setting_lookup_int(setting, "index");

		name = libconfig_setting_lookup_string(setting, "filename");
		conf.files[index].filename = strdup(name);

		alias = libconfig_setting_lookup_string(setting, "alias");
		conf.files[index].alias = strdup(alias);
	}

	griding_mass_addignment_functions =
		libconfig_lookup(&cfg,"griding.mass_assignment_functions");
	len = libconfig_setting_length(griding_mass_addignment_functions);
	for (i = 0; i < len; i++) {
		setting =
			libconfig_setting_get_elem(griding_mass_addignment_functions, i);

    index = libconfig_setting_lookup_int(setting, "index");

		name = libconfig_setting_lookup_string(setting, "name");
		conf.massFunctions[index].name = strdup(name);

		alias =libconfig_setting_lookup_string(setting, "alias");
		conf.massFunctions[index].alias = strdup(alias);
	}

	binning_algorithms = libconfig_lookup(&cfg, "binning.algorithms");
	len = libconfig_setting_length(binning_algorithms);
	for (i = 0; i < len; i++) {
		setting = libconfig_setting_get_elem(binning_algorithms, i);

    index = libconfig_setting_lookup_int(setting, "index");

		name =  libconfig_setting_lookup_string(setting, "name");
		conf.binning[index].name = strdup(name);

		alias = libconfig_setting_lookup_string(setting, "alias");
		conf.binning[index].alias = strdup(alias);
	}

	params = libconfig_lookup(&cfg, "run_params");
	conf.params.fileIndex =
		libconfig_setting_lookup_int(params, "file_index");
	conf.params.massAssignmentIndex =
		libconfig_setting_lookup_int(params, "mass_assignment_index");
	conf.params.binningIndex =
		libconfig_setting_lookup_int(params, "binning_index");
	conf.params.numOfAxisGrids =
		libconfig_setting_lookup_int(params, "num_of_axis_grids");

	libconfig_destroy(&cfg);

  return conf;
}
